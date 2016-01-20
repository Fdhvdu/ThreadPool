#include"../header/CThreadPool.h"
#include<memory>	//make_unique
#include<mutex>
#include<thread>
#include<utility>	//move
#include<vector>
#include<unordered_map>
#include"../../lib/header/algorithm/algorithm.h"
#include"../../lib/header/thread/CThreadList.h"
#include"../header/CThreadPoolCommun.h"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		CThreadList<CThreadPoolItem*> join_anyList;
		mutex mut;	//only for wait_until_all_available
		unordered_map<thread::id,CThreadPoolItem> thr;
		Impl(size_t,CThreadQueue<CThreadPoolItem*> &);
	};

	CThreadPool::Impl::Impl(const size_t size,CThreadQueue<CThreadPoolItem*> &waitingQue)
	{
		nAlgorithm::for_each_val<size_t>(0,size,[&](const auto){
			CThreadPoolItem item;
			const auto id{item.get_id()};
			thr.emplace(id,move(item));
			thr[id].setCommun(make_unique<CThreadPoolCommun>(&thr[id],join_anyList,waitingQue));
			waitingQue.emplace(&thr[id]);
		});
	}

	CThreadPool::CThreadPool(const size_t size)
		:impl_{size,waitingQue_}{}

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
		vector<decltype(waitingQue_)::value_type> vec;
		vec.reserve(count());
		lock_guard<mutex> lock{impl_.get().mut};
		while(vec.size()!=count())
			vec.emplace_back(waitingQue_.wait_and_pop());
		for(auto &val:vec)
			waitingQue_.emplace(move(val));
	}

	CThreadPool::~CThreadPool(){}
}