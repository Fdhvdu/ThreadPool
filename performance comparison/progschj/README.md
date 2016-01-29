# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 1000000<br>
Thread Count: 12
# Result
	progschj
		each spends 515112 nanoseconds on test_progschj_ctor_and_dtor
		each spends 22867 nanoseconds on test_progschj_specific_N
		each spends 1908 nanoseconds on test_progschj_billion
# Compare To Fdhvdu
About construction and destruction time, progschj's threadpool is faster than Fdhvdu's threadpool<br>
About waiting specific job to complete, progschj's threadpool = Fdhvdu's CThreadPool, but slower than Fdhvdu's CThreadPool_Ret<br>
About given a number of jobs, progschj's threadpool is slower than Fdhvdu's CThreadPool
