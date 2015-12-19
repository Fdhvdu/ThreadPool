#ifndef __CCThreadPool_Ret
#define __CCThreadPool_Ret
#include<cstddef>	//size_t
#include"CCThreadPool/CCThreadPoolCommun.h"
#include"CCThreadPool/CCThreadPoolItem.h"
#include"CCThreadPool/Thread/CCThreadQueue.h"
#include"CCThreadPool/Thread/Tool/CCID.h"

namespace nTool
{
	template<class Ret>
	class CThreadPool_Ret	//same job, different argument and return value
	{
		CID id_;
		const std::size_t size_;
		CThreadQueue<typename CThreadPoolCommun_Ret<Ret>::pair> waitingQue_;	//enough
		CThreadPoolItem<Ret> *thr_;
	public:
		explicit CThreadPool_Ret(std::size_t);
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		template<class Func,class ... Args>
		std::size_t add(Func &&,Args &&...);
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		inline std::size_t count() const noexcept
		{
			return size_;
		}
		inline decltype(std::declval<CThreadPoolItem<Ret>>().get()) get(const std::size_t id)
		{
			return thr_[id].get();
		}
		inline bool valid(const std::size_t id) const noexcept
		{
			return thr_[id].valid();
		}
		inline void wait(const std::size_t id)	//block until ready
		{
			thr_[id].wait();
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
		~CThreadPool_Ret();
	};
}

#include"CCThreadPool_RetT.cpp"

#endif