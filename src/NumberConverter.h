#ifndef NUMBERCONVERTER_H
#define NUMBERCONVERTER_H

#include <string>
#include <vector>

class NumberConverter {
public:
    std::string decimalToBase(int decimal, int base);
    int baseToDecimal(const std::string& number, int base);
    std::string convertBetweenBases(const std::string& number, int fromBase, int toBase);
    bool isValidNumber(const std::string& number, int base);
    std::vector<std::string> getConversionSteps(int decimal, int targetBase);

private:
    char digitToChar(int digit);
    int charToDigit(char c);
};

#endif