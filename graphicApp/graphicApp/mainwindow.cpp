#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isOptimise(false)
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
        default:
            function = new Function3();

    }
    int dimensions = function->getDimensions();

    std::vector<double> x_0;
    x_0.push_back(select_function_window.x);
    x_0.push_back(select_function_window.y);

    std::vector<std::pair<double, double>> box;
    std::pair<double, double> b1(select_function_window.x1, select_function_window.x2);
    std::pair<double, double> b2(select_function_window.y1, select_function_window.y2);    
    box.push_back(b1);
    box.push_back(b2);

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

void MainWindow::function_print() {
    QPainter painter;
    painter.begin(this);
}

void MainWindow::area_print() {
    QPainter painter;
    painter.begin(this);

    painter.setPen(QPen(qRgb(66, 135, 245)));
    painter.drawLine(0, 0, 1000, 600);
}

void MainWindow::paintEvent(QPaintEvent *) {
    area_print();
    if(isOptimise)
        function_print();

}

void MainWindow::on_actionRun_triggered()
{
    optimisationMethod = run_calculation();

    isOptimise = true;

    repaint();
}


void MainWindow::on_actionHelp_triggered()
{
    help_window.exec();
}

