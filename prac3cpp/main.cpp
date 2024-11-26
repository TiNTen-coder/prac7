#include "functions.h"

int main() {
    
    auto f = FunctionFactory::Create("power", {2.0});
    
    
    auto g = FunctionFactory::Create("polynomial", {7.0, 0.0, 3.0, 15.0});

    
    std::cout << f->ToString() << " for x = 10 is " << (*f)(10) << std::endl;
    std::cout << g->ToString() << " for x = 10 is " << (*g)(10) << std::endl;

    auto p = *f + *g;
    std::cout << p->ToString() << " for x = 1 is " << (*p)(1) << std::endl;

    double root = GradientDescent(*p, 1.0, 0.01, 10000);
    std::cout << "Root found at x = " << root << std::endl;
    

    return 0;
}