#include"CCThreadPool.h"
#include<memory>	//make_unique
using namespace std;

namespace nTool
{
	CThreadPool::CThreadPool(const size_t count)
		:size_{count},thr_{new CThreadPoolItem<void()>[count]}
	{
		for(auto p{thr_};p!=thr_+count;++p)
		{
			p->setCommun(make_unique<CThreadPoolCommun>(p,join_anyList_,waitingQue_,id_++));
			waitingQue_.emplace(id_.get(),p);
		}
	}

	void CThreadPool::join_all()
	{
		for(auto i{0};i!=count();++i)
			if(joinable(i))
				join(i);
	}

	size_t CThreadPool::join_any()
	{
		auto temp{join_anyList_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->join();
		return id;
	}

	CThreadPool::~CThreadPool()
	{
		delete []thr_;	//CThreadPoolItem is RAII, you don't have to call join_all()
	}
}