#include "functions.h"
#include <stdexcept>
#include <sstream>

double IdentFunction::operator()(double x) const {
    return x;
}

double IdentFunction::GetDerivative(double x) const {
    return 1;
}

std::string IdentFunction::ToString() const {
    return "x";
}

ConstFunction::ConstFunction(double value) : value(value) {}

double ConstFunction::operator()(double x) const {
    return value;
}

double ConstFunction::GetDerivative(double x) const {
    return 0;
}

std::string ConstFunction::ToString() const {
    return std::to_string(value);
}

PowerFunction::PowerFunction(double exponent) : exponent(exponent) {}

double PowerFunction::operator()(double x) const {
    return std::pow(x, exponent);
}

double PowerFunction::GetDerivative(double x) const {
    return exponent * std::pow(x, exponent - 1);
}

std::string PowerFunction::ToString() const {
    return "x^" + std::to_string(exponent);
}

double ExpFunction::operator()(double x) const {
    return std::exp(x);
}

double ExpFunction::GetDerivative(double x) const {
    return std::exp(x);
}

std::string ExpFunction::ToString() const {
    return "exp(x)";
}

PolynomialFunction::PolynomialFunction(const std::vector<double>& coefficients)
    : coefficients(coefficients) {}

double PolynomialFunction::operator()(double x) const {
    double result = 0;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * std::pow(x, i);
    }
    return result;
}

double PolynomialFunction::GetDerivative(double x) const {
    double result = 0;
    for (size_t i = 1; i < coefficients.size(); ++i) {
        result += i * coefficients[i] * std::pow(x, i - 1);
    }
    return result;
}

std::string PolynomialFunction::ToString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (coefficients[i] != 0) {
            if (i > 0) oss << " + ";
            oss << coefficients[i];
            if (i > 0) oss << "*x^" << i;
        }
    }
    return oss.str();
}

CompositeFunction::CompositeFunction(Func func, Derivative deriv, const std::string& repr)
    : func(std::move(func)), deriv(std::move(deriv)), repr(repr) {}

double CompositeFunction::operator()(double x) const {
    return func(x);
}

double CompositeFunction::GetDerivative(double x) const {
    return deriv(x);
}

std::string CompositeFunction::ToString() const {
    return repr;
}

TFunctionPtr operator+(const TFunction& lhs, const TFunction& rhs) {
    auto func = [&lhs, &rhs](double x) { return lhs(x) + rhs(x); };
    auto deriv = [&lhs, &rhs](double x) { return lhs.GetDerivative(x) + rhs.GetDerivative(x); };
    return std::make_shared<CompositeFunction>(func, deriv, "(" + lhs.ToString() + " + " + rhs.ToString() + ")");
}

TFunctionPtr operator-(const TFunction& lhs, const TFunction& rhs) {
    auto func = [&lhs, &rhs](double x) { return lhs(x) - rhs(x); };
    auto deriv = [&lhs, &rhs](double x) { return lhs.GetDerivative(x) - rhs.GetDerivative(x); };
    return std::make_shared<CompositeFunction>(func, deriv, "(" + lhs.ToString() + " - " + rhs.ToString() + ")");
}

TFunctionPtr operator*(const TFunction& lhs, const TFunction& rhs) {
    auto func = [&lhs, &rhs](double x) { return lhs(x) * rhs(x); };
    auto deriv = [&lhs, &rhs](double x) { 
        return lhs.GetDerivative(x) * rhs(x) + lhs(x) * rhs.GetDerivative(x);
    };
    return std::make_shared<CompositeFunction>(func, deriv, "(" + lhs.ToString() + " * " + rhs.ToString() + ")");
}

TFunctionPtr operator/(const TFunction& lhs, const TFunction& rhs) {
    auto func = [&lhs, &rhs](double x) { 
        double denominator = rhs(x);
        if (denominator == 0) throw std::logic_error("Division by zero");
        return lhs(x) / denominator;
    };
    auto deriv = [&lhs, &rhs](double x) { 
        double denominator = rhs(x);
        if (denominator == 0) throw std::logic_error("Division by zero");
        return (lhs.GetDerivative(x) * denominator - lhs(x) * rhs.GetDerivative(x)) / (denominator * denominator);
    };
    return std::make_shared<CompositeFunction>(func, deriv, "(" + lhs.ToString() + " / " + rhs.ToString() + ")");
}

double GradientDescent(const TFunction& f, double initialGuess, double learningRate, int iterations) {
    double x = initialGuess;
    for (int i = 0; i < iterations; ++i) {
        double grad = f.GetDerivative(x);
        x -= learningRate * f(x) / grad;
    }
    return x;
}

TFunctionPtr FunctionFactory::Create(const std::string& type, const std::vector<double>& params) {
    if (type == "ident") {
        return std::make_shared<IdentFunction>();
    } else if (type == "const") {
        if (params.size() != 1) throw std::invalid_argument("Invalid parameters for const");
        return std::make_shared<ConstFunction>(params[0]);
    } else if (type == "power") {
        if (params.size() != 1) throw std::invalid_argument("Invalid parameters for power");
        return std::make_shared<PowerFunction>(params[0]);
    } else if (type == "exp") {
        return std::make_shared<ExpFunction>();
    } else if (type == "polynomial") {
        return std::make_shared<PolynomialFunction>(params);
    } else {
        throw std::invalid_argument("Unknown function type");
    }
}
