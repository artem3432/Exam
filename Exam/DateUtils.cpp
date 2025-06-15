#include "DateUtils.h"
#include <cstdlib>

bool parseDate(const std::string& iso, std::tm& out)
{
    if (iso.size() != 10 || iso[4] != '-' || iso[7] != '-') return false;
    int y = std::atoi(iso.substr(0, 4).c_str());
    int m = std::atoi(iso.substr(5, 2).c_str());
    int d = std::atoi(iso.substr(8, 2).c_str());
    if (y < 1900 || m < 1 || m>12 || d < 1 || d>31) return false;

    out = {};
    out.tm_year = y - 1900;
    out.tm_mon = m - 1;
    out.tm_mday = d;
    return true;
}

bool dateInPast(const std::string& iso)
{
    std::tm dt{};
    if (!parseDate(iso, dt)) return false;
    auto now = std::time(nullptr);
    std::tm nowTm{};
    if (localtime_s(&nowTm, &now) != 0) return false; 
    return std::difftime(std::mktime(&nowTm), std::mktime(&dt)) > 0;
}
