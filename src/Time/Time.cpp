#include "Time.hpp"
#include <chrono>
#include <string>
#include <ctime>

double Time::Since(Time* t)
{
    std::chrono::duration<double> elapsed = Now() - t->StartedAt();

    return elapsed.count();
}

std::string Time::String()
{
    std::time_t tt = std::chrono::system_clock::to_time_t(_startedAt);
    auto lt = localtime(&tt);
    char timeStr[] = {0};
    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", lt);
    return std::string(timeStr);
}