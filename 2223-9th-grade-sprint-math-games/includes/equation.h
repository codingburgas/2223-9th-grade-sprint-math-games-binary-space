#pragma once
#include "raylib.h"
#include <string>

struct Equation
{
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    std::string Operator;
    std::string Operator2;
    std::string Operator3;
    std::string answer;
    std::string answer1;
    std::string answer2;
    std::string answer3;
};
Equation GenerateRandomEquation(Equation& equation, std::string binary1, std::string binary2, int level);
std::string bitwiseAND(std::string a, std::string b);
std::string bitwiseOR(std::string a, std::string b);
std::string bitwiseXOR(std::string a, std::string b);
std::string leftShift(std::string a, int n);
std::string rightShift(std::string a, int n);
