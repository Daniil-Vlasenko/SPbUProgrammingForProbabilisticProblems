#include "mathLibrary.h"

int main() {
    std::vector<double> x_0 = {0, 0, 0, 0};
    std::pair<double, double> x1(-7, 7);
    std::pair<double, double> x2(-7, 7);
    std::pair<double, double> x3(-7, 7);
    std::pair<double, double> x4(-7, 7);
    std::vector<std::pair<double, double>> box = {x1, x2, x3, x4};
    Area aria(box);
    Function *function = new Function4();

    // Стохастический метод.
//    TerminationMethod *terminationMethod = new TerminationMethodProb1(pow(10, -6));
//    TerminationMethod *terminationMethod = new TerminationMethodProb2(10000);
//    TerminationMethod *terminationMethod = new TerminationMethodProb3(10000);
//    OptimizationMethod *optimizationMethod = new OptimizationMethodProb(function, x_0, aria, terminationMethod);
    // Стохастический метод.

    // Градиент.
//    TerminationMethod *terminationMethod = new TerminationMethodProb4(pow(10, -4));
    TerminationMethod *terminationMethod = new TerminationMethodProb5(pow(10, -4));
//    TerminationMethod *terminationMethod = new TerminationMethodProb6(pow(10, -4));
    OptimizationMethod *optimizationMethod = new OptimizationMethodGrad(function, x_0, aria, terminationMethod);
    // Градиент.

    optimizationMethod->optimization();
    std::cout << optimizationMethod->getSequenceOfX_i().back()[0] << " " <<
                 optimizationMethod->getSequenceOfX_i().back()[1] << " " <<
                 optimizationMethod->getSequenceOfX_i().back()[2] << " " <<
                 optimizationMethod->getSequenceOfX_i().back()[3] << " " << std::endl <<
                 optimizationMethod->getSequenceOfF_i().back() << " " <<
                 optimizationMethod->getNumberOfIterations() << std::endl;


    return 0;
}
