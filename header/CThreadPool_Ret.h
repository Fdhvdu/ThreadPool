#ifndef CTHREADPOOL_RET
#define CTHREADPOOL_RET
#include<cstddef>	//size_t
#include"../../lib/header/thread/CThreadQueue.h"
#include"../../lib/header/tool/CId.h"
#include"CThreadPoolCommun_Ret.h"
#include"CThreadPoolItem_Ret.h"

namespace nThread
{
	template<class Ret>
	class CThreadPool_Ret	//same job, different argument and return value
	{
		nTool::CId id_;
		const std::size_t size_;
		CThreadQueue<typename CThreadPoolCommun_Ret<Ret>::pair> waitingQue_;	//enough
		CThreadPoolItem_Ret<Ret> *thr_;
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
		inline decltype(std::declval<CThreadPoolItem_Ret<Ret>>().get()) get(const std::size_t id)
		{
			return thr_[id].get();
		}
		inline bool valid(const std::size_t id) const noexcept
		{
			return thr_[id].valid();
		}
		inline void wait(const std::size_t id) const	//block until ready
		{
			thr_[id].wait();
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
		~CThreadPool_Ret();
	};
}

#include"CThreadPool_Ret.cpp"

#endif