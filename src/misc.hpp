#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>

using namespace std;

extern vector<string> splitString(string str, string delimeter);
extern bool stringToBool(string str);
extern void trim(string* str);

#endif