#include"CCSmartThread.h"
using namespace std;

namespace nTool
{
	CSmartThread::~CSmartThread()
	{
		thr_.join();
	}
}