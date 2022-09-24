#include "mathLibrary.h"

int main() {
    std::vector<double> x_0 = {4,4};
    std::pair<double, double> x1(-5, 5);
    std::pair<double, double> x2(-5, 5);
    std::vector<std::pair<double, double>> box = {x1, x2};
    Area aria(box);
    Function *function = new Function1();

    // Стохастический метод.
//    TerminationMethod *terminationMethod = new TerminationMethodProb1(pow(10, -6));
    TerminationMethod *terminationMethod = new TerminationMethodProb2(10000);
//    TerminationMethod *terminationMethod = new TerminationMethodProb3(10000);
//    OptimizationMethod *optimizationMethod = new OptimizationMethodProb(function, x_0, aria, terminationMethod);
//    optimizationMethod->optimization();
    // Стохастический метод.
    // Градиент.
    OptimizationMethodGrad optimizationMethodGrad(function, x_0, aria, terminationMethod);
    optimizationMethodGrad.optimization();



    // Градиент.


    return 0;
}
