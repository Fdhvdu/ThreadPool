# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: full optimization<br>
Iteration: 10000000<br>
Thread Count: 12
# Result
	Fdhvdu's CThreadPool
		each spends 618721 nanoseconds on test_Fdhvdu_CThreadPool_ctor_and_dtor
		each spends 21065 nanoseconds on test_Fdhvdu_CThreadPool_join_specific_N
		each spends 20621 nanoseconds on test_Fdhvdu_CThreadPool_join_all_N
		each spends 18222 nanoseconds on test_Fdhvdu_CThreadPool_detach_all_N
		each spends 1345 nanoseconds on test_Fdhvdu_CThreadPool_detach_billion
	Fdhvdu's CThreadPool_Ret
		each spends 611227 nanoseconds on test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor
		each spends 15404 nanoseconds on test_Fdhvdu_CThreadPool_Ret_specific_N