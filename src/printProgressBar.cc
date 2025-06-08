#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <chrono>

using namespace std;

void printProgressBar(int current, long long total)
{
    int barWidth = 50;
    double progress = static_cast<double>(current) / total;
    int pos = static_cast<int>(barWidth * progress);


    cout << "\r"
              << "event processing progress: [";
    for (int i = 0; i < barWidth; ++i)
        cout << (i < pos ? "█" : " ");
    cout << "] "
              << fixed << setprecision(1) << (progress * 100.0) << "%" << " " << flush;

    if (current == total)
        cout << endl;
}

void timeOutput(chrono::time_point<chrono::system_clock> start, chrono::time_point<chrono::system_clock> end)
{

    time_t start_time_t = chrono::system_clock::to_time_t(start);
    tm start_tm_buf;
    localtime_r(&start_time_t, &start_tm_buf);

    time_t end_time_t = chrono::system_clock::to_time_t(end);
    tm end_tm_buf;
    localtime_r(&end_time_t, &end_tm_buf);

    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    long long total_seconds = duration.count();
    // 转换为 h:m:s
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;
    // 格式化输出
    cout << "\n" << endl;
    cout << "--------------------Time Infomation-----------------------" << endl;
    cout << "Begin of Time: " << put_time(&start_tm_buf, "%Y-%m-%d %H:%M:%S") << endl;
    cout << "End of Time: " << put_time(&end_tm_buf, "%Y-%m-%d %H:%M:%S") << endl;

    cout << "Time-Consuming: "
                << setw(2) << setfill('0') << hours << ":"
                << setw(2) << setfill('0') << minutes << ":"
                << setw(2) << setfill('0') << seconds << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "\n" << endl;
}


map<string, double> unitMap = {
        {"nm", 1e-6}, {"um", 1e-3}, {"mm", 1.0}, 
        {"cm", 10.0}, {"m", 1e3},   {"km", 1e6}
    };

double ParseValueWithUnit(const string& input) {
    
    size_t starPos = input.find(" * ");
    if (starPos == string::npos) {
        cerr << "Error: Missing unit! Use format like '152.0 * mm'" << endl;
        return 0.0;
    }

    double value = atof(input.substr(0, starPos).c_str());
    string unit = input.substr(starPos + 1);

    if (unitMap.find(unit) == unitMap.end()) {
        cerr << "Error: Unknown unit '" << unit << "'" << endl;
        return 0.0;
    }

    return value * unitMap[unit]; // 转换为Geant4内部单位（mm）
}
