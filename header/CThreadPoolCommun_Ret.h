#ifndef CTHREADPOOLCOMMUN_RET
#define CTHREADPOOLCOMMUN_RET
#include"CThreadPoolCommun.h"
#include"../../lib/header/thread/CThreadQueue.h"

namespace nThread
{
	template<class Func>
	class CThreadPoolItem_Ret;

	template<class Ret>
	class CThreadPoolCommun_Ret:public CThreadPoolCommunBase
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem_Ret<Ret>*> pair;
	private:
		CThreadPoolItem_Ret<Ret> *item_;
		CThreadQueue<pair> &waitingQue_;
		const std::size_t id_;
	protected:
		void detach_() override;	//push CThreadPoolItem into waitingQue_
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem_Ret<Ret> *,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun_Ret(const CThreadPoolCommun_Ret &)=delete;
		CThreadPoolCommun_Ret& operator=(const CThreadPoolCommun_Ret &)=delete;
	};
}

#include"CThreadPoolCommun_Ret.cpp"

#endif