#include "mathLibrary.h"

int main() {
    std::vector<double> x_0 = {0, 0};
    std::pair<double, double> x1(-5, 5);
    std::pair<double, double> x2(-5, 5);
    std::vector<std::pair<double, double>> box = {x1, x2};
    Area aria(box);
    Function *function = new Function3();

    // Стохастический метод.
//    TerminationMethod *terminationMethod = new TerminationMethodProb1(pow(10, -6));
//    TerminationMethod *terminationMethod = new TerminationMethodProb2(10000);
//    TerminationMethod *terminationMethod = new TerminationMethodProb3(10000);
//    OptimizationMethod *optimizationMethod = new OptimizationMethodProb(function, x_0, aria, terminationMethod);
//    optimizationMethod->optimization();
    // Стохастический метод.
    // Градиент.
//    TerminationMethod *terminationMethod = new TerminationMethodProb4(pow(10, -4));
    TerminationMethod *terminationMethod = new TerminationMethodProb5(pow(10, -4));
//    TerminationMethod *terminationMethod = new TerminationMethodProb6(pow(10, -4));
    OptimizationMethodGrad optimizationMethodGrad(function, x_0, aria, terminationMethod);
    optimizationMethodGrad.optimization();
    std::cout << optimizationMethodGrad.getSequenceOfX_i().back()[0] << " " <<
                 optimizationMethodGrad.getSequenceOfX_i().back()[1] << " " <<
                 optimizationMethodGrad.getSequenceOfF_i().back() << " " <<
                 optimizationMethodGrad.getNumberOfIterations() << std::endl;


    // Градиент.


    return 0;
}
