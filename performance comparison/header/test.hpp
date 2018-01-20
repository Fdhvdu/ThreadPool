#ifndef TEST
#define TEST
#include<thread>	//thread::hardware_concurrency
#include<type_traits>
#include"../../../lib/header/tool/CChrono_timer.hpp"

using duration=decltype(nTool::CChrono_timer().duration_nanoseconds());

constexpr std::result_of_t<decltype(std::thread::hardware_concurrency)&()> thread_count(16);

constexpr void empty() noexcept{}

#endif