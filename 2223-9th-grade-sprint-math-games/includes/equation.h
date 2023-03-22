#pragma once
#include "raylib.h"
#include <string>

struct Equation
{
    std::string Operator;
    std::string answer;
};
Equation GenerateRandomEquation(Equation& equation, std::string binary1, std::string binary2);
std::string bitwiseAND(std::string a, std::string b);
std::string bitwiseOR(std::string a, std::string b);
std::string bitwiseXOR(std::string a, std::string b);
std::string leftShift(std::string a, int n);
std::string rightShift(std::string a, int n);
