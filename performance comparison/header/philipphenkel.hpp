#ifndef PHILIPPHENKEL
#define PHILIPPHENKEL
#include"test.hpp"

//how fast can a thread pool construct and destruct (test iteration times)
duration test_philipphenkel_ctor_and_dtor(unsigned long cnt);

//how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
duration test_philipphenkel_all_N(unsigned long cnt);

//how fast can a thread pool complete iteration jobs, while the size of thread pool is thread_count or constexpr_thread_count
duration test_philipphenkel_job(unsigned long cnt);

#endif