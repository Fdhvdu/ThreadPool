#ifndef CTHREADPOOLITEM
#define CTHREADPOOLITEM
#include<memory>	//unique_ptr
#include"IThreadPoolItemBase.h"

namespace nThread
{
	struct IThreadPoolItemExecutorBase;

	class CThreadPoolItem:public IThreadPoolItemBase
	{
		std::unique_ptr<IThreadPoolItemExecutorBase> exec_;
	public:
		CThreadPoolItem()=default;
		CThreadPoolItem(const CThreadPoolItem &)=delete;
		CThreadPoolItem(CThreadPoolItem &&) noexcept=default;
		void assign(std::unique_ptr<IThreadPoolItemExecutorBase> &&);
		bool is_running() const noexcept override;
		void wait() const override;	//after calling this, CThreadPoolItem "should" be pushed into CThreadPool::Impl::waitingQue
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		CThreadPoolItem& operator=(CThreadPoolItem &&) noexcept=default;
		~CThreadPoolItem();
	};
}

#endif