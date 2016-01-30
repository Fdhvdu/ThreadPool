# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 1000000<br>
Thread Count: 12
# Result
	Fdhvdu's CThreadPool
		each spends 612259 nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor
		each spends 18842 nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N
		each spends 18478 nanoseconds on test_Fdhvdu_CThreadPool_join_all_N
		each spends 17144 nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N
		each spends 1317 nanoseconds on test_Fdhvdu_CThreadPool_detach_billion
	Fdhvdu's CThreadPool_Ret
		each spends 575251 nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor
		each spends 15245 nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N
