# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: release, x64, full optimization<br>
Iteration: 600000 (because of memory leak, test [test_henkel_ctor_and_dtor](../header/henkel.hpp) by yourself) and 10000000<br>
Thread Count: 12<br>
Boost: [Boost.lib](https://github.com/Fdhvdu/Boost.lib/tree/master/boost_1_60_0/msvc-14.0_release_64_static_multi)
# Result
	henkel
		each spends 420012 nanoseconds on test_henkel_ctor_and_dtor (600000 iteration)
		each spends 51897 nanoseconds on test_henkel_all_N (10000000 iteration)
		each spends 1803 nanoseconds on test_henkel_billion (10000000 iteration)
# Compare To Fdhvdu
About construction and destruction time, henkel's threadpool is faster than Fdhvdu's threadpool<br>
About waiting all job to complete, henkel's threadpool is slower than Fdhvdu's CThreadPool<br>
About given a number of jobs, henkel's threadpool is slower than Fdhvdu's CThreadPool<br><br>
henkel's threadpool can only compare to Fdhvdu's CThreadPool.<br>
Normally, we only need 1 threadpool (and we should only use 1 threadpool as much as possible to prevent memory leak), so

	use CThreadpool if the times of waiting all job to complete is bigger than 5 ((607034-420012)/(51897-19929))
	use CThreadpool if the number of jobs is bigger than 348 ((607034-420012)/(1803-1267))
