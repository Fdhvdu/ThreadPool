#include"../header/CThreadPool.hpp"
#include<memory>	//make_unique
#include<mutex>
#include<vector>
#include<unordered_map>
#include"../../lib/header/thread/CThreadList.hpp"
#include"../../lib/header/thread/CThreadQueue.hpp"
#include"../header/CThreadPoolCommun.hpp"
#include"../header/CThreadPoolItem.hpp"
#include"../header/IThreadPoolItemExecutor.hpp"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		unordered_map<thread::id,bool> is_joinable;
		mutex join_all_mut;	//only for join_all
		CThreadList<CThreadPoolItem*> join_anyList;
		mutex wait_until_all_available_mut;	//only for wait_until_all_available
		CThreadQueue<CThreadPoolItem*> waitingQue;
		unordered_map<thread::id,CThreadPoolItem> thr;
		Impl(size_t);
		CThreadPool::thread_id add(function<void()> &&);
		void add_and_detach(function<void()> &&);
		void join_all();
		bool joinable(thread::id) const noexcept;
		void wait_until_all_available();
	};

	CThreadPool::Impl::Impl(size_t size)
	{
		while(size--)
		{
			//because the key_type of thr is thread::id, and thread::id is returned by CThreadPoolItem
			//so, you have to create a CThreadPoolItem first, and emplace get_id to thr
			CThreadPoolItem item;
			const auto id{item.get_id()};
			//it means "not joinable"
			is_joinable.emplace(id,false);
			//thr.emplace(item.get_id(),move(item)); is wrong
			//you cannot guarantee item.get_id() will execute prior to move(item)
			waitingQue.init_emplace(&thr.emplace(id,move(item)).first->second);
		}
	}

	CThreadPool::thread_id CThreadPool::Impl::add(function<void()> &&func)
	{
		auto temp{waitingQue.wait_and_pop()};
		is_joinable[temp->get_id()]=true;
		temp->assign(make_unique<CThreadPoolItemExecutorJoin>(CThreadPoolCommunJoin{temp,&join_anyList,&waitingQue},move(func)));
		return temp->get_id();
	}

	void CThreadPool::Impl::add_and_detach(function<void()> &&func)
	{
		auto temp{waitingQue.wait_and_pop()};
		is_joinable[temp->get_id()]=false;
		temp->assign(make_unique<CThreadPoolItemExecutorDetach>(CThreadPoolCommunDetach{temp,&waitingQue},move(func)));
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

	bool CThreadPool::Impl::joinable(const thread::id id) const noexcept
	{
		if(is_joinable.at(id))
			return thr.at(id).is_running();
		return false;
	}

	void CThreadPool::Impl::wait_until_all_available()
	{
		//speed up, you can construct a vector in each threads in advance
		vector<decltype(waitingQue)::value_type> vec;
		vec.reserve(thr.size());
		lock_guard<mutex> lock{wait_until_all_available_mut};
		while(vec.size()!=vec.capacity())
			vec.emplace_back(waitingQue.wait_and_pop());
		for(auto &val:vec)
			waitingQue.emplace(move(val));
	}

	CThreadPool::thread_id CThreadPool::add_(std::function<void()> &&func)
	{
		return impl_.get().add(move(func));
	}

	void CThreadPool::add_and_detach_(std::function<void()> &&func)
	{
		impl_.get().add_and_detach(move(func));
	}

	CThreadPool::CThreadPool(const size_t size)
		:impl_{size}{}
	
	size_t CThreadPool::available() const noexcept
	{
		return impl_.get().waitingQue.size();
	}

	size_t CThreadPool::count() const noexcept
	{
		return impl_.get().thr.size();
	}

	void CThreadPool::join(const thread_id id)
	{
		impl_.get().thr[id].wait();
	}

	void CThreadPool::join_all()
	{
		impl_.get().join_all();
	}

	CThreadPool::thread_id CThreadPool::join_any()
	{
		auto temp{impl_.get().join_anyList.wait_and_pop()};
		temp->wait();
		return temp->get_id();
	}

	bool CThreadPool::joinable(const thread_id id) const noexcept
	{
		return impl_.get().joinable(id);
	}

	void CThreadPool::wait_until_all_available() const
	{
		impl_.get().wait_until_all_available();
	}

	CThreadPool::~CThreadPool(){}
}