#include"../header/CThreadPool.h"
#include<memory>	//make_unique
#include<mutex>
#include<thread>
#include<vector>
#include<unordered_map>
#include"../../lib/header/thread/CThreadList.h"
#include"../../lib/header/thread/CThreadQueue.h"
#include"../header/CThreadPoolCommun.h"
#include"../header/CThreadPoolItem.h"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		CThreadList<CThreadPoolItem*> join_anyList;
		mutex mut;	//only for wait_until_all_available
		CThreadQueue<CThreadPoolItem*> waitingQue;
		unordered_map<thread::id,CThreadPoolItem> thr;
		Impl(size_t);
		void wait_until_all_available();
	};

	CThreadPool::Impl::Impl(size_t size)
	{
		while(size--)
		{
			CThreadPoolItem item;
			const auto id{item.get_id()};
			thr.emplace(id,move(item));
			thr[id].setCommun(make_unique<CThreadPoolCommun>(&thr[id],join_anyList,waitingQue));
			waitingQue.emplace(&thr[id]);
		}
	}
	
	void CThreadPool::Impl::wait_until_all_available()
	{
		vector<decltype(waitingQue)::value_type> vec;
		vec.reserve(thr.size());
		lock_guard<mutex> lock{mut};
		while(vec.size()!=vec.capacity())
			vec.emplace_back(waitingQue.wait_and_pop());
		for(auto &val:vec)
			waitingQue.emplace(move(val));
	}

	CThreadPool::thread_id CThreadPool::add_(std::function<void()> &&func)
	{
		auto temp{impl_.get().waitingQue.wait_and_pop()};
		const auto id{temp->get_id()};
		temp->assign(move(func));
		return id;
	}

	void CThreadPool::add_and_detach_(std::function<void()> &&func)
	{
		impl_.get().waitingQue.wait_and_pop()->assign_and_detach(move(func));
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
		impl_.get().thr[id].join();
	}

	bool CThreadPool::joinable(const thread_id id) const noexcept
	{
		return impl_.get().thr[id].joinable();
	}

	void CThreadPool::join_all()
	{
		for(auto &val:impl_.get().thr)
			if(val.second.joinable())
				val.second.join();
	}

	CThreadPool::thread_id CThreadPool::join_any()
	{
		auto temp{impl_.get().join_anyList.wait_and_pop()};
		const auto id{temp->get_id()};
		temp->join();
		return id;
	}

	void CThreadPool::wait_until_all_available() const
	{
		impl_.get().wait_until_all_available();
	}

	CThreadPool::~CThreadPool(){}
}