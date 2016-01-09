#include"CSemaphore.h"
#include<atomic>
#include<condition_variable>
#include<mutex>
using namespace std;

namespace nTool
{
	class CSemaphore::Impl
	{
		size_t count_;
		condition_variable cv_;
		mutex mut_;
	public:
		Impl(size_t);
		inline size_t count() const noexcept
		{
			return count_;
		}
		void signal();
		void wait();
	};

	CSemaphore::Impl::Impl(const size_t count)
		:count_{count}{}

	void CSemaphore::Impl::signal()
	{
		lock_guard<mutex> lock{mut_};
		++count_;
		cv_.notify_one();
	}

	void CSemaphore::Impl::wait()
	{
		unique_lock<mutex> lock{mut_};
		cv_.wait(lock,[&]{return count();});
		--count_;
	}

	CSemaphore::CSemaphore(const size_t count)
		:impl_{count}{}

	size_t CSemaphore::count() const noexcept
	{
		return impl_.get().count();
	}

	void CSemaphore::signal()
	{
		impl_.get().signal();
	}

	void CSemaphore::wait()
	{
		impl_.get().wait();
	}

	CSemaphore::~CSemaphore(){}

	class CReaders_Writers_Problem::Impl
	{
		atomic<size_t> count_;
		CSemaphore use_,wait_,writing_;
	public:
		Impl();
		void readBegin();
		void readEnd();
		void writeBegin();
		inline void writeEnd()
		{
			use_.signal();
		}
	};

	CReaders_Writers_Problem::Impl::Impl()
		:count_{0},use_{1},wait_{1},writing_{1}{}

	void CReaders_Writers_Problem::Impl::readBegin()
	{
		wait_.wait();
		writing_.wait();	//must
		if(++count_==1)
			use_.wait();
		wait_.signal();
		writing_.signal();	//can this line put prior to wait_.signal()?
	}

	void CReaders_Writers_Problem::Impl::readEnd()
	{
		//writing_.wait();	//atomic is enough, I think
		if(!--count_)
			use_.signal();
		//writing_.signal();	//atomic is enough, I think
	}

	void CReaders_Writers_Problem::Impl::writeBegin()
	{
		wait_.wait();
		use_.wait();
		wait_.signal();
	}

	CReaders_Writers_Problem::CReaders_Writers_Problem(){}

	void CReaders_Writers_Problem::readBegin()
	{
		impl_.get().readBegin();
	}

	void CReaders_Writers_Problem::readEnd()
	{
		impl_.get().readEnd();
	}

	void CReaders_Writers_Problem::writeBegin()
	{
		impl_.get().writeBegin();
	}

	void CReaders_Writers_Problem::writeEnd()
	{
		impl_.get().writeEnd();
	}

	CReaders_Writers_Problem::~CReaders_Writers_Problem(){}
}