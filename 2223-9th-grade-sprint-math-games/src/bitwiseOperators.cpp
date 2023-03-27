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