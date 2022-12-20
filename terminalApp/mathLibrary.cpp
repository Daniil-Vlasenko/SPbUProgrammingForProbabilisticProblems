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
    F = (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
    return F;
}
//----------------------------------------------------------------------------------------------------
Function2::Function2() : Function(2) {}

double Function2::calculation(std::vector<double> x) {
    this->x = x;
    F = std::pow(x[0], 2) * std::pow(x[1], 2) + std::pow(x[1] + 1, 2);
    return F;
}
//----------------------------------------------------------------------------------------------------
Function3::Function3() : Function(2) {}

double Function3::calculation(std::vector<double> x) {
    this->x = x;
    F = (1.5 - x[0] + x[0] * x[1]) * (1.5 - x[0] + x[0] * x[1]) + (2.25 - x[0] + x[0] * x[1] * x[1]) *
            (2.25 - x[0] + x[0] * x[1] * x[1]) + (2.625 - x[0] + x[0] * x[1] * x[1] * x[1]) *
            (2.625 - x[0] + x[0] * x[1] * x[1] * x[1]);
    return F;
}
//----------------------------------------------------------------------------------------------------
Function4::Function4() : Function(3) {}

double Function4::calculation(std::vector<double> x) {
    this->x = x;
    F = 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (x[0] - 1) * (x[0] - 1) +
        100 * (x[2] - x[1] * x[1]) * (x[2] - x[1] * x[1]) + (x[1] - 1) * (x[1] - 1);
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
TerminationMethodProb1::TerminationMethodProb1(double eps, int maxNumberOfIterations)
: TerminationMethod(eps, maxNumberOfIterations) {}

bool TerminationMethodProb1::termination(OptimizationMethod *optimizationMethod) {
    int numberOfIterations = optimizationMethod->getSequenceOfF_i().size();
    if (numberOfIterations == 1)
        return false;
    if(numberOfIterations >= maxNumberOfIterations)
        return true;
    double lastF = optimizationMethod->getSequenceOfF_i()[numberOfIterations - 1],
    penultimateF = optimizationMethod->getSequenceOfF_i()[numberOfIterations - 2];
    return (lastF < penultimateF) && (penultimateF - lastF < eps);
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb2::TerminationMethodProb2(int maxNumberOfIterations)
: TerminationMethod(0, maxNumberOfIterations) {}

bool TerminationMethodProb2::termination(OptimizationMethod *optimizationMethod) {
    return optimizationMethod->getNumberOfIterations() >= maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodProb3::TerminationMethodProb3(int maxNumberOfIterations)
: TerminationMethod(0, maxNumberOfIterations) {}

bool TerminationMethodProb3::termination(OptimizationMethod *optimizationMethod) {
    return optimizationMethod->getNumberOfIterationsSinceTheLastImprovement() >= maxNumberOfIterations;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodGrad1::TerminationMethodGrad1(double eps, int maxNumberOfIterations)
: TerminationMethod(eps, maxNumberOfIterations) {}

bool TerminationMethodGrad1::termination(OptimizationMethod *optimizationMethod) {
    if(optimizationMethod->getNumberOfIterations() >= maxNumberOfIterations)
        return true;
    std::vector<double> p = antiGradient(optimizationMethod->getFunction(),
                                            optimizationMethod->getSequenceOfX_i().back(), eps / 10);
    int dimensions = optimizationMethod->getFunction()->getDimensions();
    bool isExtremum = true;
    for(int i = 0; i < dimensions; ++i) {
        isExtremum = std::abs(p[i]) < eps && isExtremum;
    }
    return isExtremum;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodGrad2::TerminationMethodGrad2(double eps, int maxNumberOfIterations)
: TerminationMethod(eps, maxNumberOfIterations) {}

bool TerminationMethodGrad2::termination(OptimizationMethod *optimizationMethod) {
    std::vector<std::vector<double>> sequenceOfX_i = optimizationMethod->getSequenceOfX_i();
    int size = sequenceOfX_i.size();
    if(size == 1)
        return false;
    if(optimizationMethod->getNumberOfIterations() >= maxNumberOfIterations)
        return true;
    int dimensions = optimizationMethod->getFunction()->getDimensions();
    std::vector<double> x1 = sequenceOfX_i[size - 1], x2 = sequenceOfX_i[size - 2];
    double tmp = 0;
    for(int i = 0; i < dimensions; ++i) {
        x1[i] -= x2[i];
        tmp += x1[i] * x1[i];
    }
    return std::sqrt(tmp) < eps;
}
//----------------------------------------------------------------------------------------------------
TerminationMethodGrad3::TerminationMethodGrad3(double eps, int maxNumberOfIterations)
: TerminationMethod(eps, maxNumberOfIterations) {};

bool TerminationMethodGrad3::termination(OptimizationMethod *optimizationMethod) {
    std::vector<double> sequenceOfF_i = optimizationMethod->getSequenceOfF_i();
    int size = sequenceOfF_i.size();
    if(size == 1)
        return false;
    if(optimizationMethod->getNumberOfIterations() >= maxNumberOfIterations)
        return true;
    return std::abs((sequenceOfF_i[size - 1] - sequenceOfF_i[size - 2]) / sequenceOfF_i[size - 1]) < eps;
}
//----------------------------------------------------------------------------------------------------
OptimizationMethod::~OptimizationMethod() {
    delete function;
    delete terminationMethod;
}

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
                       TerminationMethod *terminationMethod, double p, double b, double a)
: OptimizationMethod(function, x_0, area, terminationMethod), p(p), b1(b), b2(b), a(a),
seed(std::chrono::system_clock::now().time_since_epoch().count()), generator(seed), distribution(0, 1) {
    std::vector<std::pair<double, double>> box = area.getBox();
    int dimensions = function->getDimensions();


    if(b == -1) {
        b1 = box[0].second - box[0].first;
        for (int i = 1; i < dimensions; ++i) {
            b1 = box[i].second - box[i].first < b1 ? box[i].second - box[i].first : b1;
        }
        b1 /= 10;
        b2 = b1;
    }
}

void OptimizationMethodProb::optimization() {
    numberOfIterations = 0;
    numberOfIterationsSinceTheLastImprovement = 0;
    int dimensions = function->getDimensions();
    std::vector<std::pair<double, double>> box = area.getBox();
    bool isInSmallArea = false;
    while(!terminationMethod->termination(this)) {
        ++numberOfIterations;
        ++numberOfIterationsSinceTheLastImprovement;
        std::vector<double> newX;
        if(1 - p > distribution(generator)) { // Генерациия равномерного распределения во всем D.
            for(int i = 0; i < dimensions; ++i) {
                double min = box[i].first, max = box[i].second;
                newX.push_back(distribution(generator) * (max - min) + min);
            }
            isInSmallArea = false;
        }
        else { // Генерация в пересечении D и B(x_n, b2)
            for(int i = 0; i < dimensions; ++i) {
                double min = sequenceOfX_i.back()[i] - b2 > box[i].first ? sequenceOfX_i.back()[i] - b2 : box[i].first,
                    max = sequenceOfX_i.back()[i] + b2 < box[i].second ? sequenceOfX_i.back()[i] + b2 : box[i].second;
                newX.push_back(distribution(generator) * (max - min) + min);
            }
            isInSmallArea = true;
        }
        double newF;
        if((newF = function->calculation(newX)) < sequenceOfF_i.back()) {
            if(isInSmallArea) {
                b2 *= a;
            }
            else  {
                b2 = b1;
            }
//            std::cout << "b1: " << b1 << "; b2: " << b2 << "; isInSmallArea: " << isInSmallArea << std::endl;
            sequenceOfF_i.push_back(newF);
            sequenceOfX_i.push_back(newX);
            numberOfIterationsSinceTheLastImprovement = 0;
        }
    }
}
//----------------------------------------------------------------------------------------------------
OptimizationMethodGrad::OptimizationMethodGrad(Function *function, std::vector<double> x_0, Area area,
                                               TerminationMethod *terminationMethod)
: OptimizationMethod(function, x_0, area, terminationMethod) {
    p.resize(function->getDimensions(), 0);
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

std::vector<std::pair<std::vector<double>, std::vector<double>>> OptimizationMethodGrad::pSplit(int numberOfSubvectors) {
    std::vector<std::pair<std::vector<double>, std::vector<double>>> result;
    std::vector<double> x_n = sequenceOfX_i.back();
    std::pair<std::vector<double>, std::vector<double>> subVector;
    subVector.first = x_n;
    subVector.second = x_n;
    int dimensions = function->getDimensions();
    for(int i = 0; i < numberOfSubvectors; ++i) {
        for(int j = 0; j < dimensions; ++j) {
            subVector.second[j] = subVector.first[j] + p[j] * 1 / numberOfSubvectors;
        }
        result.push_back(subVector);
        subVector.first = subVector.second;
    }
    return result;
}

std::pair<std::vector<double>, double> OptimizationMethodGrad::dichotomyMethod(
        std::pair<std::vector<double>, std::vector<double>> vector, double eps) {
    std::pair<std::vector<double>, double> result = {vector.first, 0};
    int dimensions = function->getDimensions();
    double l = 0, r = 1, m, m1, m2;
    while(r - l > eps) {
        m = (l + r) / 2, m1 = m - eps / 2, m2 = m + eps / 2;
        std::vector<double> x1 = vector.first, x2 = vector.first;
        for(int i = 0; i < dimensions; ++i) {
            x1[i] = vector.first[i] + (vector.second[i] - vector.first[i]) * m1;
            x2[i] = vector.first[i] + (vector.second[i] - vector.first[i]) * m2;
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
    for(int i = 0; i < dimensions; ++i) {
        result.first[i] += (vector.second[i] - vector.first[i]) * m;
    }
    result.second = function->calculation(result.first);

    return result;
}

void OptimizationMethodGrad::optimization() {
    numberOfIterations = 0;
    numberOfIterationsSinceTheLastImprovement = 0;
    int dimensions = function->getDimensions();
    double eps = terminationMethod->getEps();
    // Если находимся в экстремальной точке, завершаем алгоритм.
    p = antiGradient(function, sequenceOfX_i.back(), eps / 10);
    bool isExtremum = true;
    for(int i = 0; i < dimensions; ++i) {
        isExtremum = std::abs(p[i]) < eps && isExtremum;
    }
    if(isExtremum) {
        return;
    }
    // Иначе продолжаем алгоритм.
    while(!terminationMethod->termination(this)) {
        // Поиск антиградиента p.
        p = antiGradient(function, sequenceOfX_i.back(), eps / 10);
        // Укорачиваем p через проекцию, если он вылазит за область, или удлинаяем, если лежит внутри области.
        pCorrect();
        // Делим отрезок p на подотрезки, чтобы запустить на каждом метод минимизации.
        std::vector<std::pair<std::vector<double>, std::vector<double>>> subVectors = pSplit();
        // Поиск минимума в направлении p через метод дихотомии.
        int numberOfSubVectors = subVectors.size();
        std::pair<std::vector<double>, double> newXF, tmpXF;
        newXF.second = MAXFLOAT;
        for(int i = 0; i < numberOfSubVectors; ++i) {
            tmpXF = dichotomyMethod(subVectors[i], eps);
            newXF = tmpXF.second < newXF.second ? tmpXF : newXF;
        }

        sequenceOfX_i.push_back(newXF.first);
        sequenceOfF_i.push_back(newXF.second);

        ++numberOfIterations;
        ++numberOfIterationsSinceTheLastImprovement;
    }
}
//----------------------------------------------------------------------------------------------------
double partialDerivative(Function *function, int axis, std::vector<double> x, double deltaX) {
    std::vector<double> x1 = x, x2 = x;
    x1[axis] -= deltaX, x2[axis] += deltaX;
    return (function->calculation(x2) - function->calculation(x1)) / ( 2 * deltaX);
}

std::vector<double> antiGradient(Function *function, std::vector<double> x, double deltaX) {
    std::vector<double> result;
    int dimensions = function->getDimensions();
    for(int i = 0; i < dimensions; ++i) {
        result.push_back(-partialDerivative(function, i, x, deltaX));
    }
    return result;
}

double round_to(double value, double precision)
{
    return std::round(value / precision) * precision;
}

bool isNumber(const std::string& s) {
    long double ld;
    return((std::istringstream(s) >> ld).eof());
}
