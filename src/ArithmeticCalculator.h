#ifndef ARITHMETICCALCULATOR_H
#define ARITHMETICCALCULATOR_H

#include <string>
#include "StepByStepExplainer.h"

class ArithmeticCalculator {
public:
    std::string add(const std::string& num1, int base1,
                    const std::string& num2, int base2, int resultBase);
    std::string subtract(const std::string& num1, int base1,
                         const std::string& num2, int base2, int resultBase);
    std::string multiply(const std::string& num1, int base1,
                         const std::string& num2, int base2, int resultBase);
    
    std::string getLastCalculationSteps();

private:
    std::string lastSteps;
    int performOperation(int operand1, int operand2, Operation op);
};

#endif