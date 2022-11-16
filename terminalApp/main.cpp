#include "mathLibrary.h"

int main() {
    bool repeat = true;
    std::cout << "Finding the minimum of a function, by Daniil Vlasenko.\n";

    while(repeat) {
        Function *function;
        try {
            int functionInt = -1;
            std::cout << "\nSelecting the function.\n1. F = (1-x)^2 + 100(y-x^2)^2, Rosenbrock function;\n"
                         "2. F = x^2 * y^2 + (y + 1)^2;\n"
                         "3. F = (1.5 - x + xy)^2 + (2.25 - x + x * y^2)^2 + (2.625 - x + xy^3)^2, Beale function;\n"
                         "4. F = 100(y -x^2)^2 + (x - 1)^2 + 100(z - y^2)^2 + (y - 1)^2, Rosenbrock function 3d. \n"
                         "Writ down a number of the function: ";
            std::cin >> functionInt;
            switch (functionInt) {
                case 1:
                    function = new Function1();
                    break;
                case 2:
                    function = new Function2();
                    break;
                case 3:
                    function = new Function3();
                    break;
                case 4:
                    function = new Function4();
                    break;
                default:
                    throw(-1);
            }
        }
        catch(...) {
            std::cout << "\nWrong value entered!\n";
            return -1;
        }

        int dimensions = function->getDimensions();
        std::vector<double> x_0(dimensions);
        std::vector<std::pair<double, double>> box(dimensions);
        try {
            std::cout << "\nSelecting the starting point.\nWrite down coordinates of x_{0} with a space: ";
            std::string tmp;
            for (int i = 0; i < dimensions; ++i) {
                std::cin >> tmp;
                x_0[i] = std::stod(tmp);
            }

            std::cout << "\nSelecting the area of minimization.\nWrite down coordinates of boundaries of the minimization area:\n";
            for (int i = 0; i < dimensions; ++i) {
                std::cout << "axis " << i + 1 << ":";
                std::cin >> box[i].first >> box[i].second;
                if (box[i].first > x_0[i] || box[i].second < x_0[i]) {
                    std::cout << "\nThe start point isn't in the minimization area.";
                    throw(-1);
                }
            }
        }
        catch(...) {
            std::cout << "\nWrong value entered!\n";
            return -1;
        }
        Area area(box);

        OptimizationMethod *optimizationMethod;
        TerminationMethod *terminationMethod;
        try {
            int optimisationMethodInt = -1, terminationMethodInt = -1, maxNumberOfIterates = -1;
            double eps = -1;
            std::cout << "\nSelecting the optimisation method.\n1. Gradient descent (derived numerically);\n"
                         "2. Stochastic method.\nWrit down a number of the method: ";
            std::cin >> optimisationMethodInt;
            switch(optimisationMethodInt) {
                case 1:
                    std::cout << "\nSelecting the termination method.\n1. ||grad f(x_{n})|| < eps;\n"
                                 "2. ||x_{n} - x_{n-1}|| < eps.\n3. ||(f(x_{n}) - f(x_{n-1}))/f(x_n)|| < eps.\n"
                                 "Writ down a number of the method: ";
                    std::cin >> terminationMethodInt;
                    std::cout << "Write down eps: ";
                    std::cin >> eps;
                    switch (terminationMethodInt) {
                        case 1:
                            terminationMethod = new TerminationMethodGrad1(eps);
                            break;
                        case 2:
                            terminationMethod = new TerminationMethodGrad2(eps);
                            break;
                        case 3:
                            terminationMethod = new TerminationMethodGrad3(eps);
                            break;
                        default:
                            throw(-1);
                    }
                    optimizationMethod = new OptimizationMethodGrad(function, x_0, area, terminationMethod);
                    break;
                case 2:
                    double p, b, a;
                    std::cout << "\nSelect parameters p, b and a: ";
                    std::cin >> p >> b >> a;
                    std::cout << "\nSelecting the termination method.\n"
                                 "1. ||f(x_{n+j}) − f(x_{n})| < eps, j = min{m: f(x_{n+m}) < f(x_{n})};\n"
                                 "2. Number of iterations is greater than n.\n"
                                 "3. Number of iterations since the last improvement is greater than n.\n"
                                 "Writ down a number of the method: ";
                    std::cin >> terminationMethodInt;
                    switch (terminationMethodInt) {
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
                        default:
                            throw (-1);
                    }
                    optimizationMethod = new OptimizationMethodProb(function, x_0, area, terminationMethod, p, b, a);
                    break;
                default:
                    throw(-1);
            }
        }
        catch(...) {
            std::cout << "\nWrong value entered!\n";
            return -1;
        }

        optimizationMethod->optimization();

        std::cout << "\nMinimum of the function: " << optimizationMethod->getSequenceOfF_i().back() <<
                  "\nMinimum point of the function: ";
        std::vector<double> x_n = optimizationMethod->getSequenceOfX_i().back();
        for (int i = 0; i < dimensions; ++i) {
            std::cout << x_n[i] << " ";
        }
        std::cout << "\nNumber of iterations: " << optimizationMethod->getNumberOfIterations();

        char input;
        std::cout << "\n\nWould you like to repeat? (Y/n): ";
        std::cin >> input;
        if(input != 'y' && input != 'Y') {
            repeat = false;
        }
    }

    return 0;
}
