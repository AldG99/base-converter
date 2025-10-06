#include "StepByStepExplainer.h"
#include "NumberConverter.h"
#include <sstream>
#include <cmath>

std::string StepByStepExplainer::operationToString(Operation op) {
    switch (op) {
        case Operation::ADD: return "Suma";
        case Operation::SUBTRACT: return "Resta";
        case Operation::MULTIPLY: return "Multiplicación";
        default: return "Operación desconocida";
    }
}

std::string StepByStepExplainer::formatStep(const std::string& step, bool isResult) {
    if (isResult) {
        return "→ " + step;
    }
    return "  " + step;
}

std::string StepByStepExplainer::explainDecimalToBase(int decimal, int base) {
    std::stringstream explanation;
    explanation << "Conversión de " << decimal << " (decimal) a base " << base << ":\n\n";
    
    if (decimal == 0) {
        explanation << "El número 0 es 0 en cualquier base.\n";
        return explanation.str();
    }
    
    bool negative = decimal < 0;
    decimal = abs(decimal);
    int originalDecimal = decimal;
    
    explanation << "Método de divisiones sucesivas:\n";
    
    std::vector<int> remainders;
    while (decimal > 0) {
        int quotient = decimal / base;
        int remainder = decimal % base;
        remainders.push_back(remainder);
        
        explanation << decimal << " ÷ " << base << " = " << quotient << " resto " << remainder << "\n";
        decimal = quotient;
    }
    
    explanation << "\nLeyendo los restos de abajo hacia arriba:\n";
    std::string result;
    for (int i = remainders.size() - 1; i >= 0; i--) {
        char digit = (remainders[i] < 10) ? ('0' + remainders[i]) : ('A' + remainders[i] - 10);
        result += digit;
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    explanation << "Resultado: " << originalDecimal << " (decimal) = " << result << " (base " << base << ")\n";
    
    return explanation.str();
}

std::string StepByStepExplainer::explainBaseToDecimal(const std::string& number, int base) {
    std::stringstream explanation;
    explanation << "Conversión de " << number << " (base " << base << ") a decimal:\n\n";
    
    std::string num = number;
    bool negative = false;
    if (num[0] == '-') {
        negative = true;
        num = num.substr(1);
    }
    
    explanation << "Método de expansión posicional:\n";
    explanation << num << " (base " << base << ") = ";
    
    int result = 0;
    for (int i = 0; i < num.length(); i++) {
        char digit = num[i];
        int digitValue;
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else {
            digitValue = digit - 'A' + 10;
        }
        
        int position = num.length() - 1 - i;
        int positionValue = pow(base, position);
        int contribution = digitValue * positionValue;
        result += contribution;
        
        if (i > 0) explanation << " + ";
        explanation << digit << "×" << base << "^" << position;
    }
    
    explanation << "\n\nCalculando cada término:\n";
    result = 0;
    for (int i = 0; i < num.length(); i++) {
        char digit = num[i];
        int digitValue;
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else {
            digitValue = digit - 'A' + 10;
        }
        
        int position = num.length() - 1 - i;
        int positionValue = pow(base, position);
        int contribution = digitValue * positionValue;
        result += contribution;
        
        explanation << digit << "×" << base << "^" << position << " = " << digitValue 
                   << "×" << positionValue << " = " << contribution << "\n";
    }
    
    explanation << "\nSumando todos los términos:\n";
    explanation << "Resultado: " << (negative ? -result : result) << " (decimal)\n";
    
    return explanation.str();
}

std::string StepByStepExplainer::explainArithmetic(const std::string& num1, int base1,
                                                   const std::string& num2, int base2,
                                                   Operation op) {
    std::stringstream explanation;
    NumberConverter converter;
    
    explanation << operationToString(op) << ": " << num1 << " (base " << base1 
               << ") " << (op == Operation::ADD ? "+" : op == Operation::SUBTRACT ? "-" : "×") 
               << " " << num2 << " (base " << base2 << ")\n\n";
    
    int decimal1 = converter.baseToDecimal(num1, base1);
    int decimal2 = converter.baseToDecimal(num2, base2);
    
    explanation << "Paso 1: Convertir ambos números a decimal\n";
    if (base1 != 10) {
        explanation << num1 << " (base " << base1 << ") = " << decimal1 << " (decimal)\n";
    } else {
        explanation << num1 << " ya está en decimal\n";
    }
    
    if (base2 != 10) {
        explanation << num2 << " (base " << base2 << ") = " << decimal2 << " (decimal)\n";
    } else {
        explanation << num2 << " ya está en decimal\n";
    }
    
    explanation << "\nPaso 2: Realizar la operación en decimal\n";
    int result;
    switch (op) {
        case Operation::ADD:
            result = decimal1 + decimal2;
            explanation << decimal1 << " + " << decimal2 << " = " << result << "\n";
            break;
        case Operation::SUBTRACT:
            result = decimal1 - decimal2;
            explanation << decimal1 << " - " << decimal2 << " = " << result << "\n";
            break;
        case Operation::MULTIPLY:
            result = decimal1 * decimal2;
            explanation << decimal1 << " × " << decimal2 << " = " << result << "\n";
            break;
    }
    
    explanation << "\nPaso 3: Convertir el resultado a diferentes bases\n";
    explanation << result << " (decimal) =\n";
    explanation << "  Binario: " << converter.decimalToBase(result, 2) << "\n";
    explanation << "  Octal: " << converter.decimalToBase(result, 8) << "\n";
    explanation << "  Hexadecimal: " << converter.decimalToBase(result, 16) << "\n";
    
    return explanation.str();
}

std::vector<std::string> StepByStepExplainer::getDetailedConversionSteps(int decimal, int targetBase) {
    std::vector<std::string> steps;
    
    if (decimal == 0) {
        steps.push_back("Conversión de 0 (decimal) a base " + std::to_string(targetBase));
        steps.push_back("El número 0 es 0 en cualquier base");
        steps.push_back("Resultado: 0");
        return steps;
    }
    
    bool negative = decimal < 0;
    decimal = abs(decimal);
    int originalDecimal = decimal;
    
    steps.push_back("Conversión de " + std::to_string(negative ? -originalDecimal : originalDecimal) 
                   + " (decimal) a base " + std::to_string(targetBase));
    steps.push_back("Método de divisiones sucesivas:");
    steps.push_back("");
    
    std::vector<int> remainders;
    while (decimal > 0) {
        int quotient = decimal / targetBase;
        int remainder = decimal % targetBase;
        remainders.push_back(remainder);
        
        std::stringstream ss;
        ss << decimal << " ÷ " << targetBase << " = " << quotient << " resto " << remainder;
        steps.push_back(ss.str());
        
        decimal = quotient;
    }
    
    steps.push_back("");
    steps.push_back("Leyendo los restos de abajo hacia arriba:");
    
    std::string result;
    for (int i = remainders.size() - 1; i >= 0; i--) {
        char digit = (remainders[i] < 10) ? ('0' + remainders[i]) : ('A' + remainders[i] - 10);
        result += digit;
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    steps.push_back("Resultado: " + result);
    
    return steps;
}