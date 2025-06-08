#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>



void printProgressBar(int current, long long total)
{
    int barWidth = 50;
    double progress = static_cast<double>(current) / total;
    int pos = static_cast<int>(barWidth * progress);


    std::cout << "\r"
              << "event processing progress: [";
    for (int i = 0; i < barWidth; ++i)
        std::cout << (i < pos ? "█" : " ");
    std::cout << "] "
              << std::fixed << std::setprecision(1) << (progress * 100.0) << "%" << " " << std::flush;

    if (current == total)
        std::cout << std::endl;
}

void timeOutput(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end)
{

    std::time_t start_time_t = std::chrono::system_clock::to_time_t(start);
    std::tm start_tm_buf;
    localtime_r(&start_time_t, &start_tm_buf);

    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
    std::tm end_tm_buf;
    localtime_r(&end_time_t, &end_tm_buf);

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    long long total_seconds = duration.count();
    // 转换为 h:m:s
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;
    // 格式化输出
    std::cout << "\n" << std::endl;
    std::cout << "--------------------Time Infomation-----------------------" << std::endl;
    std::cout << "Begin of Time: " << std::put_time(&start_tm_buf, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "End of Time: " << std::put_time(&end_tm_buf, "%Y-%m-%d %H:%M:%S") << std::endl;

    std::cout << "Time-Consuming: "
                << std::setw(2) << std::setfill('0') << hours << ":"
                << std::setw(2) << std::setfill('0') << minutes << ":"
                << std::setw(2) << std::setfill('0') << seconds << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "\n" << std::endl;
}