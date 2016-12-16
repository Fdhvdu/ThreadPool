#include"../header/CThreadPool.hpp"
#include<memory>	//make_unique
#include<mutex>
#include<vector>
#include<unordered_map>
#include"../../lib/header/thread/CWait_bounded_queue.hpp"
#include"../header/CThreadPoolItem.hpp"
#include"../header/IThreadPoolItemExecutor.hpp"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		unordered_map<thread_id,bool> is_joinable;
		mutex join_all_mut;	//only for join_all
		mutex wait_until_all_usable_mut;	//only for wait_until_all_usable
		CWait_bounded_queue<CThreadPoolItem*> waiting_queue;
		unordered_map<thread_id,CThreadPoolItem> thr;
		Impl(CThreadPool::size_type);
		thread_id add(function<void()> &&);
		void add_and_detach(function<void()> &&);
		void join_all();
		inline bool joinable(const thread_id id) const
		{
			return is_joinable.at(id)&&thr.at(id).is_running();
		}
		void wait_until_all_usable();
	};

	CThreadPool::Impl::Impl(CThreadPool::size_type size)
		:is_joinable{size},waiting_queue{size},thr{size}
	{
		while(size--)
		{
			//because the key_type of thr is thread_id, and thread_id is returned by CThreadPoolItem
			//so, you have to create a CThreadPoolItem first, and emplace get_id to thr
			CThreadPoolItem item;
			const auto id{item.get_id()};
			//it means "not joinable"
			is_joinable.emplace(id,false);
			waiting_queue.emplace_not_ts(&thr.emplace(id,move(item)).first->second);
		}
	}

	CThreadPool::thread_id CThreadPool::Impl::add(function<void()> &&func)
	{
		const auto temp{waiting_queue.wait_and_pop()};
		is_joinable[temp->get_id()]=true;
		try
		{
			temp->assign(make_unique<CThreadPoolItemExecutorJoin>(temp,&waiting_queue,move(func)));
		}catch(...)
		{
			waiting_queue.emplace_and_notify(temp);
			throw ;
		}
		return temp->get_id();
	}

	void CThreadPool::Impl::add_and_detach(function<void()> &&func)
	{
		const auto temp{waiting_queue.wait_and_pop()};
		is_joinable[temp->get_id()]=false;
		try
		{
			temp->assign(make_unique<CThreadPoolItemExecutorDetach>(temp,&waiting_queue,move(func)));
		}catch(...)
		{
			waiting_queue.emplace_and_notify(temp);
			throw ;
		}
	}

	void CThreadPool::Impl::join_all()
	{
		//if two threads call join_all at same time
		//because joinable and wait is not atomic
		//one thread may check joinable and execute wait
		//another thread may check same item, and because the first thread have not completed wait yet
		//it may call wait again, causing problem
		//so I use lock to prevent the event from happening
		lock_guard<mutex> lock{join_all_mut};
		for(auto &val:thr)
			if(joinable(val.first))
				thr[val.first].wait();
	}
	
	void CThreadPool::Impl::wait_until_all_usable()
	{
		//speed up, you can construct a vector in each threads in advance
		vector<decltype(waiting_queue)::value_type> vec;
		size_t size{thr.size()};
		vec.reserve(size);
		lock_guard<mutex> lock{wait_until_all_usable_mut};
		while(size--)
			vec.emplace_back(waiting_queue.wait_and_pop());
		for(auto &val:vec)
			waiting_queue.emplace_and_notify(move(val));
	}

	CThreadPool::thread_id CThreadPool::add_(std::function<void()> &&func)
	{
		return impl_->add(move(func));
	}

	void CThreadPool::add_and_detach_(std::function<void()> &&func)
	{
		impl_->add_and_detach(move(func));
	}

	CThreadPool::CThreadPool()
		:CThreadPool{thread::hardware_concurrency()}{}

	CThreadPool::CThreadPool(const CThreadPool::size_type size)
		:impl_{size}{}
	
	bool CThreadPool::empty() const noexcept
	{
		return impl_->waiting_queue.empty();
	}

	void CThreadPool::join(const thread_id id)
	{
		impl_->thr.at(id).wait();
	}

	void CThreadPool::join_all()
	{
		impl_->join_all();
	}

	bool CThreadPool::joinable(const thread_id id) const
	{
		return impl_->joinable(id);
	}

	CThreadPool::size_type CThreadPool::size() const noexcept
	{
		return static_cast<size_type>(impl_->thr.size());
	}

	void CThreadPool::wait_until_all_usable() const
	{
		impl_->wait_until_all_usable();
	}

	CThreadPool::~CThreadPool()=default;
}