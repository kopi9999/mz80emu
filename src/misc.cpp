#include "misc.hpp"

using namespace std;

bool compareStringVectors(vector<string> vec1, vector<string> vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}

vector<string> splitString(string str, string delimiter) {
    if (str == "" || delimiter == "") {
        return {};
    }

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

string toLower(string str) {
    string result = "";
    for (size_t i = 0; i < str.length(); ++i) {
        result += tolower(str[i]);
    }
    return result;
}

bool stringToBool(string str) {
    if (toLower(str) == "true") {
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