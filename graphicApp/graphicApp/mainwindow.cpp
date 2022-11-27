#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSelect_function_triggered()
{
    select_function_window.exec();
}


void MainWindow::on_actionSelect_method_triggered()
{
    select_method_window.exec();
}

OptimizationMethod* MainWindow::run_calculation() {
    Function *function;
    switch(select_function_window.functionId) {
        case 0:
            function = new Function1();
            break;
        case 1:
            function = new Function2();
            break;
        case 2:
            function = new Function3();
            break;
        default:
            function = new Function4();
    }
    int dimensions = function->getDimensions();

    std::vector<double> x_0;
    x_0.push_back(select_function_window.x);
    x_0.push_back(select_function_window.y);
    if(dimensions > 2) {
        x_0.push_back(select_function_window.z);
    }

    std::vector<std::pair<double, double>> box;
    std::pair<double, double> b1(select_function_window.x1, select_function_window.x2);
    std::pair<double, double> b2(select_function_window.y1, select_function_window.y2);
    std::pair<double, double> b3(select_function_window.z1, select_function_window.z2);
    box.push_back(b1);
    box.push_back(b2);
    if(dimensions > 2) {
        box.push_back(b3);
    }
    Area area(box);

    OptimizationMethod *optimizationMethod;
    TerminationMethod *terminationMethod;
    if(select_method_window.optimisationMethodId == 0)  {
        switch(select_method_window.terminationMethodIdP) {
            case 0:
                terminationMethod = new TerminationMethodProb1(select_method_window.epsP);
                break;
            case 1:
                terminationMethod = new TerminationMethodProb2(select_method_window.numberOfiterations);
                break;
            default:
                terminationMethod = new TerminationMethodProb3(select_method_window.numberOfiterations);
        }
        optimizationMethod = new OptimizationMethodProb(function, x_0, area, terminationMethod,
                                                        select_method_window.p, select_method_window.b,
                                                        select_method_window.a);
    }
    else {
        switch(select_method_window.terminationMethodIdG) {
            case 0:
                terminationMethod = new TerminationMethodGrad1(select_method_window.epsG);
                break;
            case 1:
                terminationMethod = new TerminationMethodGrad2(select_method_window.epsG);
                break;
            default:
                terminationMethod = new TerminationMethodGrad3(select_method_window.epsG);
        }
        optimizationMethod = new OptimizationMethodGrad(function, x_0, area, terminationMethod);
    }

    optimizationMethod->optimization();

    return optimizationMethod;
}

std::string MainWindow::run_text() {
    std::string result = "";

    switch(select_function_window.functionId) {
        case 0:
            result += "F = (1-x)^2 + 100(y-x^2)^2;\n";
            break;
        case 1:
            result += "F = x^2 * y^2 + (y + 1)^2;\n";
            break;
        case 2:
            result += "F = (1.5 - x + xy)^2 + (2.25 - x + x * y^2)^2 + (2.625 - x + xy^3)^2;\n";
            break;
        default:
            result += "F = 100(y -x^2)^2 + (x - 1)^2 + 100(z - y^2)^2 + (y - 1)^2;\n";
    }
    int dimensions = optimisationMethod->getFunction()->getDimensions();

    if(dimensions <3) {
        result += "Start point: (" + std::to_string(select_function_window.x) + ", " +
                std::to_string(select_function_window.y) + ");";
    }
    else {
        result += "Start point: (" + std::to_string(select_function_window.x) + ", " +
                std::to_string(select_function_window.y) + ", " +
                std::to_string(select_function_window.z) + ");";
    }

    if(dimensions <3) {
        result += "Optimisation area: (x1, y1) = (" + std::to_string(select_function_window.x1) + ", " +
                std::to_string(select_function_window.y1)+ "), (x2, y2) = (" +
                std::to_string(select_function_window.x1) + ", " +std::to_string(select_function_window.y2) + ")\n;";
    }
    else {
        result += "Optimisation area: (x1, y1, z1) = (" + std::to_string(select_function_window.x1) + ", " +
                std::to_string(select_function_window.y1) + ", " + std::to_string(select_function_window.z1) +
                "), (x2, y2, z3) = (" + std::to_string(select_function_window.x1) + ", " +
                std::to_string(select_function_window.y2) + ", " + std::to_string(select_function_window.z2) + ")\n;";
    }

    if(select_method_window.optimisationMethodId == 0)  {
        result += "Probability optimisation method with parameters p = " + std::to_string(select_method_window.p) +
                ", b = " + std::to_string(select_method_window.b) + ", a = " +
                std::to_string(select_method_window.a) + ";\n";

        switch(select_method_window.terminationMethodIdP) {
            case 0:
                result += "Termination method: ||f(x_{n+j}) − f(x_{n})| < eps, j = min{m: f(x_{n+m}) < f(x_{n})} "
                          "with eps =" + std::to_string(select_method_window.epsP) + ";\n";
                break;
            case 1:
                result += "Termination method: Number of iterations is greater than n "
                          "with n =" + std::to_string(select_method_window.numberOfiterations) + ";\n";
                break;
            default:
                result += "Termination method: Number of iterations since the last improvement is greater than n "
                          "with n =" + std::to_string(select_method_window.numberOfiterations) + ";\n";
        }
    }
    else {
        result += "Gradient optimisation method;\n";
        switch(select_method_window.terminationMethodIdG) {
            case 0:
                result += "Termination method: ||grad f(x_{n})|| < eps "
                          "with eps =" + std::to_string(select_method_window.epsG) + ";\n";
                break;
            case 1:
                result += "Termination method: ||x_{n} - x_{n-1}|| < eps "
                          "with eps =" + std::to_string(select_method_window.epsG) + ";\n";
                break;
            default:
                result += "Termination method: ||(f(x_{n}) - f(x_{n-1}))/f(x_n)|| < eps "
                          "with eps =" + std::to_string(select_method_window.epsG) + ";\n";
        }
    }

    return result;
}

void MainWindow::on_actionRun_triggered()
{
    optimisationMethod = run_calculation();
    std::string result = run_text();
    ui->label_Text_style->setText(QString::fromStdString(result));
}


void MainWindow::on_actionHelp_triggered()
{
    help_window.exec();
}

