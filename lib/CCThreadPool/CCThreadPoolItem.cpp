#include"CCThreadPoolItem.h"

namespace nTool
{
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