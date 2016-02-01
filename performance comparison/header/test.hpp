#ifndef TEST
#define TEST
#include<thread>	//thread::hardware_concurrency
#include"../../../lib/header/tool/CChrono_timer.hpp"

typedef decltype(nTool::CChrono_timer().duration_nanoseconds()) duration;

constexpr unsigned long iteration{10000000};
constexpr std::result_of<decltype(std::thread::hardware_concurrency)&()>::type thread_count{12};

inline void empty(){};

#endif