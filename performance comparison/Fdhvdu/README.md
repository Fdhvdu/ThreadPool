# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 10000000<br>
Thread Count: 12
# Result
	Fdhvdu's CThreadPool
		each spends 605400 nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor
		each spends 21197 nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N
		each spends 20678 nanoseconds on test_Fdhvdu_CThreadPool_join_all_N
		each spends 17862 nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N
		each spends 1333 nanoseconds on test_Fdhvdu_CThreadPool_detach_billion
	Fdhvdu's CThreadPool_Ret
		each spends 571449 nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor
		each spends 15233 nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N