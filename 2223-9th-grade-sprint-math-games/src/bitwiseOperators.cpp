#include "pch.h"

std::string generateRandomBinaryString() {
    std::string binary = "";
    for (int i = 0; i < 4; i++) {
        if (GetRandomValue(0, 1) == 0) {
            binary += "0";
        }
        else {
            binary += "1";
        }
    }
    return binary;
}

std::string bitwiseAND(std::string a, std::string b) {
    std::string result = "";
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] == '1' && b[i] == '1') {
            result += "1";
        }
        else {
            result += "0";
        }
    }
    return result;
}

std::string bitwiseOR(std::string a, std::string b) {
    std::string result = "";
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] == '1' || b[i] == '1') {
            result += "1";
        }
        else {
            result += "0";
        }
    }
    return result;
}

std::string bitwiseXOR(std::string a, std::string b) {
    std::string result = "";
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            result += "0";
        }
        else {
            result += "1";
        }
    }
    return result;
}

std::string leftShift(std::string a, int n) {
    std::string result = "";
    int size = a.size();
    for (int i = n; i < size; i++) {
        result += a[i];
    }
    for (int i = 0; i < n; i++) {
        result += "0";
    }
    return result;
}

std::string rightShift(std::string a, int n) {
    std::string result = "";
    int size = a.size();
    for (int i = 0; i < size - n; i++) {
        result += a[i];
    }
    for (int i = 0; i < n; i++) {
        result = "0" + result;
    }
    return result;
}
int decimalToBinary(int decimalNum) {
    int binaryNum = 0;
    int base = 1;

    while (decimalNum > 0) {
        binaryNum += (decimalNum & 1) * base;
        decimalNum >>= 1;
        base *= 10;
    }
    return binaryNum;
}