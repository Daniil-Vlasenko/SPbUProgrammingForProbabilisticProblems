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
TerminationMethodProb3::TerminationMethodProb3(int maxNumberOfIterations)
: TerminationMethod(0, maxNumberOfIterations) {}

bool TerminationMethodProb3::termination(OptimizationMethod *optimizationMethod) {
    return optimizationMethod->getNumberOfIterationsSinceTheLastImprovement() > maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
//TerminationMethodProb4::TerminationMethodProb4(double eps)
//: TerminationMethod(eps, 100000) {}
//
//bool TerminationMethodProb4::termination(OptimizationMethod *optimizationMethod) {
//    std::vector<double> grad =
//    return ;
//}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb5::TerminationMethodProb5(double eps)
: TerminationMethod(eps, 100000) {}

bool TerminationMethodProb5::termination(OptimizationMethod *optimizationMethod) {
    std::vector<std::vector<double>> sequenceOfX_i = optimizationMethod->getSequenceOfX_i();
    int size = sequenceOfX_i.size();
    if(size == 1)
        return false;
    int dimensions = optimizationMethod->getFunction()->getDimensions();
    std::vector<double> x1 = sequenceOfX_i[size - 1], x2 = sequenceOfX_i[size - 2];
    double tmp = 0;
    for(int i = 0; i < dimensions; ++i) {
        x1[i] -= x2[i];
        tmp += x1[i] * x1[i];
    }
    return std::sqrt(tmp) > eps;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb6::TerminationMethodProb6(double eps)
: TerminationMethod(eps, 100000) {};

bool TerminationMethodProb6::termination(OptimizationMethod *optimizationMethod) {
    int size = optimizationMethod->getSequenceOfF_i().size();
    if(size == 1)
        return false;
    std::vector<double> sequenceOfF_i = optimizationMethod->getSequenceOfF_i();
    return (std::abs((sequenceOfF_i[size - 1] - sequenceOfF_i[size - 2]) / sequenceOfF_i[size - 2]) > eps);
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

//            std::cout << "i: " << numberOfIterations << std::endl << "F_i: " << newF << std::endl << "X_i: ";
//            for(int i = 0; i < dimensions; ++i) {
//                std::cout << newX[i] << " ";
//            }
//            std::cout << std::endl;
        }
    }
}
//----------------------------------------------------------------------------------------------------
OptimizationMethodGrad::OptimizationMethodGrad(Function *function, std::vector<double> x_0, Area area,
                                               TerminationMethod *terminationMethod)
: OptimizationMethod(function, x_0, area, terminationMethod) {
    p.resize(function->getDimensions(), 0);
    a = 0;
}

double OptimizationMethodGrad::partialDerivative(int axis, double deltaX) {
    std::vector<double> x = sequenceOfX_i.back();
    std::vector<double> x1 = x, x2 = x;
    x1[axis] -= deltaX, x2[axis] += deltaX;
    return (function->calculation(x2) - function->calculation(x1)) / ( 2 * deltaX);
}

std::vector<double> OptimizationMethodGrad::antiGradient(double deltaX) {
    std::vector<double> x = sequenceOfX_i.back();
    std::vector<double> result;
    int dimensions = function->getDimensions();
    for(int i = 0; i < dimensions; ++i) {
        result.push_back(-partialDerivative(i, deltaX));
    }
    return result;
}

