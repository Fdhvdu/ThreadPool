#include"CCSemaphore.h"
#include<atomic>
#include<condition_variable>
#include<mutex>
using namespace std;

namespace nTool
{
	struct CSemaphore::CSemaphoreImpl
	{
		size_t notActivity;
		const size_t count;
		condition_variable cv;
		mutex mut;
		CSemaphoreImpl(const size_t &);
		void signal();
		void wait();
	};

	CSemaphore::CSemaphoreImpl::CSemaphoreImpl(const size_t &count_)
		:notActivity(count_),count(count_){}

	void CSemaphore::CSemaphoreImpl::signal()
	{
		lock_guard<mutex> lock(mut);
		++notActivity;
		cv.notify_one();
	}

	void CSemaphore::CSemaphoreImpl::wait()
	{
		unique_lock<mutex> lock(mut);
		cv.wait(lock,[&](){return notActivity;});
		--notActivity;
	}

	CSemaphore::CSemaphore(const size_t &count)
		:p_(new CSemaphoreImpl(count)){}
	
	size_t CSemaphore::available() const noexcept
	{
		return p_->notActivity;
	}

	size_t CSemaphore::count() const noexcept
	{
		return p_->count;
	}

	void CSemaphore::signal()
	{
		p_->signal();
	}

	void CSemaphore::wait()
	{
		p_->wait();
	}

	CSemaphore::~CSemaphore()
	{
		delete p_;
	}

	struct CReaders_Writers_Problem::CReaders_Writers_ProblemImpl
	{
		atomic<size_t> count;
		CSemaphore use,wait;
		CReaders_Writers_ProblemImpl();
		void readBegin();
		void readEnd();
		void writeBegin();
	};

	CReaders_Writers_Problem::CReaders_Writers_ProblemImpl::CReaders_Writers_ProblemImpl()
		:count(0){}

	void CReaders_Writers_Problem::CReaders_Writers_ProblemImpl::readBegin()
	{
		wait.wait();
		if(++count==1)
			use.wait();
		wait.signal();
	}

	void CReaders_Writers_Problem::CReaders_Writers_ProblemImpl::readEnd()
	{
		if(!--count)
			use.signal();
	}

	void CReaders_Writers_Problem::CReaders_Writers_ProblemImpl::writeBegin()
	{
		wait.wait();
		use.wait();
		wait.signal();
	}

	CReaders_Writers_Problem::CReaders_Writers_Problem()
		:p_(new CReaders_Writers_ProblemImpl()){}

	void CReaders_Writers_Problem::readBegin()
	{
		p_->readBegin();
	}

	void CReaders_Writers_Problem::readEnd()
	{
		p_->readEnd();
	}

	void CReaders_Writers_Problem::writeBegin()
	{
		p_->writeBegin();
	}

	void CReaders_Writers_Problem::writeEnd()
	{
		p_->use.signal();
	}

	CReaders_Writers_Problem::~CReaders_Writers_Problem()
	{
		delete p_;
	}
}