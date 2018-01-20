#ifndef FDHVDU
#define FDHVDU
#include"test.hpp"

//how fast can a thread pool construct and destruct (test iteration times)
nTest::duration test_Fdhvdu_CThreadPool_ctor_and_dtor(unsigned long cnt);
nTest::duration test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor(unsigned long cnt);

//how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
nTest::duration test_Fdhvdu_CThreadPool_join_specific_N(unsigned long cnt);
nTest::duration test_Fdhvdu_CThreadPool_join_all_N(unsigned long cnt);
nTest::duration test_Fdhvdu_CThreadPool_detach_all_N(unsigned long cnt);
nTest::duration test_Fdhvdu_CThreadPool_Ret_specific_N(unsigned long cnt);

//how fast can a thread pool complete iteration jobs, while the size of thread pool is thread_count or constexpr_thread_count
nTest::duration test_Fdhvdu_CThreadPool_detach_job(unsigned long cnt);

#endif