void OptimizationMethodGrad::pCorrect() {
    std::vector<std::pair<double, double>> box = area.getBox();
    std::vector<double> x_n = sequenceOfX_i.back();
    int dimensions = function->getDimensions();

    // Проверяем нужно укоротить или удлинить вектор.
    bool isVectorInTheArea = true;
    for(int i = 0; i < dimensions; ++i) {
        if(x_n[i] + p[i] < box[i].first || x_n[i] + p[i] > box[i].second) {
            isVectorInTheArea = false;
        }
    }

    // Укорачиваем вектор через проекцию, если необходимо.
    if(!isVectorInTheArea)
        for(int i = 0; i < dimensions; ++i) {
            p[i] = x_n[i] + p[i] < box[i].first ? box[i].first - x_n[i] : p[i];
            p[i] = x_n[i] + p[i] > box[i].second ? box[i].second - x_n[i] : p[i];
        }
    // Удлиняем вектор до конца области, если он лежит внутри области.
    else {
        double tmp = 0;
        for(int i = 0; i < dimensions; ++i) {
            tmp += p[i] * p[i];
        }
        for(int i = 0; i < dimensions; ++i) {
            p[i] /= std::sqrt(tmp);
        }
        double minFraction = MAXFLOAT;
        for(int i = 0; i < dimensions; ++i) {
            if(p[i] > 0) {
                minFraction = (tmp = std::abs((box[i].second - x_n[i]) / p[i])) < minFraction ? tmp : minFraction;
            }
            else {
                minFraction = (tmp = std::abs((x_n[i] - box[i].first) / p[i])) < minFraction ? tmp : minFraction;
            }
        }
        for(int i = 0; i < dimensions; ++i) {
            p[i] *= minFraction;
        }
    }
}

void OptimizationMethodGrad::linearSearchOfMin(double eps) {
    std::vector<double> x_n = sequenceOfX_i.back();
    int dimensions = function->getDimensions();
    std::vector<std::pair<double, double>> box = area.getBox();
    double maxLength = 0;
    for(int i = 0; i < dimensions; ++i) {
        maxLength = box[i].second - box[i].first > maxLength ? box[i].second - box[i].first : maxLength;
    }
    int steps = maxLength / eps;

    std::vector<double> minX = x_n, tmpX = x_n;
    double tmpF;
    double minF = function->calculation(x_n);
    for(int i = 0; i < steps; ++i) {
        for(int j = 0; j < dimensions; ++j) {
            tmpX[j] += eps * p[j];
        }
        if(minF > (tmpF = function->calculation(tmpX))) {
            minF = tmpF;
            minX = tmpX;
        }
    }

    sequenceOfX_i.push_back(minX);
    sequenceOfF_i.push_back(minF);
}

void OptimizationMethodGrad::dichotomyMethod(double eps) {
    std::vector<double> x_n = sequenceOfX_i.back();
    int dimensions = function->getDimensions();
    double l = 0, r = 1, m, m1, m2;
    while(r - l > eps) {
        m = (l + r) / 2, m1 = m - eps / 2, m2 = m + eps / 2;
        std::vector<double> x1 = x_n, x2 = x_n;
        for(int i = 0; i < dimensions; ++i) {
            x1[i] = x_n[i] + p[i] * m1;
            x2[i] = x_n[i] + p[i] * m2;
        }
        double F1 = function->calculation(x1), F2 = function->calculation(x2);
        if ((F2 - F1) / eps > 0) {
            r = m;
        }
        else {
            l = m;
        }
    }
    m = (l + r) / 2;
    std::vector<double> newX = x_n;
    for(int i = 0; i < dimensions; ++i) {
        newX[i] = x_n[i] + p[i] * m;
    }
    sequenceOfX_i.push_back(newX);
    sequenceOfF_i.push_back(function->calculation(newX));
}

void OptimizationMethodGrad::optimization() {
    numberOfIterations = 0;
    numberOfIterationsSinceTheLastImprovement = 0;
    while(!terminationMethod->termination(this)) {
        ++numberOfIterations;
        ++numberOfIterationsSinceTheLastImprovement;

        // Поиск антиградиента p.
        p = antiGradient();
        // Укорачиваем p чере проекцию, если он вылазит за область, или удлинаяем, если лежит внутри области.
        pCorrect();
        // Поиск минимума в направлении p через линейный поиск.
        dichotomyMethod();
    }
}