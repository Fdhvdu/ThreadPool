# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 10000000<br>
Thread Count: 12
# Result
	Fdhvdu's CThreadPool
		each spends 607034 nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor
		each spends 20187 nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N
		each spends 19929 nanoseconds on test_Fdhvdu_CThreadPool_join_all_N
		each spends 17194 nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N
		each spends 1267 nanoseconds on test_Fdhvdu_CThreadPool_detach_billion
	Fdhvdu's CThreadPool_Ret
		each spends 592792 nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor
		each spends 14921 nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N