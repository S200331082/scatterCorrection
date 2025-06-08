#ifndef PROGRESS_BAR_HH
#define PROGRESS_BAR_HH

#include <chrono>

// 使用 std::chrono::high_resolution_clock 简化类型命名
using Clock = std::chrono::high_resolution_clock;

// 函数声明
void printProgressBar(int current, long long total);

void timeOutput(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);

#endif
