#ifndef MTREBI
#define MTREBI
#include"test.hpp"

//how fast can a thread pool construct and destruct (test iteration times)
nTest::duration test_mtrebi_ctor_and_dtor(unsigned long cnt);

//how fast can a thread pool (really) construct and (really) destruct (test iteration times)
nTest::duration test_mtrebi_init_and_dtor(unsigned long cnt);

//how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
nTest::duration test_mtrebi_specific_N(unsigned long cnt);

//how fast can a thread pool complete iteration jobs, while the size of thread pool is thread_count or constexpr_thread_count
nTest::duration test_mtrebi_job(unsigned long cnt);

#endif