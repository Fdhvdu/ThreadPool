# Contents
[Introduction](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#introduction)<br>
[Performance comparison](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#performance-comparison)<br>
[Compiler](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#compiler)<br>
[Tutorial](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#tutorial)<br>
[About compilation errors](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#about-compilation-errors)<br>
[Future work](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#future-work)
# Introduction
Two classes

	CThreadPool, including the member function
		thread_id	add(Func &&,Args &&...)
		void		add_and_detach(Func &&,Args &&...)
		size_type	available() const noexcept
		void		join(thread_id)
		void		join_all()
		thread_id	join_any()
		bool		joinable(thread_id) const noexcept
		size_type	size() const noexcept
		void 		wait_until_all_available() const
		
	CThreadPool_Ret, including the member function
		thread_id	add(Func &&,Args &&...)
		size_type	available() const noexcept
		Ret			get(thread_id)
		size_type	size() const noexcept
		bool		valid(thread_id) const noexcept
		void		wait(thread_id) const
		void 		wait_all() const
Use the CThreadPool_Ret when you want to get the return value of function.<br>
Use the CThreadPool when you don't care the return value of function.<br>
The CThreadPool::add_and_detach is faster (very) than the CThreadPool_Ret::add.<br>
But the CThreadPool_Ret::add is faster than the CThreadPool::add.
# Performance comparison
About [progschj/ThreadPool](https://github.com/progschj/ThreadPool), see [Compare To Fdhvdu](performance comparison/progschj/README.md#compare-to-fdhvdu).<br>
About [henkel/threadpool](https://github.com/henkel/threadpool), somehow, it has memory leak, see [README](performance comparison/henkel/README.md).<br><br>
P.S. [bilash/threadpool](https://github.com/bilash/threadpool) needs POSIX support, however, I don't have Unix system. So, there is no comparison result.<br>
P.S. [nbsdx/ThreadPool](https://github.com/nbsdx/ThreadPool) is not thread-safe (as far as 24 commits).<br>
P.S. [tghosgor/threadpool11](https://github.com/tghosgor/threadpool11) is not thread-safe (as far as 11 releases).<br>
See the [directory](performance comparison/) for more details.
# Compiler
VC++ 2015 and GCC 5.2.0.
# Tutorial
I provide [example.cpp](tutorial/example.cpp) and [example_ret.cpp](tutorial/example_ret.cpp) to help you understand how to use this powerful thread pool<br>
To use [example.cpp](tutorial/example.cpp):<br>
g++ -std=c++14 tutorial/example.cpp src/* ../lib/src/CScopeGuard.cpp ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp<br>
To use [example_ret.cpp](tutorial/example_ret.cpp):<br>
g++ -std=c++14 tutorial/example_ret.cpp src/IThreadPoolItemBase.cpp ../lib/src/CScopeGuard.cpp ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp
# About compilation errors
Does your compiler support C++14? If not, why don't you use Visual Studio Community 2015 or GCC 5.2.0?<br>
Or, maybe you lost my lib files, [here is link](https://github.com/Fdhvdu/lib)<br>
The directory should be look like

	-ThreadPool---header
	|            -performance comparison
	|            -src
	|            -tutorial
	|            -LICENSE
	|            -README.md
	|
	-lib----------header
	             -src
	             -tutorial
	             -LICENSE
	             -README.md
Or, maybe you forget to compile lib/src/CScopeGuard.cpp, lib/src/CSemaphore.cpp and lib/src/CSmartThread.cpp
# Future work
exception safety<br>
work stealing
