#include "BaseValidator.h"
#include <algorithm>
#include <sstream>

int BaseValidator::charToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    return -1;
}

bool BaseValidator::isValidDigit(char digit, int base) {
    int value = charToDigit(digit);
    return value >= 0 && value < base;
}

bool BaseValidator::isValidNumber(const std::string& number, int base) {
    if (number.empty() || !isValidBase(base)) {
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
        if (!isValidDigit(c, base)) {
            return false;
        }
    }
    
    return true;
}

bool BaseValidator::isValidBase(int base) {
    return base >= 2 && base <= 36;
}

int BaseValidator::getMinimumBase(const std::string& number) {
    if (number.empty()) {
        return -1;
    }
    
    std::string num = number;
    if (num[0] == '-') {
        num = num.substr(1);
    }
    
    if (num.empty()) {
        return -1;
    }
    
    int maxDigit = 0;
    for (char c : num) {
        int digit = charToDigit(c);
        if (digit == -1) {
            return -1;
        }
        maxDigit = std::max(maxDigit, digit);
    }
    
    return maxDigit + 1;
}

std::string BaseValidator::getValidationError(const std::string& number, int base) {
    if (number.empty()) {
        return "El número no puede estar vacío";
    }
    
    if (!isValidBase(base)) {
        return "La base debe estar entre 2 y 36";
    }
    
    std::string num = number;
    if (num[0] == '-') {
        num = num.substr(1);
    }
    
    if (num.empty()) {
        return "El número no puede ser solo un signo negativo";
    }
    
    for (char c : num) {
        int digit = charToDigit(c);
        if (digit == -1) {
            std::stringstream ss;
            ss << "Carácter inválido: '" << c << "'";
            return ss.str();
        }
        if (digit >= base) {
            std::stringstream ss;
            ss << "El dígito '" << c << "' no es válido para la base " << base;
            return ss.str();
        }
    }
    
    return "";
}