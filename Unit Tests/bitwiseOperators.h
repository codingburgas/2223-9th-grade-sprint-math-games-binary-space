#pragma once
#include "raylib.h"
#include <string>
std::string generateRandomBinaryString();
std::string bitwiseAND(std::string a, std::string b);
std::string bitwiseOR(std::string a, std::string b);
std::string bitwiseXOR(std::string a, std::string b);
std::string leftShift(std::string a, int n);
std::string rightShift(std::string a, int n);
int decimalToBinary(int decimalNum);