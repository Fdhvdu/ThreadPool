# Contents
[Introduction](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#introduction)<br>
[Class view](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#class-view)<br>
[Performance comparison](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#performance-comparison)<br>
[Compiler](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#compiler)<br>
[How to compile](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#how-to-compile)<br>
[About compilation errors](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#about-compilation-errors)<br>
[Tutorial](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#tutorial)<br>
[Future work](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#future-work)
# Introduction
This is a pure C++ (which means it doesn't depend on any platform) and exception-safety (such as bad_alloc) threadpool (so far, there is no standard threadpool in C++).<br>
The goal of this project is to provide a *fastest*, *beautiful* and *easy-to-use* C++ threadpool library.
# Class view
Two classes

	CThreadPool, including the member function
		thread_id	add(Func &&,Args &&...)
		void		add_and_detach(Func &&,Args &&...)
		size_type	empty() const noexcept
		void		join(thread_id)
		void		join_all()
		bool		joinable(thread_id) const
		size_type	size() const noexcept
		void 		wait_until_all_usable() const
		
	CThreadPool_Ret, including the member function
		thread_id	add(Func &&,Args &&...)
		size_type	empty() const noexcept
		Ret			get(thread_id)
		size_type	size() const noexcept
		bool		valid(thread_id) const
		void		wait(thread_id) const
		void 		wait_all() const
Use the CThreadPool_Ret when you want to get the return value of function.<br>
Use the CThreadPool when you don't care the return value of function.<br>
The CThreadPool::add_and_detach is faster (very) than the CThreadPool_Ret::add.
# Performance comparison
github search "threadpool language:C++"<br><br>
About [progschj/ThreadPool](https://github.com/progschj/ThreadPool), see [Compare To Fdhvdu](performance comparison/progschj/README.md#compare-to-fdhvdu).<br>
About [henkel/threadpool](https://github.com/henkel/threadpool), somehow, it has memory leak, see [README](performance comparison/henkel/README.md).<br><br>
P.S. [bilash/threadpool](https://github.com/bilash/threadpool) needs POSIX support, however, I don't have Unix system. So, there is no comparison result.<br>
P.S. [nbsdx/ThreadPool](https://github.com/nbsdx/ThreadPool) is not thread-safe (as far as 24 commits).<br>
P.S. [tghosgor/threadpool11](https://github.com/tghosgor/threadpool11) is not thread-safe (as far as 177 commits and 11 releases).<br>
See the [directory](performance comparison/) for more details.
# Compiler
VC++ 2015 (update 2)<br>
or any compiler which supports C++14
# How to compile
You have to download [my lib](https://github.com/Fdhvdu/lib)<br>
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
Don't forget to add compile lib/src/CScopeGuard.cpp and lib/src/CSemaphore.cpp.
# About compilation errors
Q: My compiler doesn't support C++14<br>
A: Get a newer compiler version, such as GCC 5.3.0 or VC++ 14.2 (inside Visual Studio Community 2015 Update 2)<br><br>
Q: Other problems<br>
A: See [How to compile](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#how-to-compile)
# Tutorial
I provide [example.cpp](tutorial/example.cpp) and [example_ret.cpp](tutorial/example_ret.cpp) to help you understand how to use this powerful thread pool<br>
To use [example.cpp](tutorial/example.cpp):<br>
g++ -std=c++14 tutorial/example.cpp src/* ../lib/src/CScopeGuard.cpp ../lib/src/CSemaphore.cpp<br>
To use [example_ret.cpp](tutorial/example_ret.cpp):<br>
g++ -std=c++14 tutorial/example_ret.cpp src/IThreadPoolItemBase.cpp ../lib/src/CScopeGuard.cpp ../lib/src/CSemaphore.cpp
# Future work
work stealing
