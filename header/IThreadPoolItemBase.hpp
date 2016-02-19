#ifndef ITHREADPOOLITEMBASE
#define ITHREADPOOLITEMBASE
#include<functional>	//function
#include"../../lib/header/thread/CSmartThread.hpp"	//CSmartThread::id
#include"../../lib/header/tool/CPimpl.hpp"

namespace nThread
{
	struct IThreadPoolItemBase
	{
		IThreadPoolItemBase();
		IThreadPoolItemBase(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase(IThreadPoolItemBase &&) noexcept;
		CSmartThread::id get_id() const noexcept;
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
}

#endif