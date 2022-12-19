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

    // Рисуем оси.
    painter.drawLine(50, 100, 970, 100);
    painter.drawLine(50, 100, 50, 570);
    painter.drawLine(965, 105, 970, 100);
    painter.drawLine(965, 95, 970, 100);
    painter.drawLine(45, 565, 50, 570);
    painter.drawLine(55, 565, 50, 570);
    painter.drawText(965, 90, "x");
    painter.drawText(30, 575, "y");
    double x1 = select_function_window.x1;
    double x2 = select_function_window.x2;
    painter.drawText(45, 90, QString::number(x1));
    double y1 = select_function_window.y1;
    double y2 = select_function_window.y2;
    painter.drawText(30, 110, QString::number(y1));
    for(int i = 1; i <= 10; ++i) {
        double x = 50 + 900 / 10 * i,
            y = 100 + 450 / 10 * i;
        double xText = (double) i / 10 * (x2 - x1) + x1,
            yText = (double) i / 10 * (y2 - y1) + y1;

        painter.drawLine(x, 103, x, 97);
        painter.drawText(x - 5, 90, QString::number(xText));
        painter.drawLine(47, y, 53, y);
        painter.drawText(30, y + 5, QString::number(yText));
    }

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

