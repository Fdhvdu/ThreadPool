#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<functional>	//bind
#include<utility>	//forward
#include"../../lib/header/tool/CScopeGuard.hpp"
#include"../../lib/header/thread/CTask.hpp"
#include"../../lib/header/thread/CThreadRingBuf.hpp"
#include"IThreadPoolItemBase.hpp"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret:public IThreadPoolItemBase
	{
		CTask<Ret> exec_;
		CThreadRingBuf<CThreadPoolItem_Ret<Ret>*> *waiting_buf_;
	public:
		CThreadPoolItem_Ret(CThreadRingBuf<CThreadPoolItem_Ret<Ret>*> *waitingQue)
			:waiting_buf_{waitingQue}{}
		CThreadPoolItem_Ret(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret(CThreadPoolItem_Ret &&) noexcept=default;
		template<class Func,class ... Args>
		void assign(Func &&func,Args &&...args)
		{
			exec_=CTask<Ret>{std::forward<Func>(func),std::forward<Args>(args)...};
			IThreadPoolItemBase::exec_(std::bind(&CTask<Ret>::operator(),&exec_));
		}
		inline Ret get()
		{
			const nTool::CScopeGuard<void()> sg{[this]{waiting_buf_->write(this);}};
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
		CThreadPoolItem_Ret& operator=(CThreadPoolItem_Ret &&) noexcept=default;
		~CThreadPoolItem_Ret()
		{
			if(is_running())
				wait();
		}
	};
}

#endif