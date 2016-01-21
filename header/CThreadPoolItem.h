#ifndef CTHREADPOOLITEM
#define CTHREADPOOLITEM
#include<memory>	//unique_ptr
#include<thread>	//thread::id
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	struct IThreadPoolItemExecutorBase;

	class CThreadPoolItem
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItem();
		CThreadPoolItem(const CThreadPoolItem &)=delete;
		CThreadPoolItem(CThreadPoolItem &&) noexcept;
		void assign(std::unique_ptr<IThreadPoolItemExecutorBase> &&);
		std::thread::id get_id() const noexcept;
		bool is_running() const noexcept;
		bool joinable() const noexcept;	//dynamic_cast inside
		void wait();	//after calling this, CThreadPoolItem "should" be pushed into CThreadPool::Impl::waitingQue
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		CThreadPoolItem& operator=(CThreadPoolItem &&) noexcept;
		~CThreadPoolItem();
	};
}

#endif