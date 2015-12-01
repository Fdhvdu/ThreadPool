#ifndef __CCThreadPool_Ret
#define __CCThreadPool_Ret
#include<cstddef>	//size_t
#include"./CCThreadPool/Thread/Tool/CCID.h"
#include"./CCThreadPool/CCThreadPoolCommun.h"
#include"./CCThreadPool/CCThreadPoolItem.h"
#include"./CCThreadPool/Thread/CCThreadQueue.h"

namespace nTool
{
	template<class Func>
	class CThreadPool_Ret	//same job, different argument and return value
	{
		CID id_;
		const std::size_t size_;
		CThreadQueue<typename CThreadPoolCommun_Ret<Func>::pair> waitingQue_;	//enough
		CThreadPoolItem<Func> *thr_;
	public:
		explicit CThreadPool_Ret(const std::size_t &);
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		template<class ... Args>
		std::size_t add(Args &&...);
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		inline std::size_t count() const noexcept
		{
			return size_;
		}
		inline decltype(std::declval<CThreadPoolItem<Func>>().join()) get(const std::size_t &id)
		{
			return thr_[id].join();
		}
		inline bool valid(const std::size_t &id) const noexcept
		{
			return thr_[id].joinable();
		}
		inline void wait(const std::size_t &id) const	//block until ready
		{
			thr_[id].wait();
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
		~CThreadPool_Ret();
	};
}

#include"CCThreadPool_RetT.cpp"

#endif