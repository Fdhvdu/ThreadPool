# What is test function?
First, the execution time of function is same (no matter what thread pool you use).<br>
So, the function should be short, and what we need to do is test

	how fast can a thread pool construct and destruct (test iteration times)
	how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
		-test by wait_single (if has)
		-test by wait_all (if has)
	how fast can a thread pool complete iteration jobs
# The version I use
[progschj/ThreadPool](https://github.com/progschj/ThreadPool) commit: 9a42ec1329f259a5f4881a291db1dcb8f2ad9040<br>
[nbsdx/ThreadPool](https://github.com/nbsdx/ThreadPool) commit: 08905cfc36d8bae308488c56c505e9aefa2bcb78<br>
[philipphenkel/threadpool](https://github.com/philipphenkel/threadpool) commit: bb6da2e40eacb3358e5c648f2242faf307a54268<br>
[tghosgor/threadpool11](https://github.com/tghosgor/threadpool11) commit: 8bfcf6afbdb60b2dc7976762f45fd424de06097a<br>
[Tyler-Hardin/thread_pool](https://github.com/Tyler-Hardin/thread_pool) commit: 0b1eff9817d89266232489cd250d24841e147dc3
# Environment
Motherboard: ASUS TUF X299 MARK 1<br>
CPU: Intel(R) Core(TM) i7-7820X<br>
Memory: 16 GiB DDR4 2400 MHz * 2<br>
OS: Linux 4.14.15-1-ARCH #1 SMP PREEMPT<br>
Compiler: gcc version 7.2.1 20180116<br>
boost version: 1.66.0-1
# Result
First, I will not compare nbsdx, philipphenkel and tghosgor. Because their works has potential bug.<br>
You can get the following statistic in their directory. (out_100000)<br>
Construct and destruct time:

	progschj                 with 547785 ns
	Tyler-Hardin             with 620148 ns
	Fdhvdu's CThreadPool_Ret with 956302 ns
	Fdhvdu's CThreadPool     with 959417 ns
Wait until specific job completes:

	Fdhvdu's CThreadPool_Ret with 39995 ns
	Fdhvdu's CThreadPool     with 40560 ns
	progschj                 with 51185 ns
	Tyler-Hardin             with 72200 ns
Launch a large number of jobs and wait until all jobs complete:

	Fdhvdu's CThreadPool     with 2550 ns
	progschj                 with 3107 ns
	Tyler-Hardin             with 4638 ns
Use Fdhvdu's CThreadPool in most cases.<br>
Use progschj only if you want to construct a thread pool multiple times.