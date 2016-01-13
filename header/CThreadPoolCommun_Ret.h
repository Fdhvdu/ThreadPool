#ifndef CTHREADPOOLCOMMUN_RET
#define CTHREADPOOLCOMMUN_RET
#include"CThreadPoolCommun.h"
#include"../../lib/header/thread/CThreadQueue.h"
#include"CThreadPoolItem.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolCommun_Ret:public CThreadPoolCommunBase
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem<Ret>*> pair;
	private:
		CThreadPoolItem<Ret> *item_;
		CThreadQueue<pair> &waitingQue_;
		const std::size_t id_;
	protected:
		void detach_() override;	//push CThreadPoolItem into waitingQue_
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem<Ret> *,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun_Ret(const CThreadPoolCommun_Ret &)=delete;
		CThreadPoolCommun_Ret& operator=(const CThreadPoolCommun_Ret &)=delete;
	};
}

#include"CThreadPoolCommun_Ret.cpp"

#endif