#include"../header/CThreadPool.h"
#include<memory>	//make_unique
#include<mutex>
#include<utility>	//move
#include<vector>
#include"../../lib/header/algorithm/algorithm.h"
#include"../../lib/header/thread/CThreadList.h"
#include"../../lib/header/tool/CId.h"
#include"../header/CThreadPoolItem.h"
using namespace std;

namespace nThread
{
	struct CThreadPool::Impl
	{
		nTool::CId id;
		CThreadList<typename CThreadPoolCommun::pair> join_anyList;
		mutex mut;	//only for wait_until_all_available
		vector<CThreadPoolItem<void>> thr;
		Impl(size_t,CThreadQueue<typename CThreadPoolCommun::pair> &);
	};

	CThreadPool::Impl::Impl(const size_t size,CThreadQueue<typename CThreadPoolCommun::pair> &waitingQue)
		:thr(size)
	{
		for(auto &val:thr)
		{
			val.setCommun(make_unique<CThreadPoolCommun>(&val,join_anyList,waitingQue,id++));
			waitingQue.emplace(id.get(),&val);
		}
	}

	CThreadPool::CThreadPool(const size_t size)
		:impl_{size,waitingQue_}{}

	std::size_t CThreadPool::count() const noexcept
	{
		return impl_.get().thr.size();
	}

	void CThreadPool::join(const size_t id)
	{
		impl_.get().thr[id].join();
	}

	bool CThreadPool::joinable(const size_t id) const noexcept
	{
		return impl_.get().thr[id].joinable();
	}

	void CThreadPool::join_all()
	{
		for(auto &val:impl_.get().thr)
			if(val.joinable())
				val.join();
	}

	size_t CThreadPool::join_any()
	{
		auto temp{impl_.get().join_anyList.wait_and_pop()};
		const auto id{temp.first};
		temp.second->join();
		return id;
	}

	void CThreadPool::wait_until_all_available() const
	{
		vector<typename CThreadPoolCommun::pair> vec;
		vec.reserve(count());
		lock_guard<mutex> lock{impl_.get().mut};
		while(vec.size()!=count())
			vec.emplace_back(waitingQue_.wait_and_pop());
		for(auto &val:vec)
			waitingQue_.emplace(move(val));
	}

	CThreadPool::~CThreadPool(){}
}