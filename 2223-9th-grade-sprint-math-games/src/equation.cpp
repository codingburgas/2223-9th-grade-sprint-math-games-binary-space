#include "pch.h"

Equation GenerateRandomEquation(Equation& equation, std::string binary1, std::string binary2, int level)
{
    //Equation
    int Operator = GetRandomValue(0, 4);
    switch (level)
    {
    case 1:
        switch (Operator)
        {
        case 0:
            equation.answer1 = bitwiseAND(binary1, binary2);
            equation.Operator = "&";
            break;
        case 1:
            equation.answer1 = bitwiseOR(binary1, binary2);
            equation.Operator = "|";
            break;
        case 2:
            equation.answer1 = bitwiseXOR(binary1, binary2);
            equation.Operator = "^";
            break;
        case 3:
            equation.answer1 = leftShift(binary1, 2);
            equation.Operator = "<<";
            break;
        case 4:
            equation.answer1 = rightShift(binary1, 2);
            equation.Operator = ">>";
            break;
        }
    }
    return equation;
}