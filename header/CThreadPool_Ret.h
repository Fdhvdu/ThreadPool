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
		typedef std::size_t thread_id;
		explicit CThreadPool_Ret(std::size_t);
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		template<class Func,class ... Args>
		thread_id add(Func &&,Args &&...);
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		inline std::size_t count() const noexcept
		{
			return size_;
		}
		inline Ret get(const thread_id id)
		{
			return thr_[id].get();
		}
		inline bool valid(const thread_id id) const noexcept
		{
			return thr_[id].valid();
		}
		inline void wait(const thread_id id) const	//block until ready
		{
			thr_[id].wait();
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
		~CThreadPool_Ret();
	};
}

#include"CThreadPool_Ret.cpp"

#endif