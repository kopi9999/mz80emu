#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <iostream>
#include <vector>
#include <string>

extern bool validateStringIsInteger(std::string, std::string);
extern bool validateStringIsBool(std::string, std::string);
extern bool validateVectorSize(std::vector<std::string>, size_t, std::string);
extern bool validateDerivedInterfaceCreated(std::vector<std::vector<std::vector<std::string>>>);
extern bool validateDerivedInterfaceHasValues(std::vector<std::vector<std::string>>);
extern bool validateIdExist(uint32_t, uint32_t, std::string);
extern bool validateValueDoesNotEqualZero(uint32_t, std::string);
extern bool validateValueEqualsNumberOfInstances(uint32_t, uint32_t, std::string);
extern bool validateVectorHasUniqueValues(std::vector<std::string>, std::string);

#endif