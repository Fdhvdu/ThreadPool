# C++14 thread pool
I provide example.cpp and example_ret.cpp to help you understand how to use

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
If you want to get the return value from function, you should use CThreadPool_Ret<br/>
If you don't care the return value, use CThreadPool is better<br/>
To use threadpool, you also have to download my lib (https://github.com/Fdhvdu/lib)<br/>
The directory should look like

	-lib----------header
	|            -src
	|            -tutorial
	|            -LICENSE
	|            -README.md
	|
	-ThreadPool---header
	             -src
	             -tutorial
	             -LICENSE
	             -README.md
<br/><br/>The compiler I use is VC++ 2015 and gcc 5.2.0<br/><br/><br/>
Tutorial:<br/>
To use example.cpp:<br/>
g++ -std=c++14 tutorial/example.cpp src/* ../lib/src/CId.cpp ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp
To use example_ret.cpp:<br/>
g++ -std=c++14 tutorial/example_ret.cpp src/CThreadPoolCommun.cpp ../lib/src/CId.cpp ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp
