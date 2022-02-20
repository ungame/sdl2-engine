#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <string>

class Time
{
    public:
        static inline std::chrono::time_point<std::chrono::system_clock> Now() { return std::chrono::system_clock::now(); }
        static double Since(Time* t);

    public:
        Time() { _startedAt = Now(); }
        inline std::chrono::time_point<std::chrono::system_clock> StartedAt() { return _startedAt; }
    
    public:
        std::string String();

    private:
        std::chrono::time_point<std::chrono::system_clock> _startedAt;
};

#endif