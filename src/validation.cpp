#include "validation.hpp"
#include "misc.hpp"

using namespace std;

bool validateStringIsInteger(string str, string loadingStep) {
    string digits = "0123456789";
    for (int i=0; i<str.length(); i++) {
        if (digits.find(str[i]) == string::npos) {
            cout << "ERROR: Value \"" << str << "\" is not an integer (\"" << loadingStep << "\" section of config.txt).\n";
            return false;
        }
    }
    return true;
}

bool validateStringIsBool(string str, string loadingStep) {
    if (toLower(str) != "true" && toLower(str) != "false") {
        cout << "ERROR: Value \"" << str << "\" is not a boolean value (\"" << loadingStep << "\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateVectorSize(vector<string> vec, size_t size, string loadingStep) {
    if (vec.size() != size) {
        cout << "ERROR: Invalid number of values - \"";
        for (int i=0; i<vec.size()-1; i++) {
            cout << vec[i] << " ";
        }
        cout << vec[vec.size()-1] << "\" - expected " << size << " values (\"" << loadingStep << "\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateDerivedInterfaceCreated(vector<vector<vector<string>>> loadedDerivedInterfaces) {
    if (loadedDerivedInterfaces.size() == 0) {
        cout << "ERROR: New derived interface has not been created, but its values were specified (\"Derived interfaces\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateDerivedInterfaceHasValues(vector<vector<string>> derivedInterface) {
    if (derivedInterface.size() == 0) {
        cout << "ERROR: New derived interface has been created, but its values were not specified (\"Derived interfaces\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateIdExist(uint32_t id, uint32_t maxId, string loadingStep) {
    if (id > maxId) {
        cout << "ERROR: Specified ID \"" << id << "\" does not exist (\"" << loadingStep << "\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateValueDoesNotEqualZero(uint32_t value, string loadingStep) {
    if (value == 0) {
        cout << "ERROR: Specified value equals zero (\"" << loadingStep << "\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateValueEqualsNumberOfInstances(uint32_t value, uint32_t numberOfInstances, string loadingStep) {
    if (value != numberOfInstances) {
        cout << "ERROR: Number of values in section does not equal number of module instances (\"" << loadingStep << "\" section of config.txt).\n";
        return false;
    }
    return true;
}

bool validateVectorHasUniqueValues(vector<string> vec, string loadingStep) {
    for (size_t i=0; i<vec.size(); ++i) {
        trimLeadingZeros(&vec[i]);
        for (size_t j=0; j<i; ++j) {
            if (vec[i] == vec[j]) {
                cout << "ERROR: Values in section are not unique (\"" << loadingStep << "\" section of config.txt).\n";
                return false;
            }
        }
    }
    return true;
}