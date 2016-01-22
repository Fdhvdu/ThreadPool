#ifndef CTHREADPOOLCOMMUN_RET
#define CTHREADPOOLCOMMUN_RET
#include"IThreadPoolCommun.h"
#include"../../lib/header/thread/CThreadQueue.h"

namespace nThread
{
	template<class Func>
	class CThreadPoolItem_Ret;

	template<class Ret>
	class CThreadPoolCommun_Ret:public IThreadPoolCommunBase
	{
		CThreadPoolItem_Ret<Ret> *item_;
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> &waitingQue_;
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem_Ret<Ret> *,CThreadQueue<CThreadPoolItem_Ret<Ret>*> &);
		void func_is_completed() override{}
		void destroy() override;	//push CThreadPoolItem into waitingQue_
	};
}

#include"CThreadPoolCommun_Ret.cpp"

#endif