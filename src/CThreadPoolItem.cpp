#include"../header/CThreadPoolItem.hpp"
#include<functional>	//bind
#include<utility>	//move
#include"../header/IThreadPoolItemExecutor.hpp"
using namespace std;

namespace nThread
{
	void CThreadPoolItem::assign(unique_ptr<IThreadPoolItemExecutorBase> &&exec)
	{
		exec_=move(exec);
		IThreadPoolItemBase::exec_(bind(&IThreadPoolItemExecutorBase::exec,exec_.get()));
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
		if(exec_&&is_running())
			wait();
	}
}