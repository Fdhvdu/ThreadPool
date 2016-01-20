#include"../header/CThreadPoolItem.h"

namespace nThread
{
	void CThreadPoolItem::loop_()
	{
		while(waiting_(),!destructor_)
			exec_->exec();
	}

	void CThreadPoolItem::waiting_()
	{
		wait_.wait();
	}
	
	void CThreadPoolItem::wake_()
	{
		wait_.signal();
	}

	CThreadPoolItem::CThreadPoolItem()
		:destructor_{false},wait_{0},thr_{&CThreadPoolItem::loop_,this}{}
	
	void CThreadPoolItem::join()
	{
		exec_->wait();
	}

	bool CThreadPoolItem::joinable() const noexcept
	{
		return exec_->joinable();
	}

	CThreadPoolItem::~CThreadPoolItem()
	{
		if(exec_&&exec_->is_running())
			exec_->wait();
		destructor_=true;
		wake_();
	}

	void CThreadPoolItem::setCommun(std::unique_ptr<CThreadPoolCommunBase> &&commun)
	{
		commun_=std::move(commun);
	}

	void CThreadPoolItemExecutorDetach::exec()
	{
		func_();
		complete_.signal();
		commun_->communPoolDetach();
	}
	
	void CThreadPoolItemExecutorJoin::exec()
	{
		func_();
		commun_->communPoolFinish();
		complete_.signal();
	}

	void CThreadPoolItemExecutorJoin::wait()
	{
		complete_.wait();
		running_=false;
		commun_->communPoolJoin();
	}
}