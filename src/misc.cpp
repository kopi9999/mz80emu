#include "misc.hpp"

vector<string> splitString(string str, string delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

bool stringToBool(string str) {
    if (str == "true") {
        return true;
    }
    return false;
}

void trim(string* str) {
    int i = 0;
    while (str[0][i] == ' ' || str[0][i] == '\n' || str[0][i] == '\r' || str[0][i] == '\t') {
        i++;
    }
    *str = str->substr(i);
    i = 0;
    while (str[0][i] == ' ' || str[0][i] == '\n' || str[0][i] == '\r' || str[0][i] == '\t') {
        i--;
    }
    *str = str->substr(0, str->length() - i);
}