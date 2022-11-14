#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

/**
 * @brief Abstract class of the minimizing function.
 **/
class Function {
protected:
    int dimensions;
    std::vector<double> x;
    double F;

public:
    Function() = default;
    virtual ~Function() = default;
    explicit Function(int dimensions);
    int getDimensions();
    std::vector<double> getX();
    double getF();
    /**
     * @brief Abstract function for calculation of the function.
     */
    virtual double calculation(std::vector<double> x) = 0;
};

/**
 * @brief F = (1-x)^2 + 100(y-x^2)^2, Rosenbrock function. Minimum F is F(1,1) = 0.
 **/
class Function1 : public Function {
public:
    Function1();
    /**
     * @brief Calculation of the function.
     */
    double calculation(std::vector<double> x) override;
};

/**
 * @brief F = x^2 * y^2 + (y + 1)^2. Minimum F is F(0,-1) = 0.
 **/
class Function2 : public Function {
public:
    Function2();
    /**
     * @brief Calculation of the function.
     */
    double calculation(std::vector<double> x) override;
};

/**
 * @brief F = (1.5 - x + xy)^2 + (2.25 - x + x * y^2)^2 + (2.625 - x + xy^3)^2, Beale function. Minimum F(3,0.5) = 0.
 **/
class Function3 : public Function {
public:
    Function3();
    /**
     * @brief Calculation of the function.
     */
    double calculation(std::vector<double> x) override;
};

/**
 * @brief F = 30 + (x^2 - 10 * cos(2 * pi * x)) + (y^2 - 10 * cos(2 * pi * y)) + (z^2 - 10 * cos(2 * pi * z)),
 * Rastrigin function. Minimum F(0,0,0) = 0.
 **/
class Function4 : public Function {
public:
    Function4();
    /**
     * @brief Calculation of the function.
     */
    double calculation(std::vector<double> x) override;
};

/**
 * @brief Class of the minimization area.
 **/
class Area {
private:
    std::vector<std::pair<double, double>> box;

public:
    Area() = default;
    explicit Area(std::vector<std::pair<double, double>> box);
    std::vector<std::pair<double, double>> getBox();
};

class OptimizationMethod;

/**
 * @brief Abstract class of the termination method.
 * @details Since the termination method is a field of an optimization method and it needs information about it's
 * parent class, it's main function takes as it's argument a pointer to the optimization method whose field the
 * termination method is.
 **/
class TerminationMethod {
protected:
    double eps;
    int maxNumberOfIterations;
public:
    TerminationMethod() = default;
    virtual ~TerminationMethod() = default;
    TerminationMethod(double eps, int maxNumberOfIterations);
    double getEps();
    int getMaxNumberOfIterations();
    /**
     * @brief Abstract function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    virtual bool termination(OptimizationMethod *optimizationMethod) = 0;
};

/**
 * @brief Class of the termination method: ||f(x_{n+j}) − f(x_{n})| < eps, j = min{m: f(x_{n+m}) < f(x_{n})}.
 **/
class TerminationMethodProb1 : public TerminationMethod {
public:
    TerminationMethodProb1() = default;
    explicit TerminationMethodProb1(double eps, int maxNumberOfIterations = 2000);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Class of the termination method: number of iterations is greater than n.
 **/
class TerminationMethodProb2 : public TerminationMethod {
public:
    TerminationMethodProb2() = default;
    explicit TerminationMethodProb2(int maxNumberOfIterations);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Class of the termination method: number of iterations since the last improvement is greater than n.
 **/
class TerminationMethodProb3 : public TerminationMethod {
public:
    TerminationMethodProb3() = default;
    explicit TerminationMethodProb3(int maxNumberOfIterations);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Class of the termination method: ||grad f(x_{n})|| < eps.
 **/
class TerminationMethodGrad1 : public TerminationMethod {
public:
    TerminationMethodGrad1() = default;
    explicit TerminationMethodGrad1(double eps, int maxNumberOfIterations = 2000);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Class of the termination method: ||x_{n} - x_{n-1}|| < eps.
 **/
class TerminationMethodGrad2 : public TerminationMethod {
public:
    TerminationMethodGrad2() = default;
    explicit TerminationMethodGrad2(double eps, int maxNumberOfIterations = 2000);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Class of the termination method: ||(f(x_{n}) - f(x_{n-1})/f(x_n)|| < eps.
 **/
class TerminationMethodGrad3 : public TerminationMethod {
public:
    TerminationMethodGrad3() = default;
    explicit TerminationMethodGrad3(double eps, int maxNumberOfIterations = 2000);
    /**
     * @brief Function for checking the completion of an optimization method.
     * @param optimizationMethod A pointer to the parent class.
     */
    bool termination(OptimizationMethod *optimizationMethod) override;
};

/**
 * @brief Abstract class of the optimization method.
 **/
class OptimizationMethod {
protected:
    std::vector<std::vector<double>> sequenceOfX_i;
    std::vector<double> sequenceOfF_i;
    Function *function;
    Area area;
    TerminationMethod *terminationMethod;
    int numberOfIterations;
    int numberOfIterationsSinceTheLastImprovement;

public:
    OptimizationMethod() = default;
    virtual ~OptimizationMethod();
    OptimizationMethod(Function *function, std::vector<double> x_0, Area aria,
                       TerminationMethod *terminationMethod);
    std::vector<std::vector<double>> getSequenceOfX_i();
    std::vector<double> getSequenceOfF_i();
    Function* getFunction();
    Area getArea();
    TerminationMethod* getTerminationMethod();
    int getNumberOfIterations();
    int getNumberOfIterationsSinceTheLastImprovement();
    /**
     * @brief Abstract optimization function.
     */
    virtual void optimization() = 0;
};

/**
 * @brief Class of the probability optimization method.
 **/
class OptimizationMethodProb : public OptimizationMethod {
private:
    unsigned seed;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
    double p;
    double b1, b2;
    double a;

public:
    OptimizationMethodProb() = default;
    /**
     * @brief If the parameter b is not set, it is defined as 0.1 length of the narrowest side of the box.
     * */
    OptimizationMethodProb(Function *function, std::vector<double> x_0, Area area,
                           TerminationMethod *terminationMethod, double p = 0.5, double b = -1, double a = 0.5);
    /**
     * @brief Optimization function.
     */
    void optimization() override;
};

/**
 * @brief Class of the gradient optimization method. The gradient step is ten times
 * smaller than the epsilon taken from the termination method.
 **/
class  OptimizationMethodGrad : public OptimizationMethod {
private:
    std::vector<double> p;
    void pCorrect();
    std::vector<std::pair<std::vector<double>, std::vector<double>>> pSplit(int numberOfSubvectors = 100);
    std::pair<std::vector<double>, double> dichotomyMethod(std::pair<std::vector<double>, std::vector<double>> vector,
                                                           double eps);
public:
    OptimizationMethodGrad() = default;
    OptimizationMethodGrad(Function *function, std::vector<double> x_0, Area area,
                           TerminationMethod *terminationMethod);
    /**
     * @brief Optimization function.
     */
    void optimization() override;
};

double partialDerivative(Function *function, int axis, std::vector<double> x, double deltaX);
std::vector<double> antiGradient(Function *function, std::vector<double> x, double deltaX);