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
       

        };
    }

