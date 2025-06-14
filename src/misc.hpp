#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>
#include "main.hpp"

extern bool compareStringVectors(std::vector<std::string>, std::vector<std::string>);
extern std::vector<std::string> splitString(std::string, std::string);
extern std::vector<std::string> splitByWhitespace(std::string);
extern std::string toLower(std::string);
extern bool stringToBool(std::string);
extern std::string boolToString(bool);
extern void trim(std::string*);
extern void trimLeadingZeros(std::string*);
extern enum CrashCode convertErrorToCrash(enum Error);
extern void setCrashIfRunning(enum CrashCode*, enum CrashCode);

#endif
