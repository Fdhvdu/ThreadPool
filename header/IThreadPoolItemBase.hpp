#ifndef ITHREADPOOLITEMBASE
#define ITHREADPOOLITEMBASE
#include<functional>	//function
#include<thread>	//thread::hardware_concurrency
#include"../../lib/header/tool/CUnique_obj.hpp"

namespace nThread
{
	struct IThreadPoolItemBase
	{
		using id=std::result_of_t<decltype(std::thread::hardware_concurrency)&()>;
		IThreadPoolItemBase();
		IThreadPoolItemBase(const IThreadPoolItemBase &)=delete;
		IThreadPoolItemBase(IThreadPoolItemBase &&) noexcept;
		id get_id() const noexcept;
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
		nTool::CUnique_obj<Impl> impl_;
	};
}

#endif