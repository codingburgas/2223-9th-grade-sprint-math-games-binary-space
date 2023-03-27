#pragma once
#include "raylib.h"
#include <string>

struct Equation
{
    int num1;
    int num2;
    std::string Operator;
    std::string answer;
};
Equation GenerateRandomEquation(Equation& equation, std::string binary1, std::string binary2);