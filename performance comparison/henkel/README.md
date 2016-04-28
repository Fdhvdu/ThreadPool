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
henkel's threadpool can only compare to Fdhvdu's CThreadPool. (because CThreadPool_Ret cannot use "all" function)<br>
About construction and destruction time, henkel's threadpool is slower than Fdhvdu's threadpool<br>
About waiting all job to complete, henkel's threadpool is slower than Fdhvdu's CThreadPool<br>
About given a number of jobs, henkel's threadpool is slower than Fdhvdu's CThreadPool<br><br>
As a result, you should use Fdhvdu's CThreadPool in any condition
