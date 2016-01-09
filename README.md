# C++14 thread pool
This is a C++14 thread pool<br/>
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
		wait_until_all_available
	CThreadPool_Ret, including the function
		add
		available
		count
		get
		valid
		wait
<br/>
If you want to get the return value from function, you should use CThreadPool_Ret<br/>
If you don't care the return value, use CThreadPool is better
<br/><br/>
The compiler I use is VC++ 2015 and gcc 5.2.0<br/>
To use example.cpp:<br/>
g++ -std=c++14 tutorial/example.cpp lib/CThreadPool.cpp lib/CThreadPool/CThreadPoolCommun.cpp lib/CThreadPool/CThreadPoolItem.cpp lib/CThreadPool/Thread/CSemaphore.cpp lib/CThreadPool/Thread/CSmartThread.cpp lib/CThreadPool/Thread/Tool/CId.cpp<br/>
To use example_ret.cpp:<br/>
g++ -std=c++14 tutorial/example_ret.cpp lib/CThreadPool/CThreadPoolCommun.cpp lib/CThreadPool/Thread/CSemaphore.cpp lib/CThreadPool/Thread/CSmartThread.cpp lib/CThreadPool/Thread/Tool/CId.cpp