#include "mathLibrary.h"

int main() {
    std::cout << "Finding the minimum of a function, by Daniil Vlasenko.\n\n";
    int functionInt = -1;
    std::cout << "Selecting the function.\n1. F = (x+1)^2 + (y+1)^2;\n2. F = x^2 * y^2 + y^5 * cos(x);\n"
                 "3. F = x^2 + y * sin(y) * cos(y);\n4. F = cos(x) + cos(y) + cos(z) + cos(t).\n"
                 "Writ down a number of the function: ";
    std::cin >> functionInt;
    Function *function;
    switch(functionInt) {
        case 1: function = new Function1(); break;
        case 2: function = new Function2(); break;
        case 3: function = new Function3(); break;
        case 4: function = new Function4(); break;
        default: return -1;
    }

    int dimensions = function->getDimensions();
    std::vector<double> x_0(dimensions);
    std::cout << "\nSelecting the starting point.\nWrite down coordinates of x_{0} with a space: ";
    for(int i = 0; i < dimensions; ++i)
        std::cin >> x_0[i];

    std::vector<std::pair<double, double>> box(dimensions);
    std::cout << "\nSelecting the area of minimisation.\nWrite down coordinates of boundaries of the minimization area:\n";
    for(int i = 0; i < dimensions; ++i) {
        std::cout << "axis " << i + 1 << ":";
        std::cin >> box[i].first >> box[i].second;
    }
    Area area(box);

    int optimisationMethodInt = -1, terminationMethodInt = -1, maxNumberOfIterates = - 1;
    double eps = -1;
    std::cout << "\nSelecting the optimisation method.\n1. Gradient descent (derived numerically);\n"
                 "2. Stochastic method.\nWrit down a number of the method: ";
    std::cin >> optimisationMethodInt;
    OptimizationMethod *optimizationMethod;
    TerminationMethod *terminationMethod;
    if(optimisationMethodInt == 1) {
        std::cout << "\nSelecting the termination method.\n1. ||grad f(x_{n})|| < eps;\n"
                     "2. ||x_{n} - x_{n-1}|| < eps.\n3. ||(f(x_{n}) - f(x_{n-1})/f(x_n)|| < eps.\n"
                     "Writ down a number of the method: ";
        std::cin >> terminationMethodInt;
        std::cout << "Write down eps: ";
        std::cin >> eps;
        switch(terminationMethodInt) {
            case 1: terminationMethod = new TerminationMethodGrad1(eps); break;
            case 2: terminationMethod = new TerminationMethodGrad2(eps); break;
            case 3: terminationMethod = new TerminationMethodGrad3(eps); break;
            default: return -1;
        }
        optimizationMethod = new OptimizationMethodGrad(function, x_0, area, terminationMethod);
    }
    else if(optimisationMethodInt == 2) {
        std::cout << "\nSelecting the termination method.\n"
                     "1. ||f(x_{n+j}) − f(x_{n})| < eps, j = min{m: f(x_{n+m}) < f(x_{n})};\n"
                     "2. Number of iterations is greater than n.\n"
                     "3. Number of iterations since the last improvement is greater than n.\n"
                     "Writ down a number of the method: ";
        std::cin >> terminationMethodInt;
        switch(terminationMethodInt) {
            case 1:
                std::cout << "Write down eps: ";
                std::cin >> eps;
                terminationMethod = new TerminationMethodProb1(eps);
                break;
            case 2:
                std::cout << "Write down n: ";
                std::cin >> maxNumberOfIterates;
                terminationMethod = new TerminationMethodProb2(maxNumberOfIterates);
                break;
            case 3:
                std::cout << "Write down n: ";
                std::cin >> maxNumberOfIterates;
                terminationMethod = new TerminationMethodProb3(maxNumberOfIterates);
                break;
            default: return -1;
        }
        optimizationMethod = new OptimizationMethodProb(function, x_0, area, terminationMethod);
    }





    return 0;
}
