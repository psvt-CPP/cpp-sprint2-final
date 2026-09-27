
#include <iostream>
#include <string>
#include <cmath>
#include "calculator.h"


bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle () {
    Number current_number = 0;

    if (!ReadNumber(current_number)) {
        return false;
    }

    Number memory = 0;
    bool memory_save = false;

    std::string command;

    while (std::cin >> command) {
        Number operand;

        if (command == "+") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number += operand;
        } else if (command == "-") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number -= operand;
        } else if (command == "*") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number *= operand;
        } else if (command == "/") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number /= operand;
        } else if (command == "**") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number = std::pow(current_number, operand);
        } else if (command == "s") {
            memory = current_number;
            memory_save = true;
        } else if (command == "l") {
            if (!memory_save) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            current_number = memory;
        } else if (command == "=") {
            std::cout << current_number << std::endl;
        } else if (command == ":") {
            if (!ReadNumber(operand)) {
                return false;
            }
            current_number = operand;
        } else if (command == "c") {
            current_number = 0;
        } else if (command == "q") {
            return true;
        } else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return false;
        }
    }
    return false;
}