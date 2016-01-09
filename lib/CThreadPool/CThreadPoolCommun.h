#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<cstddef>	//size_t
#include<utility>	//pair
#include"Thread/Tool/CPimpl.h"

namespace nTool
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
		CPimpl<Impl> impl_;
		void detach_() override;	//notify CThreadPool::join_any
		void finish_() override;	//push CThreadPoolItem into waitingQue_
		void join_() override;	//erase join_anyList_ and push CThreadPoolItem into waitingQue_
	public:
		CThreadPoolCommun(CThreadPoolItem<void> *,CThreadList<pair> &,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun(const CThreadPoolCommun &)=delete;
		CThreadPoolCommun& operator=(const CThreadPoolCommun &)=delete;
		~CThreadPoolCommun();
	};

	template<class Ret>
	class CThreadPoolCommun_Ret:public CThreadPoolCommunBase
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem<Ret>*> pair;
	private:
		CThreadPoolItem<Ret> *item_;
		CThreadQueue<pair> &waitingQue_;
		const std::size_t id_;
		void detach_() override;	//push CThreadPoolItem into waitingQue_
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem<Ret> *,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun_Ret(const CThreadPoolCommun_Ret &)=delete;
		CThreadPoolCommun_Ret& operator=(const CThreadPoolCommun_Ret &)=delete;
	};
}

#include"CThreadPoolCommunT.cpp"

#endif