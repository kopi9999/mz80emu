#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>

extern bool compareStringVectors(std::vector<std::string>, std::vector<std::string>)
extern std::vector<std::string> splitString(std::string, std::string);
extern bool stringToBool(std::string);
extern void trim(std::string*);

#endif