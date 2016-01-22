#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<memory>	//unique_ptr
#include"CThreadPoolItemExecutor_Ret.h"
#include"IThreadPoolCommun.h"
#include"IThreadPoolItem.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret:public IThreadPoolItemBase
	{
		std::unique_ptr<IThreadPoolCommunBase> commun_;	//communicate with CThreadPool
		std::unique_ptr<CThreadPoolItemExecutor_Ret<Ret>> exec_;
	public:
		CThreadPoolItem_Ret()=default;
		CThreadPoolItem_Ret(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret(CThreadPoolItem_Ret &&) noexcept=default;
		template<class Func,class ... Args>
		void assign(Func &&,Args &&...);
		inline Ret get()
		{
			return exec_->get();
		}
		bool is_running() const noexcept override
		{
			return exec_->is_running();
		}
		void setCommun(std::unique_ptr<IThreadPoolCommunBase> &&commun)
		{
			commun_=std::move(commun);
		}
		void wait() override
		{
			exec_->wait();
		}
		CThreadPoolItem_Ret& operator=(const CThreadPoolItem_Ret &)=delete;
		CThreadPoolItem_Ret& operator=(CThreadPoolItem_Ret &&) noexcept=default;
		~CThreadPoolItem_Ret();
	};
}

#include"CThreadPoolItem_Ret.cpp"

#endif