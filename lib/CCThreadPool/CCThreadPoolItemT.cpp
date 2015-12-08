#include"CCThreadPoolItem.h"

namespace nTool
{
	template<class Func_t>
	void CThreadPoolItem<Func_t>::loop_()
	{
		while(waiting_(),!destructor_)
			exec_->exec();
	}

	template<class Func_t>
	CThreadPoolItem<Func_t>::CThreadPoolItem()
		:destructor_(false),joinable_(false),wait_(0),thr_(&CThreadPoolItem<Func_t>::loop_,this){}

	template<class Func_t>
	template<class ... Args>
	void CThreadPoolItem<Func_t>::assign(Args &&...args)
	{
		exec_=std::unique_ptr<ThreadPoolItemExecutorBase<Func_t>>(new CThreadPoolItemExecutorJoin<Func_t>(commun_.get(),std::forward<Args>(args)...));
		joinable_=true;
		wake_();
	}

	template<class Func_t>
	template<class ... Args>
	void CThreadPoolItem<Func_t>::assign_and_detach(Args &&...args)
	{
		exec_=std::unique_ptr<ThreadPoolItemExecutorBase<Func_t>>(new CThreadPoolItemExecutorDetach<Func_t>(commun_.get(),std::forward<Args>(args)...));
		joinable_=false;
		wake_();
	}

	template<class Func_t>
	template<class ... Args>
	void CThreadPoolItem<Func_t>::assign_and_ret(Args &&...args)
	{
		exec_=std::unique_ptr<ThreadPoolItemExecutorBase<Func_t>>(new CThreadPoolItemExecutorRet<Func_t>(commun_.get(),std::forward<Args>(args)...));
		joinable_=false;
		wake_();
	}

	template<class Func_t>
	CThreadPoolItem<Func_t>::~CThreadPoolItem()
	{
		if(exec_->is_running())
			exec_->wait();
		destructor_=true;
		wake_();
	}

	template<class Func_t>
	ThreadPoolItemExecutorBase<Func_t>::~ThreadPoolItemExecutorBase(){}

	template<class Func_t>
	template<class ... Args>
	CThreadPoolItemExecutorDetach<Func_t>::CThreadPoolItemExecutorDetach(ThreadPoolCommunBase<Func_t> *commun,Args &&...args)
		:commun_(commun),complete_(0),func_(std::bind(std::forward<Args>(args)...)),running_(true){}

	template<class Func_t>
	void CThreadPoolItemExecutorDetach<Func_t>::exec()
	{
		func_();
		commun_->communPoolDetach();
		complete_.signal();
		running_=false;
	}

	template<class Func_t>
	template<class ... Args>
	CThreadPoolItemExecutorJoin<Func_t>::CThreadPoolItemExecutorJoin(ThreadPoolCommunBase<Func_t> *commun,Args &&...args)
		:commun_(commun),complete_(0),func_(std::bind(std::forward<Args>(args)...)),running_(true){}

	template<class Func_t>
	void CThreadPoolItemExecutorJoin<Func_t>::exec()
	{
		func_();
		commun_->communPoolFinish();
		complete_.signal();
	}

	template<class Func_t>
	void CThreadPoolItemExecutorJoin<Func_t>::wait()
	{
		complete_.wait();
		running_=false;
		commun_->communPoolJoin();
	}

	template<class Func_t>
	template<class ... Args>
	CThreadPoolItemExecutorRet<Func_t>::CThreadPoolItemExecutorRet(ThreadPoolCommunBase<Func_t> *commun,Args &&...args)
		:asyncExec_(std::forward<Args>(args)...),commun_(commun){}

	template<class Func_t>
	decltype(std::declval<CAsyncExecutor<Func_t>>().get()) CThreadPoolItemExecutorRet<Func_t>::get()
	{
		const auto temp(asyncExec_.get());
		commun_->communPoolJoin();
		return temp;
	}
}