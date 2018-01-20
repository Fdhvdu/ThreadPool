#ifndef TEST
#define TEST
#include<thread>	//thread::hardware_concurrency
#include<type_traits>
#include"../../../lib/header/tool/CChrono_timer.hpp"

using duration=decltype(nTool::CChrono_timer().duration_nanoseconds());

constexpr unsigned long iteration(10000000);
constexpr std::result_of_t<decltype(std::thread::hardware_concurrency)&()> thread_count(16);

inline void empty() noexcept{}

#endif