#include <iostream>
#include <string>
#include "NumberConverter.h"
#include "BaseValidator.h"
#include "StepByStepExplainer.h"
#include "ArithmeticCalculator.h"

void displayMenu() {
    std::cout << "\n=== Convertidor de Sistemas Numéricos ===\n";
    std::cout << "1. Convertir número entre bases\n";
    std::cout << "2. Ver proceso paso a paso\n";
    std::cout << "3. Realizar operación aritmética\n";
    std::cout << "4. Validar número\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void convertNumber(NumberConverter& converter, BaseValidator& validator) {
    std::string number;
    int fromBase, toBase;
    
    std::cout << "Ingrese el número: ";
    std::cin >> number;
    std::cout << "Ingrese la base de origen (2-36): ";
    std::cin >> fromBase;
    std::cout << "Ingrese la base de destino (2-36): ";
    std::cin >> toBase;
    
    if (!validator.isValidNumber(number, fromBase)) {
        std::cout << "Error: " << validator.getValidationError(number, fromBase) << std::endl;
        return;
    }
    
    try {
        std::string result = converter.convertBetweenBases(number, fromBase, toBase);
        std::cout << "Resultado: " << number << " (base " << fromBase << ") = " 
                  << result << " (base " << toBase << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void showStepByStep(NumberConverter& converter, BaseValidator& validator, StepByStepExplainer& explainer) {
    std::string number;
    int fromBase, toBase;
    
    std::cout << "Ingrese el número: ";
    std::cin >> number;
    std::cout << "Ingrese la base de origen (2-36): ";
    std::cin >> fromBase;
    std::cout << "Ingrese la base de destino (2-36): ";
    std::cin >> toBase;
    
    if (!validator.isValidNumber(number, fromBase)) {
        std::cout << "Error: " << validator.getValidationError(number, fromBase) << std::endl;
        return;
    }
    
    try {
        int decimal = converter.baseToDecimal(number, fromBase);
        
        std::cout << "\n" << std::string(50, '=') << std::endl;
        
        if (fromBase != 10) {
            std::cout << explainer.explainBaseToDecimal(number, fromBase) << std::endl;
            std::cout << std::string(50, '=') << std::endl;
        }
        
        if (toBase != 10) {
            std::cout << explainer.explainDecimalToBase(decimal, toBase) << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void performArithmetic(NumberConverter& converter, BaseValidator& validator, ArithmeticCalculator& calculator) {
    std::string num1, num2;
    int base1, base2, resultBase, operation;
    
    std::cout << "Primer número: ";
    std::cin >> num1;
    std::cout << "Base del primer número (2-36): ";
    std::cin >> base1;
    
    std::cout << "Segundo número: ";
    std::cin >> num2;
    std::cout << "Base del segundo número (2-36): ";
    std::cin >> base2;
    
    std::cout << "Operación (1=Suma, 2=Resta, 3=Multiplicación): ";
    std::cin >> operation;
    
    std::cout << "Base para el resultado (2-36): ";
    std::cin >> resultBase;
    
    if (!validator.isValidNumber(num1, base1)) {
        std::cout << "Error en el primer número: " << validator.getValidationError(num1, base1) << std::endl;
        return;
    }
    
    if (!validator.isValidNumber(num2, base2)) {
        std::cout << "Error en el segundo número: " << validator.getValidationError(num2, base2) << std::endl;
        return;
    }
    
    try {
        std::string result;
        switch (operation) {
            case 1:
                result = calculator.add(num1, base1, num2, base2, resultBase);
                break;
            case 2:
                result = calculator.subtract(num1, base1, num2, base2, resultBase);
                break;
            case 3:
                result = calculator.multiply(num1, base1, num2, base2, resultBase);
                break;
            default:
                std::cout << "Operación inválida." << std::endl;
                return;
        }
        
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << calculator.getLastCalculationSteps() << std::endl;
        std::cout << "Resultado final: " << result << " (base " << resultBase << ")" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void validateNumber(BaseValidator& validator) {
    std::string number;
    int base;
    
    std::cout << "Ingrese el número: ";
    std::cin >> number;
    std::cout << "Ingrese la base (2-36): ";
    std::cin >> base;
    
    if (validator.isValidNumber(number, base)) {
        std::cout << "✓ El número es válido para la base " << base << std::endl;
        int minBase = validator.getMinimumBase(number);
        if (minBase != -1 && minBase < base) {
            std::cout << "  La base mínima posible para este número es: " << minBase << std::endl;
        }
    } else {
        std::cout << "❌ Error: " << validator.getValidationError(number, base) << std::endl;
        int minBase = validator.getMinimumBase(number);
        if (minBase != -1) {
            std::cout << "  La base mínima posible para este número sería: " << minBase << std::endl;
        }
    }
}

int main() {
    NumberConverter converter;
    BaseValidator validator;
    StepByStepExplainer explainer;
    ArithmeticCalculator calculator;
    
    std::cout << "Bienvenido al Convertidor de Sistemas Numéricos" << std::endl;
    std::cout << "Versión de línea de comandos" << std::endl;
    std::cout << "Para usar la versión gráfica, compile con 'make gui'" << std::endl;
    
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                convertNumber(converter, validator);
                break;
            case 2:
                showStepByStep(converter, validator, explainer);
                break;
            case 3:
                performArithmetic(converter, validator, calculator);
                break;
            case 4:
                validateNumber(validator);
                break;
            case 5:
                std::cout << "¡Gracias por usar el convertidor!" << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, seleccione 1-5." << std::endl;
        }
    } while (choice != 5);
    
    return 0;
}