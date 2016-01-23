#ifndef CTHREADPOOLCOMMUN_RET
#define CTHREADPOOLCOMMUN_RET
#include"../../lib/header/thread/CThreadQueue.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret;

	template<class Ret>
	class CThreadPoolCommun_Ret
	{
		CThreadPoolItem_Ret<Ret> *item_;
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> &waitingQue_;
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem_Ret<Ret> *,CThreadQueue<CThreadPoolItem_Ret<Ret>*> &);
		void destroy()	//push CThreadPoolItem into waitingQue_
		{
			waitingQue_.emplace(item_);
		}
	};
}

#include"CThreadPoolCommun_Ret.cpp"

#endif