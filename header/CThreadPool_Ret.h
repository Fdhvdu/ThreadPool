#ifndef CTHREADPOOL_RET
#define CTHREADPOOL_RET
#include<cstddef>	//size_t
#include<thread>	//thread::id
#include<unordered_map>
#include"../../lib/header/thread/CThreadQueue.h"
#include"../../lib/header/tool/CId.h"
#include"CThreadPoolCommun_Ret.h"
#include"CThreadPoolItem_Ret.h"

namespace nThread
{
	template<class Ret>
	class CThreadPool_Ret	//same job, different argument and return value
	{
	public:
		typedef std::thread::id thread_id;
	private:
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> waitingQue_;
		std::unordered_map<thread_id,CThreadPoolItem_Ret<Ret>> thr_;
	public:
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
			return thr_.size();
		}
		inline Ret get(const thread_id id)
		{
			return thr_.at(id).get();
		}
		inline bool valid(const thread_id id) const noexcept
		{
			return thr_.at(id).is_running();
		}
		inline void wait(const thread_id id)	//block until ready
		{
			thr_.at(id).wait();
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
	};
}

#include"CThreadPool_Ret.cpp"

#endif