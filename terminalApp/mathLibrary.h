#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>

class Function {
protected:
    int dimensions;
    std::vector<double> x;
    double F;

public:
    Function() = default;
    explicit Function(int dimensions);
    int getDimensions();
    std::vector<double> getX();
    double getF();
    virtual double calculation(std::vector<double> x) = 0;
};

class Function1 : public Function {
public:
    Function1();
    double calculation(std::vector<double> x) override; // (x+1)^2 + (y+1)^2
};

class Area {
private:
    std::vector<std::pair<double, double>> box;

public:
    Area() = default;
    explicit Area(std::vector<std::pair<double, double>> box);
    std::vector<std::pair<double, double>> getBox();
};

// Что происходит далее. Мне нужен абстрактный класс остановки оптимизации, наследникам которого
// нужна разная информация о процессе оптимизации и который будет полем класса оптимизации.
// Делать класс терминации вычислений наследником класса метода оптимизации глупо,
// но доступ к его полям все еще нужен. Выход: сделать класс терминайции полем класса метода
// оптимизации, которому побуед подаваться ссылка на текущий метод оптимизации для поступа к его полям.
class OptimizationMethod;

class TerminationMethod {
protected:
    double eps;
    int maxNumberOfIterations;
public:
    TerminationMethod() = default;
    TerminationMethod(double eps, int maxNumberOfIterations);
    double getEps();
    int getMaxNumberOfIterations();
    virtual bool termination(OptimizationMethod *optimizationMethod) = 0;
};

class TerminationMethodProb1 : public TerminationMethod{
public:
    TerminationMethodProb1() = default;
    explicit TerminationMethodProb1(double eps);
    bool termination(OptimizationMethod *optimizationMethod) override;
};

class TerminationMethodProb2 : public TerminationMethod{
public:
    TerminationMethodProb2() = default;
    explicit TerminationMethodProb2(int maxNumberOfIterations);
    bool termination(OptimizationMethod *optimizationMethod) override;
};

class TerminationMethodProb3 : public TerminationMethod{
public:
    TerminationMethodProb3() = default;
    explicit TerminationMethodProb3(int maxNumberOfIterations);
    bool termination(OptimizationMethod *optimizationMethod) override;
};

//class TerminationMethodProb4 : public TerminationMethod{
//public:
//    TerminationMethodProb4() = default;
//    explicit TerminationMethodProb4(double eps);
//    bool termination(OptimizationMethod *optimizationMethod) override;
//};

class TerminationMethodProb5 : public TerminationMethod{
public:
    TerminationMethodProb5() = default;
    explicit TerminationMethodProb5(double eps);
    bool termination(OptimizationMethod *optimizationMethod) override;
};

class TerminationMethodProb6 : public TerminationMethod{
public:
    TerminationMethodProb6() = default;
    explicit TerminationMethodProb6(double eps);
    bool termination(OptimizationMethod *optimizationMethod) override;
};

class OptimizationMethod {
//    friend bool TerminationMethod::termination(OptimizationMethod &optimizationMethod);
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
    OptimizationMethod(Function *function, std::vector<double> x_0, Area aria,
                       TerminationMethod *terminationMethod);
    std::vector<std::vector<double>> getSequenceOfX_i();
    std::vector<double> getSequenceOfF_i();
    Function* getFunction();
    Area getArea();
    TerminationMethod* getTerminationMethod();
    int getNumberOfIterations();
    int getNumberOfIterationsSinceTheLastImprovement();
    virtual void optimization() = 0;
};

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
    OptimizationMethodProb(Function *function, std::vector<double> x_0, Area area,
                           TerminationMethod *terminationMethod);
    void optimization() override;
};

class  OptimizationMethodGrad : public OptimizationMethod {
private:
    std::vector<double> p;
    double a;

public:
    OptimizationMethodGrad() = default;
    OptimizationMethodGrad(Function *function, std::vector<double> x_0, Area area,
                           TerminationMethod *terminationMethod);
    void pCorrect();
    void linearSearchOfMin(double eps = pow(10, -2));
    std::vector<std::pair<std::vector<double>, std::vector<double>>> pSplit(int numberOfSubvectors = 10000);
    std::pair<std::vector<double>, double> dichotomyMethod(std::pair<std::vector<double>, std::vector<double>> vector,
                                                           double eps = pow(10, -5));
    void optimization() override;
};

double partialDerivative(Function *function, int axis, std::vector<double> x, double deltaX = pow(10, -5));
std::vector<double> antiGradient(Function *function, std::vector<double> x, double deltaX = pow(10, -5));



