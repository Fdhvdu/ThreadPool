#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include"../../lib/header/tool/CScopeGuard.h"
#include"../../lib/header/thread/CTask.h"
#include"../../lib/header/thread/CThreadQueue.h"
#include"IThreadPoolItemBase.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret:public IThreadPoolItemBase
	{
		CTask<Ret> exec_;
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> *waitingQue_;
	public:
		CThreadPoolItem_Ret(CThreadQueue<CThreadPoolItem_Ret<Ret>*> *);
		CThreadPoolItem_Ret(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret(CThreadPoolItem_Ret &&) noexcept=default;
		template<class Func,class ... Args>
		void assign(Func &&,Args &&...);
		inline Ret get()
		{
			const nTool::CScopeGuard<void()> sg{[=]{waitingQue_->emplace(this);}};
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
		~CThreadPoolItem_Ret();
	};
}

#include"CThreadPoolItem_Ret.cpp"

#endif