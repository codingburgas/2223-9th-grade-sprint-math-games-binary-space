#include "pch.h"

Equation GenerateRandomEquation(Equation& equation, std::string binary1, std::string binary2)
{
    //Equation
    int Operator = GetRandomValue(0, 4);
    switch (Operator)
    {
    case 0:
        equation.answer = bitwiseAND(binary1, binary2);
        equation.Operator = "&";
        break;
    case 1:
        equation.answer = bitwiseOR(binary1, binary2);
        equation.Operator = "|";
        break;
    case 2:
        equation.answer = bitwiseXOR(binary1, binary2);
        equation.Operator = "^";
        break;
    }
    return equation;
}