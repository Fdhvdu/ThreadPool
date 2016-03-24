#include"../header/CThreadPool.hpp"
#include<memory>	//make_unique
#include<mutex>
#include<vector>
#include<unordered_map>
#include"../../lib/header/thread/CThread_forward_list.hpp"
#include"../../lib/header/thread/CThreadRingBuf.hpp"
#include"../header/CThreadPoolCommun.hpp"
#include"../header/CThreadPoolItem.hpp"
#include"../header/IThreadPoolItemExecutor.hpp"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		unordered_map<thread_id,bool> is_joinable;
		mutex join_all_mut;	//only for join_all
		CThread_forward_list<CThreadPoolItem*> join_anyList;
		mutex wait_until_all_available_mut;	//only for wait_until_all_available
		CThreadRingBuf<CThreadPoolItem*> waiting_buf;
		unordered_map<thread_id,CThreadPoolItem> thr;
		Impl(CThreadPool::size_type);
		thread_id add(function<void()> &&);
		void add_and_detach(function<void()> &&);
		inline void join(const thread_id id)
		{
			thr[id].wait();
		}
		void join_all();
		bool joinable(thread_id) const noexcept;
		void wait_until_all_available();
	};

	CThreadPool::Impl::Impl(CThreadPool::size_type size)
		:is_joinable{size},waiting_buf{size},thr{size}
	{
		while(size--)
		{
			//because the key_type of thr is thread_id, and thread_id is returned by CThreadPoolItem
			//so, you have to create a CThreadPoolItem first, and emplace get_id to thr
			CThreadPoolItem item;
			const auto id{item.get_id()};
			//it means "not joinable"
			is_joinable.emplace(id,false);
			//thr.emplace(item.get_id(),move(item)); is wrong
			//you cannot guarantee item.get_id() will execute prior to move(item)
			waiting_buf.write(&thr.emplace(id,move(item)).first->second);
		}
	}

	CThreadPool::thread_id CThreadPool::Impl::add(function<void()> &&func)
	{
		auto temp{waiting_buf.read()};
		is_joinable[temp->get_id()]=true;
		try
		{
			temp->assign(make_unique<CThreadPoolItemExecutorJoin>(CThreadPoolCommunJoin{temp,&join_anyList,&waiting_buf},move(func)));
		}catch(...)
		{
			waiting_buf.write(temp);
			throw ;
		}
		return temp->get_id();
	}

	void CThreadPool::Impl::add_and_detach(function<void()> &&func)
	{
		auto temp{waiting_buf.read()};
		is_joinable[temp->get_id()]=false;
		try
		{
			temp->assign(make_unique<CThreadPoolItemExecutorDetach>(CThreadPoolCommunDetach{temp,&waiting_buf},move(func)));
		}catch(...)
		{
			waiting_buf.write(temp);
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
				join(val.first);
	}

	bool CThreadPool::Impl::joinable(const thread_id id) const noexcept
	{
		if(is_joinable.at(id))
			return thr.at(id).is_running();
		return false;
	}

	void CThreadPool::Impl::wait_until_all_available()
	{
		//speed up, you can construct a vector in each threads in advance
		vector<decltype(waiting_buf)::value_type> vec;
		vec.reserve(thr.size());
		lock_guard<mutex> lock{wait_until_all_available_mut};
		while(vec.size()!=vec.capacity())
			vec.emplace_back(waiting_buf.read());
		for(auto &val:vec)
			waiting_buf.write(move(val));
	}

	CThreadPool::thread_id CThreadPool::add_(std::function<void()> &&func)
	{
		return impl_.get().add(move(func));
	}

	void CThreadPool::add_and_detach_(std::function<void()> &&func)
	{
		impl_.get().add_and_detach(move(func));
	}

	CThreadPool::CThreadPool()
		:CThreadPool(thread::hardware_concurrency()){}

	CThreadPool::CThreadPool(const CThreadPool::size_type size)
		:impl_{size}{}

	CThreadPool::size_type CThreadPool::available() const noexcept
	{
		return static_cast<size_type>(impl_.get().waiting_buf.available());
	}

	void CThreadPool::join(const thread_id id)
	{
		impl_.get().join(id);
	}

	void CThreadPool::join_all()
	{
		impl_.get().join_all();
	}

	CThreadPool::thread_id CThreadPool::join_any()
	{
		auto temp{impl_.get().join_anyList.wait_and_pop_front()};
		temp->wait();
		return temp->get_id();
	}

	bool CThreadPool::joinable(const thread_id id) const noexcept
	{
		return impl_.get().joinable(id);
	}

	CThreadPool::size_type CThreadPool::size() const noexcept
	{
		return static_cast<size_type>(impl_.get().thr.size());
	}

	void CThreadPool::wait_until_all_available() const
	{
		impl_.get().wait_until_all_available();
	}

	CThreadPool::~CThreadPool()=default;
}