#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<cstddef>	//size_t
#include<utility>	//pair
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	template<class Func>
	class CThreadList;
	template<class Func>
	class CThreadPoolItem;
	template<class Func>
	class CThreadQueue;

	class CThreadPoolCommunBase
	{
		virtual void detach_();
		virtual void finish_();
		virtual void join_();
	public:
		CThreadPoolCommunBase()=default;
		CThreadPoolCommunBase(const CThreadPoolCommunBase &)=delete;
		void communPoolDetach();
		void communPoolFinish();
		void communPoolJoin();
		CThreadPoolCommunBase& operator=(const CThreadPoolCommunBase &)=delete;
		virtual ~CThreadPoolCommunBase();
	};

	class CThreadPoolCommun:public CThreadPoolCommunBase
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem<void>*> pair;
	private:
		struct Impl;
		nTool::CPimpl<Impl> impl_;
		void detach_() override;	//notify CThreadPool::join_any
		void finish_() override;	//push CThreadPoolItem into waitingQue_
		void join_() override;	//erase join_anyList_ and push CThreadPoolItem into waitingQue_
	public:
		CThreadPoolCommun(CThreadPoolItem<void> *,CThreadList<pair> &,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun(const CThreadPoolCommun &)=delete;
		CThreadPoolCommun& operator=(const CThreadPoolCommun &)=delete;
		~CThreadPoolCommun();
	};
}

#endif