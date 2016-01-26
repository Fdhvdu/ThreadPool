# Introduction
I provide example.cpp and example_ret.cpp to help you understand how to use

	CThreadPool, including the function
		thread_id	add(Func &&,Args &&...)
		void		add_and_detach(Func &&,Args &&...)
		std::size_t	available() const noexcept
		std::size_t	count() const noexcept
		void		join(thread_id)
		bool		joinable(thread_id) const noexcept
		void		join_all()
		thread_id	join_any()
		void 		wait_until_all_available() const
	CThreadPool_Ret, including the function
		thread_id	add(Func &&,Args &&...)
		std::size_t	available() const noexcept
		std::size_t	count() const noexcept
		Ret			get(thread_id)
		bool		valid(thread_id) const noexcept
		void		wait(thread_id) const
		void 		wait_all()
Use CThreadPool_Ret when you want to get the return value of function<br>
Use CThreadPool when you don't care the return value of function<br>
The performance of CThreadPool and CThreadPool_Ret is almost same<br>
But the CThreadPool::add_and_detach is faster (very) than the CThreadPool::add<br>
So, use the CThreadPool::add_and_detach when you can, and the CThreadPool::add when you have to
# Performance comparison
My threadpool is totally faster and more powerful than tghosgor/threadpool11 (https://github.com/tghosgor/threadpool11)<br>
See the directory (performance comparison/tghosgor/) for more details
# Why do I get compilation errors?
Does your compiler support C++14?<br>
Or, maybe you lost my lib files, here is link https://github.com/Fdhvdu/lib<br>
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
Or, maybe you forget to compile lib/src/CSemaphore.cpp and lib/src/CSmartThread.cpp<br>
The compiler I use is VC++ 2015 and gcc 5.2.0
# Tutorial
To use example.cpp:<br>
g++ -std=c++14 tutorial/example.cpp src/* ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp<br>
To use example_ret.cpp:<br>
g++ -std=c++14 tutorial/example_ret.cpp src/IThreadPoolItemBase.cpp ../lib/src/CSemaphore.cpp ../lib/src/CSmartThread.cpp
