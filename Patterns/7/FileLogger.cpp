#include "FileLogger.h"
#include <chrono>
#include <iostream>

std::string FileLogger::GetCurDateTime() {
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
    return std::string(buf);
}

void FileLogger::Write(const std::string& str) {
    if (logOut.is_open())
    {
        logOut << GetCurDateTime() << " - " << str << std::endl;
    }
}

void FileLogger::Write(const std::string& str, int n) {
    if (logOut.is_open())
    {
        logOut << GetCurDateTime() << " - " << str << n << std::endl;
    }
}

void FileLogger::Write(const std::string& str, double d) {
    if (logOut.is_open())
    {
        logOut << GetCurDateTime() << " - " << str << d << std::endl;
    }
}