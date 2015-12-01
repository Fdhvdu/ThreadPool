#include"CCSmartThread.h"
using namespace std;

namespace nTool
{
	CSmartThread::CSmartThread(){}

	CSmartThread& CSmartThread::operator=(CSmartThread &&rVal) noexcept
	{
		swap(thr_,rVal.thr_);
		return *this;
	}

	CSmartThread::~CSmartThread()
	{
		if(thr_.joinable())
			thr_.join();
	}
}