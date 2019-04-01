# Warnings
Since commit `468129863ec65c0b4ede02e8581bea682351a6d2`, I move ThreadPool to C++17. (To use `std::apply`.)<br>
In addition, **the rule of passing parameters to ThreadPool is different.**<br>
Unlike before, which uses `std::bind`, **ThreadPool will not copy anything right now.**<br>
All of ThreadPool does is forward (**no decay**).<br>
This means you have to copy arguments by yourself before passing it to ThreadPool.<br>
Below is demonstration,

	void test(int &i)
	{
		i=10;
	}

	int main()
	{
		int i(0);
		CThreadPool tp;
		tp.join(tp.add(test,i));

		//before commit f66048ed999aa1b50dc956c4a728ff565042d761
		cout<<i<<endl;	//0

		//since commit f66048ed999aa1b50dc956c4a728ff565042d761
		cout<<i<<endl;	//10
	}
# Contents
[Introduction](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#introduction)<br>
[Class view](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#class-view)<br>
[Performance comparison](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#performance-comparison)<br>
[Compiler](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#compiler)<br>
[How to compile](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#how-to-compile)<br>
[Compilation errors?](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#compilation-errors)<br>
[Tutorial](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#tutorial)<br>
[Future work](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#future-work)
# Introduction
This is a pure (which means it doesn't depend on any platform) and exception-safety C++ threadpool (so far, there is no standard threadpool in C++).<br>
The goal of this project is to provide a `fastest`, `beautiful` and `easy-to-use` C++ threadpool library.
# Class view
Two classes

	CThreadPool, including the member function
		thread_id    add(Func &&,Args &&...)
		void         add_and_detach(Func &&,Args &&...)
		size_type    empty() const noexcept
		void         join(thread_id)
		void         join_all()
		bool         joinable(thread_id) const
		size_type    size() const noexcept
		void         wait_until_all_usable() const
		
	CThreadPool_Ret, including the member function
		thread_id    add(Func &&,Args &&...)
		size_type    empty() const noexcept
		Ret          get(thread_id)
		size_type    size() const noexcept
		bool         valid(thread_id) const
		void         wait(thread_id) const
		void         wait_all() const
Use the CThreadPool_Ret when you want to get the return value of function.<br>
Use the CThreadPool when you don't care the return value of function.<br>
`CThreadPool::add_and_detach` is faster (very) than `CThreadPool_Ret::add`.
# Performance comparison
[progschj/ThreadPool](https://github.com/progschj/ThreadPool), see [Comparison](comparison/README.md#result).<br>
[Tyler-Hardin/thread_pool](https://github.com/Tyler-Hardin/thread_pool), see [Comparison](comparison/README.md#result).<br>
P.S. About [bilash/threadpool](https://github.com/bilash/threadpool), I don't want to test a C-like code.<br>
P.S. [nbsdx/ThreadPool](https://github.com/nbsdx/ThreadPool) cannot pass testing, see [README](comparison/nbsdx/README.md#warning).<br>
P.S. [philipphenkel/threadpool](https://github.com/philipphenkel/threadpool) cannot pass testing, see [README](comparison/philipphenkel/README.md#warning).<br>
P.S. [tghosgor/threadpool11](https://github.com/tghosgor/threadpool11) cannot pass testing, see [README](comparison/tghosgor/README.md#warning).<br>
P.S. [mtrebi/thread-pool](https://github.com/mtrebi/thread-pool) cannot pass testing, see [README](comparison/mtrebi/README.md#warning).<br>
See the [directory](comparison/) for more details.
# Compiler
	Visual Studio 2017 15.5.5
	g++ 7.2.1
	clang++ 5.0.1
# How to compile
You have to download [my lib](https://github.com/Fdhvdu/lib) first.<br>
The directory should be look like

	├── lib
	│   ├── header
	│   ├── LICENSE
	│   ├── README.md
	│   ├── src
	│   └── tutorial
	└── ThreadPool
	    ├── comparison
	    ├── header
	    ├── LICENSE
	    ├── README.md
	    ├── src
	    └── tutorial
Don't forget to compile lib/src/Scope_guard.cpp.
# Compilation errors?
See [How to compile](https://github.com/Fdhvdu/ThreadPool/blob/master/README.md#how-to-compile) or email me
# Tutorial
I provide [example.cpp](tutorial/example.cpp) and [example_ret.cpp](tutorial/example_ret.cpp) to help you understand how to use this powerful thread pool<br>
To use [example.cpp](tutorial/example.cpp):<br>

	g++ -std=c++17 tutorial/example.cpp src/* ../lib/src/Scope_guard.cpp
To use [example_ret.cpp](tutorial/example_ret.cpp):<br>

	g++ -std=c++17 tutorial/example_ret.cpp src/IThreadPoolItemBase.cpp ../lib/src/Scope_guard.cpp
# Future work
add a non-block version of `CThreadPool::add`<br>
work stealing
