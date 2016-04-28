#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<utility>	//forward
#include"../../lib/header/thread/CTask.hpp"
#include"../../lib/header/thread/CWait_bounded_queue.hpp"
#include"../../lib/header/tool/CScopeGuard.hpp"
#include"IThreadPoolItemBase.hpp"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret:public IThreadPoolItemBase
	{
		CTask<Ret> exec_;
		CWait_bounded_queue<CThreadPoolItem_Ret<Ret>*> *waiting_queue_;
	public:
		CThreadPoolItem_Ret(CWait_bounded_queue<CThreadPoolItem_Ret<Ret>*> *waitingQue)
			:waiting_queue_{waitingQue}{}
		CThreadPoolItem_Ret(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret(CThreadPoolItem_Ret &&)=default;
		template<class Func,class ... Args>
		void assign(Func &&func,Args &&...args)
		{
			exec_=CTask<Ret>{std::forward<Func>(func),std::forward<Args>(args)...};
			IThreadPoolItemBase::exec_([this]{exec_();});
		}
		inline Ret get()
		{
			const nTool::CScopeGuard sg{[this]{waiting_queue_->emplace_and_notify(this);}};
			return exec_.get();
		}
		bool is_running() const noexcept override
		{
			return exec_.valid();
		}
		void wait() const override
		{
			exec_.wait();
		}
		CThreadPoolItem_Ret& operator=(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret& operator=(CThreadPoolItem_Ret &&)=default;
		~CThreadPoolItem_Ret()
		{
			if(is_running())
				wait();
		}
	};
}

#endif