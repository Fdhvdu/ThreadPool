#include"CCSmartThread.h"
using namespace std;

namespace nTool
{
	CSmartThread::~CSmartThread()
	{
		if(thr_.joinable())
			thr_.join();
	}
}