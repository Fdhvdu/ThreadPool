#ifndef CSEMAPHORE
#define CSEMAPHORE
#include<cstddef>
#include"Tool/CPimpl.h"

namespace nTool
{
	class CSemaphore
	{
		class Impl;
		CPimpl<Impl> impl_;
	public:
		CSemaphore(std::size_t);
		CSemaphore(const CSemaphore &)=delete;
		std::size_t count() const noexcept;
		void signal();
		void wait();
		CSemaphore& operator=(const CSemaphore &)=delete;
		~CSemaphore();
	};

	class CReaders_Writers_Problem	//no as powerful as std::shared_mutex
	{
		class Impl;
		CPimpl<Impl> impl_;
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