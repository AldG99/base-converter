#include "NumberConverter.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <cmath>

char NumberConverter::digitToChar(int digit) {
    if (digit < 10) {
        return '0' + digit;
    }
    return 'A' + (digit - 10);
}

int NumberConverter::charToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    throw std::invalid_argument("Invalid character");
}

std::string NumberConverter::decimalToBase(int decimal, int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Base must be between 2 and 36");
    }
    
    if (decimal == 0) {
        return "0";
    }
    
    std::string result;
    bool negative = decimal < 0;
    decimal = abs(decimal);
    
    while (decimal > 0) {
        result += digitToChar(decimal % base);
        decimal /= base;
    }
    
    if (negative) {
        result += '-';
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

int NumberConverter::baseToDecimal(const std::string& number, int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Base must be between 2 and 36");
    }
    
    if (number.empty()) {
        throw std::invalid_argument("Empty number string");
    }
    
    int result = 0;
    int power = 0;
    bool negative = false;
    
    std::string num = number;
    if (num[0] == '-') {
        negative = true;
        num = num.substr(1);
    }
    
    for (int i = num.length() - 1; i >= 0; i--) {
        int digit = charToDigit(num[i]);
        if (digit >= base) {
            throw std::invalid_argument("Invalid digit for base");
        }
        result += digit * pow(base, power);
        power++;
    }
    
    return negative ? -result : result;
}

std::string NumberConverter::convertBetweenBases(const std::string& number, int fromBase, int toBase) {
    int decimal = baseToDecimal(number, fromBase);
    return decimalToBase(decimal, toBase);
}

bool NumberConverter::isValidNumber(const std::string& number, int base) {
    if (number.empty() || base < 2 || base > 36) {
        return false;
    }
    
    std::string num = number;
    if (num[0] == '-') {
        num = num.substr(1);
    }
    
    if (num.empty()) {
        return false;
    }
    
    for (char c : num) {
        try {
            int digit = charToDigit(c);
            if (digit >= base) {
                return false;
            }
        } catch (const std::invalid_argument&) {
            return false;
        }
    }
    
    return true;
}

std::vector<std::string> NumberConverter::getConversionSteps(int decimal, int targetBase) {
    std::vector<std::string> steps;
    
    if (decimal == 0) {
        steps.push_back("0 ÷ " + std::to_string(targetBase) + " = 0 resto 0");
        steps.push_back("Resultado: 0");
        return steps;
    }
    
    int originalDecimal = decimal;
    bool negative = decimal < 0;
    decimal = abs(decimal);
    
    std::vector<int> remainders;
    
    while (decimal > 0) {
        int remainder = decimal % targetBase;
        remainders.push_back(remainder);
        
        std::stringstream ss;
        ss << decimal << " ÷ " << targetBase << " = " << (decimal / targetBase) 
           << " resto " << remainder;
        steps.push_back(ss.str());
        
        decimal /= targetBase;
    }
    
    steps.push_back("");
    steps.push_back("Leyendo los restos de abajo hacia arriba:");
    
    std::string result;
    for (int i = remainders.size() - 1; i >= 0; i--) {
        result += digitToChar(remainders[i]);
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    steps.push_back("Resultado: " + result);
    
    return steps;
}