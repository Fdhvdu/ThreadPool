#ifndef CTHREADPOOLITEM
#define CTHREADPOOLITEM
#include<functional>	//function
#include<memory>	//unique_ptr
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	class CThreadPoolCommun;

	class CThreadPoolItem
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItem();
		CThreadPoolItem(const CThreadPoolItem &)=delete;
		void assign(std::function<void()> &&);
		void assign_and_detach(std::function<void()> &&);
		void join();	//after calling this, CThreadPoolItem will be pushed into waitingQue_
						//it also means assign will be called in the subsequent (if has)
		bool joinable() const noexcept;
		void setCommun(std::unique_ptr<CThreadPoolCommun> &&);
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		~CThreadPoolItem();
	};
}

#endif