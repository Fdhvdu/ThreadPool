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
		bool joinable() const noexcept;
		void wait();	//after calling this, CThreadPoolItem will be pushed into waitingQue_
						//it also means assign will be called in the subsequent (if has)
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		CThreadPoolItem& operator=(CThreadPoolItem &&) noexcept;
		~CThreadPoolItem();
	};
}

#endif