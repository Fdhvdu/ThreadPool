#ifndef __CCSemaphore
#define __CCSemaphore
#include<cstddef>

namespace nTool
{
	class CSemaphore
	{
		struct CSemaphoreImpl;
		CSemaphoreImpl *p_;
	public:
		CSemaphore(const std::size_t);
		CSemaphore(const CSemaphore &)=delete;
		std::size_t count() const noexcept;
		void signal();
		void wait();
		CSemaphore& operator=(const CSemaphore &)=delete;
		~CSemaphore();
	};

	class CReaders_Writers_Problem
	{
		struct CReaders_Writers_ProblemImpl;
		CReaders_Writers_ProblemImpl *p_;
	public:
		CReaders_Writers_Problem();
		CReaders_Writers_Problem(const CReaders_Writers_Problem &)=delete;
		void readBegin();
		void readEnd();
		void writeBegin();
		void writeEnd();
		CReaders_Writers_Problem& operator=(const CReaders_Writers_Problem &)=delete;
		~CReaders_Writers_Problem();
	};
}

#endif