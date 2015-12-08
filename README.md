# C++11 thread pool
This is a C++11 thread pool<br/>
I provide 2 example files (example.cpp and example_ret.cpp) to help you understand how to use

	CThreadPool, including the function
		add
		add_and_detach
		available
		count
		join
		joinable
		join_all
		join_any
	CThreadPool_Ret, including the function
		add
		available
		count
		get
		valid
		wait
<br/>
If you want to get the return value from function, then you should use CThreadPool_Ret<br/>
If you don't care the return value, then use CThreadPool is better<br/>
To make thread pool powerful, beautiful and maintainable, I discard some performance.
<br/><br/>
The compiler I use is VC++ 2015 and gcc 5.2.0.<br/>
To use example.cpp:<br/>
g++ -std=c++11 tutorial/example.cpp lib/CCThreadPool.h lib/CCThreadPool/CCThreadPoolCommun.h lib/CCThreadPool/CCThreadPoolItem.h lib/CCThreadPool/Thread/CCAsyncExecutor.h lib/CCThreadPool/Thread/CCSemaphore.cpp lib/CCThreadPool/Thread/CCSmartThread.h lib/CCThreadPool/Thread/CCSmartThread.cpp lib/CCThreadPool/Thread/CCThreadList.h lib/CCThreadPool/Thread/CCThreadQueue.h lib/CCThreadPool/Thread/Tool/CCID.cpp<br/>
To use example.cpp:<br/>
g++ -std=c++11 tutorial/example_ret.cpp lib/CCThreadPool_Ret.h lib/CCThreadPool/CCThreadPoolCommun.h lib/CCThreadPool/CCThreadPoolItem.h lib/CCThreadPool/Thread/CCAsyncExecutor.h lib/CCThreadPool/Thread/CCSemaphore.cpp lib/CCThreadPool/Thread/CCSmartThread.h lib/CCThreadPool/Thread/CCSmartThread.cpp lib/CCThreadPool/Thread/CCThreadList.h lib/CCThreadPool/Thread/CCThreadQueue.h lib/CCThreadPool/Thread/Tool/CCID.cpp
