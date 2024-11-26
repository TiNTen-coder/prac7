#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
#include <sstream>

class TFunction {
public:
    using Func = std::function<double(double)>;
    using Derivative = std::function<double(double)>;

    virtual ~TFunction() = default;
    virtual double operator()(double x) const = 0;
    virtual double GetDerivative(double x) const = 0;
    virtual std::string ToString() const = 0;

    template <typename T>
    std::shared_ptr<TFunction> operator+(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T>
    std::shared_ptr<TFunction> operator-(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T>
    std::shared_ptr<TFunction> operator*(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T>
    std::shared_ptr<TFunction> operator/(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }
};

using TFunctionPtr = std::shared_ptr<TFunction>;

class IdentFunction : public TFunction {
public:
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

class ConstFunction : public TFunction {
    double value;
public:
    explicit ConstFunction(double value);
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

class PowerFunction : public TFunction {
    double exponent;
public:
    explicit PowerFunction(double exponent);
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

class ExpFunction : public TFunction {
public:
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

class PolynomialFunction : public TFunction {
    std::vector<double> coefficients;
public:
    explicit PolynomialFunction(const std::vector<double>& coefficients);
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

class CompositeFunction : public TFunction {
    Func func;
    Derivative deriv;
    std::string repr;
public:
    CompositeFunction(Func func, Derivative deriv, const std::string& repr);
    double operator()(double x) const override;
    double GetDerivative(double x) const override;
    std::string ToString() const override;
};

template <typename T, size_t N>
T operator+(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T>
T operator+(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator-(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T>
T operator-(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator*(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T>
T operator*(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator/(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T>
T operator/(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

TFunctionPtr operator+(const TFunction& lhs, const TFunction& rhs);
TFunctionPtr operator-(const TFunction& lhs, const TFunction& rhs);
TFunctionPtr operator*(const TFunction& lhs, const TFunction& rhs);
TFunctionPtr operator/(const TFunction& lhs, const TFunction& rhs);

double GradientDescent(const TFunction& f, double initialGuess, double learningRate, int iterations);

class FunctionFactory {
public:
    static TFunctionPtr Create(const std::string& type, const std::vector<double>& params);
};

#endif
