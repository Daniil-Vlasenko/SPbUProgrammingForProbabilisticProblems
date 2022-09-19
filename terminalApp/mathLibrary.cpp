#include "mathLibrary.h"


Function::Function(int dimensions) : dimensions(dimensions) {}

int Function::getDimensions() {
    return dimensions;
}

std::vector<double> Function::getX() {
    return x;
}

double Function::getF(){
    return F;
}
//----------------------------------------------------------------------------------------------------
Function1::Function1() : Function(2) {}

double Function1::calculation(std::vector<double> x) {
    this->x = x;
    F = (x[0] + 1) * (x[0] + 1) + (x[1] + 1) * (x[1] + 1);
    return F;
}
//----------------------------------------------------------------------------------------------------
Area::Area(std::vector<std::pair<double, double>> box) : box(box) {}

std::vector<std::pair<double, double>> Area::getBox() {
    return box;
}
//----------------------------------------------------------------------------------------------------
TerminationMethod::TerminationMethod(double eps, int maxNumberOfIterations)
: eps(eps), maxNumberOfIterations(maxNumberOfIterations) {}

double TerminationMethod::getEps() {
    return eps;
}

int TerminationMethod::getMaxNumberOfIterations() {
    return maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb1::TerminationMethodProb1(double eps) : TerminationMethod(eps, 0) {}

bool TerminationMethodProb1::termination(OptimizationMethod *optimizationMethod) {
    int numberOfIterations = optimizationMethod->getSequenceOfF_i().size();
    double lastF = optimizationMethod->getSequenceOfF_i()[numberOfIterations],
    penultimateF = optimizationMethod->getSequenceOfF_i()[numberOfIterations - 1];
    return (lastF < penultimateF) && (penultimateF - lastF < eps);
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb2::TerminationMethodProb2(int maxNumberOfIterations)
: TerminationMethod(0, maxNumberOfIterations) {}

bool TerminationMethodProb2::termination(OptimizationMethod *optimizationMethod) {
    return optimizationMethod->getNumberOfIterations() > maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb3::TerminationMethodProb3(int maxNumberOfIterations) :
TerminationMethod(0, maxNumberOfIterations) {}

bool TerminationMethodProb3::termination(OptimizationMethod *optimizationMethod) {
    return optimizationMethod->getNumberOfIterationsSinceTheLastImprovement() > maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
OptimizationMethod::OptimizationMethod(Function *function, std::vector<double> x_0, Area aria,
                                       TerminationMethod *terminationMethod)
: function(function), area(aria), terminationMethod(terminationMethod), numberOfIterations(0),
  numberOfIterationsSinceTheLastImprovement(0) {
  sequenceOfX_i.push_back(x_0);
  sequenceOfF_i.push_back(function->calculation(x_0));
}

std::vector<std::vector<double>> OptimizationMethod::getSequenceOfX_i() {
    return sequenceOfX_i;
}

std::vector<double> OptimizationMethod::getSequenceOfF_i() {
    return sequenceOfF_i;
}

Function* OptimizationMethod::getFunction() {
    return function;
}

Area OptimizationMethod::getArea() {
    return area;
}

TerminationMethod* OptimizationMethod::getTerminationMethod() {
    return terminationMethod;
}

int OptimizationMethod::getNumberOfIterations() {
    return numberOfIterations;
}

int OptimizationMethod::getNumberOfIterationsSinceTheLastImprovement() {
    return numberOfIterationsSinceTheLastImprovement;
}
//----------------------------------------------------------------------------------------------------
OptimizationMethodProb::OptimizationMethodProb(Function *function, std::vector<double> x_0, Area area,
                       TerminationMethod *terminationMethod)
: OptimizationMethod(function, x_0, area, terminationMethod),
seed(std::chrono::system_clock::now().time_since_epoch().count()), generator(seed), distribution(0, 1) {
    // Проверка принадлежности начальной точки области минимизации функции.
    std::vector<std::pair<double, double>> box = area.getBox();
    assert(!box.empty());
    int dimensions = function->getDimensions();
    for(int i = 0; i < dimensions; ++i) {
        assert(x_0[i] > box[i].first && x_0[i] < box[i].second );
    }

    p = 0.5;
    a = 0.5;
    b1 = box[0].second - box[0].first;
    for(int i = 1; i < dimensions; ++i) {
        b1 = box[i].second - box[i].first < b1 ? box[i].second - box[i].first : b1;
    }
    b1 /= 10;
    b2 = b1;
}

void OptimizationMethodProb::optimization() {
    numberOfIterations = 0;
    numberOfIterationsSinceTheLastImprovement = 0;
    int dimensions = function->getDimensions();
    std::vector<std::pair<double, double>> box = area.getBox();
    sequenceOfF_i.push_back(function->calculation(sequenceOfX_i[0]));
    while(!terminationMethod->termination(this)) {
        ++numberOfIterations;
        ++numberOfIterationsSinceTheLastImprovement;
        std::vector<double> newX;
        if(1 - p < distribution(generator)) { // Генерациия равномерного распределения во всем D.
            for(int i = 0; i < dimensions; ++i) {
                double min = box[i].first, max = box[i].second;
                newX.push_back(distribution(generator) * (max - min) + min);
            }
            b2 = b1;
        }
        else { // Генерация в пересечении D и B(x_n, b2)
            for(int i = 0; i < dimensions; ++i) {
                double min = sequenceOfX_i.back()[i] - b2 > box[i].first ? sequenceOfX_i.back()[i] - b2 : box[i].first,
                    max = sequenceOfX_i.back()[i] + b2 < box[i].second ? sequenceOfX_i.back()[i] + b2 : box[i].second;
                newX.push_back(distribution(generator) * (max - min) + min);
            }
            b2 *= a;
        }
        double newF;
        if((newF = function->calculation(newX)) < sequenceOfF_i.back()) {
            sequenceOfF_i.push_back(newF);
            sequenceOfX_i.push_back(newX);
            numberOfIterationsSinceTheLastImprovement = 0;

            std::cout << "i: " << numberOfIterations << std::endl << "F_i: " << newF << std::endl << "X_i: ";
            for(int i = 0; i < dimensions; ++i) {
                std::cout << newX[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}