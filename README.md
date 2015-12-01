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
Becides, CThreadPool provides more functions then CThreadPool_Ret<br/>
(Actually, they use same components)<br/><br/><br/>
The compiler I use is VC++ 2015 and gcc 5.2.0.
