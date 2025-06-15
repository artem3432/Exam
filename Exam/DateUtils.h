#pragma once
#include <string>
#include <ctime>

bool parseDate(const std::string&, std::tm&);
bool dateInPast(const std::string&);
