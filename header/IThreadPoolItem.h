#ifndef ITHREADPOOLITEM
#define ITHREADPOOLITEM
#include<functional>	//function
#include<memory>	//unique_ptr
#include<thread>	//thread::id
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	struct IThreadPoolItemExecutorBase;

	struct IThreadPoolItemBase
	{
		IThreadPoolItemBase();
		IThreadPoolItemBase(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase(IThreadPoolItemBase &&) noexcept;
		std::thread::id get_id() const noexcept;
		virtual bool is_running() const noexcept=0;
		virtual void wait() const=0;
		IThreadPoolItemBase& operator=(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase& operator=(IThreadPoolItemBase &&) noexcept;
		virtual ~IThreadPoolItemBase();
	protected:
		void exec_(const std::function<void()> &);
		void exec_(std::function<void()> &&);
	private:
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	};

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