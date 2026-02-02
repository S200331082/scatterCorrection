#ifndef PROGRESS_BAR_HH
#define PROGRESS_BAR_HH

#include <chrono>


using namespace std;

// 函数声明
void printProgressBar(int current, long long total);

void timeOutput(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);

double ParseValueWithUnit(const string& input);

#endif
