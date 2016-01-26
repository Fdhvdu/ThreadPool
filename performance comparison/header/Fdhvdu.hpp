#ifndef FDHVDU
#define FDHVDU
#include"test.hpp"

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Detach_fibonacci_10();
void test_Fdhvdu_CThreadPool_Detach_fibonacci_47();
//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Detach_iterative_100000();
void test_Fdhvdu_CThreadPool_Detach_iterative_2000000000();
//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Join_fibonacci_10();
void test_Fdhvdu_CThreadPool_Join_fibonacci_47();
//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Join_iterative_100000();
void test_Fdhvdu_CThreadPool_Join_iterative_2000000000();
//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Ret_fibonacci_10();
void test_Fdhvdu_CThreadPool_Ret_fibonacci_47();
//execute 100000 times
//to test how fast the threadpool can take a new job and execute
void test_Fdhvdu_CThreadPool_Ret_iterative_100000();
void test_Fdhvdu_CThreadPool_Ret_iterative_2000000000();

#endif