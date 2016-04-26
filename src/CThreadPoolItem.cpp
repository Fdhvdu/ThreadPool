#include"../header/CThreadPoolItem.hpp"
#include<functional>	//bind, ref
#include<utility>	//move
#include"../header/IThreadPoolItemExecutor.hpp"
using namespace std;

namespace nThread
{
	void CThreadPoolItem::assign(unique_ptr<IThreadPoolItemExecutorBase> &&exec)
	{
		exec_=move(exec);
		IThreadPoolItemBase::exec_(bind(&IThreadPoolItemExecutorBase::exec,ref(*exec_)));
	}

	bool CThreadPoolItem::is_running() const noexcept
	{
		return exec_->is_running();
	}

	void CThreadPoolItem::wait() const
	{
		exec_->wait();
	}

	CThreadPoolItem::~CThreadPoolItem()
	{
		//if you don't call assign after constructing CThreadPoolItem
		//when destructing CThreadPoolItem, exec_ is empty
		if(exec_&&is_running())
			wait();	//no try-block here (this is what I want)
	}
}