#include "ArithmeticCalculator.h"
#include "NumberConverter.h"
#include <sstream>

int ArithmeticCalculator::performOperation(int operand1, int operand2, Operation op) {
    switch (op) {
        case Operation::ADD:
            return operand1 + operand2;
        case Operation::SUBTRACT:
            return operand1 - operand2;
        case Operation::MULTIPLY:
            return operand1 * operand2;
        default:
            return 0;
    }
}

std::string ArithmeticCalculator::add(const std::string& num1, int base1,
                                      const std::string& num2, int base2, int resultBase) {
    NumberConverter converter;
    StepByStepExplainer explainer;
    
    try {
        int decimal1 = converter.baseToDecimal(num1, base1);
        int decimal2 = converter.baseToDecimal(num2, base2);
        int result = decimal1 + decimal2;
        
        lastSteps = explainer.explainArithmetic(num1, base1, num2, base2, Operation::ADD);
        
        return converter.decimalToBase(result, resultBase);
    } catch (const std::exception& e) {
        lastSteps = "Error en el cálculo: " + std::string(e.what());
        return "Error";
    }
}

std::string ArithmeticCalculator::subtract(const std::string& num1, int base1,
                                           const std::string& num2, int base2, int resultBase) {
    NumberConverter converter;
    StepByStepExplainer explainer;
    
    try {
        int decimal1 = converter.baseToDecimal(num1, base1);
        int decimal2 = converter.baseToDecimal(num2, base2);
        int result = decimal1 - decimal2;
        
        lastSteps = explainer.explainArithmetic(num1, base1, num2, base2, Operation::SUBTRACT);
        
        return converter.decimalToBase(result, resultBase);
    } catch (const std::exception& e) {
        lastSteps = "Error en el cálculo: " + std::string(e.what());
        return "Error";
    }
}

std::string ArithmeticCalculator::multiply(const std::string& num1, int base1,
                                           const std::string& num2, int base2, int resultBase) {
    NumberConverter converter;
    StepByStepExplainer explainer;
    
    try {
        int decimal1 = converter.baseToDecimal(num1, base1);
        int decimal2 = converter.baseToDecimal(num2, base2);
        int result = decimal1 * decimal2;
        
        lastSteps = explainer.explainArithmetic(num1, base1, num2, base2, Operation::MULTIPLY);
        
        return converter.decimalToBase(result, resultBase);
    } catch (const std::exception& e) {
        lastSteps = "Error en el cálculo: " + std::string(e.what());
        return "Error";
    }
}

std::string ArithmeticCalculator::getLastCalculationSteps() {
    return lastSteps;
}