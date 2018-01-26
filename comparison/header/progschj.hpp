#ifndef PROGSCHJ
#define PROGSCHJ
#include"test.hpp"

//how fast can a thread pool construct and destruct (test iteration times)
nTest::duration test_progschj_ctor_and_dtor(unsigned long cnt);

//how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
nTest::duration test_progschj_specific_N(unsigned long cnt);

//how fast can a thread pool complete iteration jobs, while the size of thread pool is thread_count or constexpr_thread_count
nTest::duration test_progschj_job(unsigned long cnt);

#endif