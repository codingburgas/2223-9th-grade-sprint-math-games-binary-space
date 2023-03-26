#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(UnitTests)
    {
    public:
        TEST_METHOD(TestBitwiseOperations)
        {
            std::string result = bitwiseAND("1010", "1100");
            Assert::AreEqual(std::string("1000"), result);

            result = bitwiseOR("1010", "1100");
            Assert::AreEqual(std::string("1110"), result);

            result = bitwiseXOR("1010", "1100");
            Assert::AreEqual(std::string("0110"), result);

            result = leftShift("1010", 2);
            Assert::AreEqual(std::string("1000"), result);

            result = rightShift("1010", 2);
            Assert::AreEqual(std::string("0010"), result);

            int decimal = 10;
            int binary = decimalToBinary(decimal);
            Assert::AreEqual(1010, binary);

            decimal = 7;
            binary = decimalToBinary(decimal);
            Assert::AreEqual(111, binary);
        }

        TEST_METHOD(TestGenerateRandomEquation)
        {
            Equation equation;
            std::string binary1 = "1010";
            std::string binary2 = "1100";
            equation = GenerateRandomEquation(equation, binary1, binary2, 1);

            Assert::IsNotNull(equation.Operator.c_str());
            Assert::IsNotNull(equation.answer1.c_str());

            bool isValidOperator = (equation.Operator == "&") || (equation.Operator == "|") || (equation.Operator == "^") || (equation.Operator == "<<") || (equation.Operator == ">>");
            Assert::IsTrue(isValidOperator);

            if (equation.Operator == "&")
            {
                Assert::AreEqual(std::string("1000"), equation.answer1);
            }
            else if (equation.Operator == "|")
            {
                Assert::AreEqual(std::string("1110"), equation.answer1);
            }
            else if (equation.Operator == "^")
            {
                Assert::AreEqual(std::string("0110"), equation.answer1);
            }
            else if (equation.Operator == "<<")
            {
                Assert::AreEqual(std::string("101000"), equation.answer1);
            }
            else if (equation.Operator == ">>")
            {
                Assert::AreEqual(std::string("0010"), equation.answer1);
            }
        }
        TEST_METHOD(TestGenerateRandomBinaryString)
        {
            // Test if the generated binary string is of length 4
            std::string binary = generateRandomBinaryString();
            Assert::AreEqual(static_cast<int>(binary.size()), 4);

            // Test if the generated binary string only contains 0's and 1's
            for (char c : binary) {
                Assert::IsTrue(c == '0' || c == '1');
            }
        }

        TEST_METHOD(TestBitwiseAND)
        {
            // Test with two all-ones binary strings
            std::string binary1 = "1111";
            std::string binary2 = "1111";
            std::string result = bitwiseAND(binary1, binary2);
            Assert::AreEqual(result, std::string("1111"));

            // Test with two all-zeros binary strings
            binary1 = "0000";
            binary2 = "0000";
            result = bitwiseAND(binary1, binary2);
            Assert::AreEqual(result, std::string("0000"));

            // Test with two arbitrary binary strings
            binary1 = "1010";
            binary2 = "1100";
            result = bitwiseAND(binary1, binary2);
            Assert::AreEqual(result, std::string("1000"));
        }

        TEST_METHOD(TestBitwiseOR)
        {
            // Test with two all-ones binary strings
            std::string binary1 = "1111";
            std::string binary2 = "1111";
            std::string result = bitwiseOR(binary1, binary2);
            Assert::AreEqual(result, std::string("1111"));

            // Test with two all-zeros binary strings
            binary1 = "0000";
            binary2 = "0000";
            result = bitwiseOR(binary1, binary2);
            Assert::AreEqual(result, std::string("0000"));

            // Test with two arbitrary binary strings
            binary1 = "1010";
            binary2 = "1100";
            result = bitwiseOR(binary1, binary2);
            Assert::AreEqual(result, std::string("1110"));
        }

        TEST_METHOD(TestBitwiseXOR)
        {
            // Test with two all-ones binary strings
            std::string binary1 = "1111";
            std::string binary2 = "1111";
            std::string result = bitwiseXOR(binary1, binary2);
            Assert::AreEqual(result, std::string("0000"));

            // Test with two all-zeros binary strings
            binary1 = "0000";
            binary2 = "0000";
            result = bitwiseXOR(binary1, binary2);
            Assert::AreEqual(result, std::string("0000"));

            // Test with two arbitrary binary strings
            binary1 = "1010";
            binary2 = "1100";
            result = bitwiseXOR(binary1, binary2);
            Assert::AreEqual(result, std::string("0110"));
        }
        
        TEST_METHOD(TestMainMenu)
        {
            // Arrange
            const int screenWidth = 800;
            const int screenHeight = 600;

            // Act
            bool result = mainMenu(screenWidth, screenHeight);

            // Assert
            Assert::IsTrue(result, L"mainMenu function returned false", LINE_INFO());
        }
        
    };

}