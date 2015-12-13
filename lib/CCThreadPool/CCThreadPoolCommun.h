#ifndef __CCThreadPoolCommun
#define __CCThreadPoolCommun
#include<cstddef>	//size_t
#include<utility>	//pair

namespace nTool
{
	template<class Func>
	class CThreadPoolItem;

	template<class Func>
	struct ThreadPoolCommunBase
	{
		ThreadPoolCommunBase()=default;
		ThreadPoolCommunBase(const ThreadPoolCommunBase &)=delete;
		virtual void communPoolFinish();
		virtual void communPoolDetach();
		virtual void communPoolJoin();
		ThreadPoolCommunBase& operator=(const ThreadPoolCommunBase &)=delete;
		virtual ~ThreadPoolCommunBase();
	};

	template<class Func>
	class CThreadList;
	template<class Func>
	class CThreadQueue;

	template<class Func>
	class CThreadPoolCommun:public ThreadPoolCommunBase<Func>
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem<Func>*> pair;
	private:
		CThreadPoolItem<Func> *item_;
		CThreadList<pair> &join_anyList_;	//or use deque
		CThreadQueue<pair> &waitingQue_;
		const std::size_t id_;
	public:
		CThreadPoolCommun(CThreadPoolItem<Func> *,CThreadList<pair> &,CThreadQueue<pair> &,const std::size_t);
		CThreadPoolCommun(const CThreadPoolCommun &)=delete;
		void communPoolFinish() override;	//notify CThreadPool::join_any
		void communPoolDetach() override;	//push CThreadPoolItem into waitingQue_
		void communPoolJoin() override;	//erase join_anyList_ and push CThreadPoolItem into waitingQue_
		inline std::size_t id() const noexcept
		{
			return id_;
		}
		CThreadPoolCommun& operator=(const CThreadPoolCommun &)=delete;
	};

	template<class Func>
	class CThreadPoolCommun_Ret:public ThreadPoolCommunBase<Func>
	{
	public:
		typedef std::pair<std::size_t,CThreadPoolItem<Func>*> pair;
	private:
		CThreadPoolItem<Func> *item_;
		CThreadQueue<pair> &waitingQue_;
		const std::size_t id_;
	public:
		CThreadPoolCommun_Ret(CThreadPoolItem<Func> *,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun_Ret(const CThreadPoolCommun_Ret &)=delete;
		void communPoolDetach() override;	//push CThreadPoolItem into waitingQue_
		inline std::size_t id() const noexcept
		{
			return id_;
		}
		CThreadPoolCommun_Ret& operator=(const CThreadPoolCommun_Ret &)=delete;
	};
}

#include"CCThreadPoolCommunT.cpp"

#endif