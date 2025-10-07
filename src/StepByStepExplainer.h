#ifndef STEPBYSTEPEXPLAINER_H
#define STEPBYSTEPEXPLAINER_H

#include <string>
#include <vector>

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY
};

class StepByStepExplainer {
public:
    std::string explainDecimalToBase(int decimal, int base);
    std::string explainBaseToDecimal(const std::string& number, int base);
    std::string explainArithmetic(const std::string& num1, int base1,
                                  const std::string& num2, int base2,
                                  Operation op);
    std::vector<std::string> getDetailedConversionSteps(int decimal, int targetBase);

private:
    std::string operationToString(Operation op);
    std::string formatStep(const std::string& step, bool isResult = false);
};

#endif