#include "pch.h"
#include "CppUnitTest.h"
#include "Equation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
    TEST_CLASS(GenerateRandomEquationTests)
    {
    public:
        TEST_METHOD(TestGenerateRandomEquation)
        {
            Equation equation;
            std::string binary1 = "1010";
            std::string binary2 = "1100";
            equation = GenerateRandomEquation(equation, binary1, binary2, 1);

            // Check that the equation has been generated
            Assert::IsNotNull(equation.Operator.c_str());
            Assert::IsNotNull(equation.answer1.c_str());

            // Check that the operator is one of the expected values
            bool isValidOperator = (equation.Operator == "&") || (equation.Operator == "|") || (equation.Operator == "^") || (equation.Operator == "<<") || (equation.Operator == ">>");
            Assert::IsTrue(isValidOperator);

            // Check that the answer1 is correct
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
