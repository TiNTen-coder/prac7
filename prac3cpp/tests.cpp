#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <vector>
#include "functions.h"

using namespace testing;

TEST(FunctionTest, IdentFunction) {
    auto ident = FunctionFactory::Create("ident", {});

    EXPECT_DOUBLE_EQ((*ident)(2.0), 2.0);
    EXPECT_DOUBLE_EQ(ident->GetDerivative(2.0), 1.0);
}

TEST(FunctionTest, IdentPlusAnother) {
    auto ident = FunctionFactory::Create("ident", {});
    auto power = FunctionFactory::Create("power", {2.0});
    auto h = *ident + *power;

    EXPECT_DOUBLE_EQ((*h)(2.0), 6.0);
}

TEST(FunctionTest, ConstFunction) {
    auto constant = FunctionFactory::Create("const", {5.0});

    EXPECT_DOUBLE_EQ((*constant)(2.0), 5.0);
    EXPECT_DOUBLE_EQ(constant->GetDerivative(2.0), 0.0);
}

TEST(FunctionTest, PowerFunction) {
    auto power = FunctionFactory::Create("power", {2.0});

    EXPECT_DOUBLE_EQ((*power)(3.0), 9.0);
    EXPECT_DOUBLE_EQ(power->GetDerivative(3.0), 6.0);
}

TEST(FunctionTest, ExpFunction) {
    auto exp = FunctionFactory::Create("exp", {});

    EXPECT_DOUBLE_EQ((*exp)(1.0), std::exp(1.0));
    EXPECT_DOUBLE_EQ(exp->GetDerivative(1.0), std::exp(1.0));
}

TEST(FunctionTest, ExpFunctio123n) {
    auto exp = FunctionFactory::Create("exp", {});

    std::cout << (*exp)(0.0) << std::endl;
    EXPECT_DOUBLE_EQ((*exp)(0.0), 1.0);
    EXPECT_DOUBLE_EQ(exp->GetDerivative(1.0), std::exp(1.0));
}

TEST(FunctionTest, PolynomialFunction) {
    auto polynomial = FunctionFactory::Create("polynomial", {0.0, 1.0, 2.0, 3.0, 4.0});

    EXPECT_DOUBLE_EQ((*polynomial)(1.0), 10.0);
    EXPECT_DOUBLE_EQ(polynomial->GetDerivative(1.0), 30.0);
}

TEST(FunctionTest, CompositeFunctionsSum) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = FunctionFactory::Create("const", {3.0});
    auto h = *f + *g;

    EXPECT_DOUBLE_EQ((*h)(2.0), 7.0);
    EXPECT_DOUBLE_EQ(h->GetDerivative(2.0), 4.0);
}

TEST(FunctionTest, CompositeFunctionsMultiply) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = FunctionFactory::Create("const", {3.0});
    auto h = *f * *g;

    EXPECT_DOUBLE_EQ((*h)(2.0), 12.0);
    EXPECT_DOUBLE_EQ(h->GetDerivative(2.0), 12.0);

}

TEST(FunctionTest, CompositeFunctionsSubtract) {
    auto f = FunctionFactory::Create("polynomial", {0.0, 1.0, -2.0, 1.0});
    auto g = FunctionFactory::Create("const", {2.0});
    auto h = *f - *g;

    EXPECT_DOUBLE_EQ((*h)(2.0), 0.0);
    EXPECT_DOUBLE_EQ(h->GetDerivative(1.0), 0.0);
}

TEST(FunctionTest, CompositeFunctionsDivide) {
    auto f = FunctionFactory::Create("polynomial", {0.0, 1.0, 1.0, 1.0});
    auto g = FunctionFactory::Create("power", {1.0});
    auto h = *f / *g;

    EXPECT_DOUBLE_EQ((*h)(2.0), 7.0);
    EXPECT_DOUBLE_EQ(h->GetDerivative(1.0), 3.0);
}

TEST(FunctionTest, GradientDescentPositiveRoot) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = FunctionFactory::Create("const", {4.0});
    auto shifted = *f - *g;
    
    double root = GradientDescent(*shifted, 5.0, 0.1, 1000);
    EXPECT_NEAR(root, 2.0, 0.1); 
}

TEST(FunctionTest, GradientDescentNegativeRoot) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = FunctionFactory::Create("const", {4.0});
    auto shifted = *f - *g;

    double root = GradientDescent(*shifted, -5.0, 0.1, 1000);
    EXPECT_NEAR(root, -2.0, 0.1);    
}

TEST(FunctionTest, WithStringSecondOperatorPlus) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({*f + "abc";}, std::logic_error);
}

TEST(FunctionTest, WithStringFirstOperatorPlus) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({"abc" + *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringVectorPlus) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = std::vector<int>{1, 2, 3};
    EXPECT_THROW({g + *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringSecondOperatorMinus) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({*f - "abc";}, std::logic_error);
}

TEST(FunctionTest, WithStringFirstOperatorMinus) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({"abc" - *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringVectorMinus) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = std::vector<int>{1, 2, 3};
    EXPECT_THROW({g - *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringSecondOperatorMulty) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({*f * "abc";}, std::logic_error);
}

TEST(FunctionTest, WithStringFirstOperatorMulty) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({"abc" * *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringVectorMulty) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = std::vector<int>{1, 2, 3};
    EXPECT_THROW({g * *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringSecondOperatorDivide) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({*f / "abc";}, std::logic_error);
}

TEST(FunctionTest, WithStringFirstOperatorDivide) {
    auto f = FunctionFactory::Create("power", {2.0});

    EXPECT_THROW({"abc" / *f;}, std::logic_error);
}

TEST(FunctionTest, WithStringVectorDivide) {
    auto f = FunctionFactory::Create("power", {2.0});
    auto g = std::vector<int>{1, 2, 3};
    EXPECT_THROW({g / *f;}, std::logic_error);
}

TEST(FunctionTest, qwe) {
    auto f = FunctionFactory::Create("polynomial", {5.0, 1.0});
    auto g = FunctionFactory::Create("polynomial", {-2.0, 1.0});
    auto h = *f * *g;
    std::cout << h->GetDerivative(10.0) << std::endl;
    std::cout << (*h)(3.0) << std::endl;
    double root = GradientDescent(*h, 0.0, 0.1, 1000);
    std::cout << root << std::endl;
    double root2 = GradientDescent(*h, -7.0, 0.1, 1000);
    std::cout << root2 << std::endl;
}

int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv); 
  ::testing::InitGoogleMock(&argc, argv); 
 
  return RUN_ALL_TESTS(); 
}