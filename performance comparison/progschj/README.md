# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 10000000<br>
Thread Count: 12
# Result
	progschj
		each spends 532306 nanoseconds on test_progschj_ctor_and_dtor
		each spends 23359 nanoseconds on test_progschj_specific_N
		each spends 1988 nanoseconds on test_progschj_billion
# Compare To Fdhvdu
About construction and destruction time, progschj's threadpool is faster than Fdhvdu's threadpool<br>
About waiting specific job to complete, progschj's threadpool is slower than Fdhvdu's threadpool<br>
About given a number of jobs, progschj's threadpool is slower than Fdhvdu's CThreadPool<br><br>
In short, progschj only wins in the construction and destruction time.<br>
However, normally, we only need 1 threadpool, so

	use CThreadPool_Ret if the times of waiting specific job to complete is bigger than 7 ((592792-532306)/(23359-14921))
	use CThreadpool if the times of waiting specific job to complete is bigger than 23 ((607034-532306)/(23359-20187))
	use CThreadpool if the number of jobs is bigger than 103 ((607034-532306)/(1988-1267))