#ifndef HENKEL
#define HENKEL
#include"test.hpp"

//how fast can a thread pool construct and destruct (test iteration times)
duration test_henkel_ctor_and_dtor();

//how fast can a thread pool complete N jobs, while N equals to the size of thread pool (test iteration times)
duration test_henkel_all_N();

//how fast can a thread pool complete iteration jobs, while the size of thread pool is thread_count or constexpr_thread_count
duration test_henkel_billion();

#endif