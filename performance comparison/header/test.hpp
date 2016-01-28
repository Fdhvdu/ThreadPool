#ifndef TEST
#define TEST
#include<thread>	//thread::hardware_concurrency
#include<type_traits>	//result_of

extern const std::result_of<decltype(std::thread::hardware_concurrency)&()>::type thread_count;
extern constexpr std::result_of<decltype(std::thread::hardware_concurrency)&()>::type constexpr_thread_count{8};
unsigned long fibonacci_10();
unsigned long fibonacci_47();
void iterative_100000();
void iterative_2000000000();

#endif