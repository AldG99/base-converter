#ifndef BASEVALIDATOR_H
#define BASEVALIDATOR_H

#include <string>

class BaseValidator {
public:
    bool isValidNumber(const std::string& number, int base);
    bool isValidBase(int base);
    int getMinimumBase(const std::string& number);
    std::string getValidationError(const std::string& number, int base);

private:
    bool isValidDigit(char digit, int base);
    int charToDigit(char c);
};

#endif