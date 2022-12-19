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

    // Рисуем кривую.
    double x1 = select_function_window.x1;
    double x2 = select_function_window.x2;
    double y1 = select_function_window.y1;
    double y2 = select_function_window.y2;
    std::vector<std::vector<double>> sequenceOfX_i = optimisationMethod->getSequenceOfX_i();
    int length = sequenceOfX_i.size();
    for(int i = 0; i < length - 1; ++i) {
        painter.drawLine(550 + sequenceOfX_i[i][0] / (x2 - x1) * 900, 325 + sequenceOfX_i[i][1] / (y2 - y1) * 450,
                550 + sequenceOfX_i[i + 1][0] / (x2 - x1) * 900, 325 + sequenceOfX_i[i + 1][1] / (y2 - y1) * 450);
    }
    painter.setPen(QPen(Qt::red, 4));
    painter.drawPoint(550 + sequenceOfX_i[0][0] / (x2 - x1) * 900,
                      325 + sequenceOfX_i[0][1] / (y2 - y1) * 450);
    painter.setPen(QPen(Qt::green, 4));
    painter.drawPoint(550 + sequenceOfX_i.back()[0] / (x2 - x1) * 900,
                      325 + sequenceOfX_i.back()[1] / (y2 - y1) * 450);

}

void MainWindow::axec_print() {
    QPainter painter;
    painter.begin(this);

    painter.drawLine(100, 50, 1020, 50);
    painter.drawLine(25, 100, 25, 570);
    painter.drawLine(1015, 55, 1020, 50);
    painter.drawLine(1015, 45, 1020, 50);
    painter.drawLine(20, 565, 25, 570);
    painter.drawLine(30, 565, 25, 570);
    painter.drawText(1015, 70, "x");
    painter.drawText(35, 575, "y");
    double x1 = select_function_window.x1;
    double x2 = select_function_window.x2;
    double y1 = select_function_window.y1;
    double y2 = select_function_window.y2;
    for(int i = 0; i <= 10; ++i) {
        double x = 100 + 900 / 10 * i,
            y = 100 + 450 / 10 * i;
        double xText = (double) i / 10 * (x2 - x1) + x1,
            yText = (double) i / 10 * (y2 - y1) + y1;

        painter.drawLine(x, 53, x, 47);
        painter.drawText(x - 5, 70, QString::number(xText, 'g', 2));
        painter.drawLine(22, y, 28, y);
        painter.drawText(35, y + 5, QString::number(yText, 'g', 2));
    }
}

void MainWindow::area_print() {
    QPainter painter;
    painter.begin(this);

    double x1 = select_function_window.x1;
    double x2 = select_function_window.x2;
    double y1 = select_function_window.y1;
    double y2 = select_function_window.y2;
    Function* function = optimisationMethod->getFunction();

    // Вычисляем область.
    int numberOfBoxes = 1000;
    std::vector<std::vector<double>> area(numberOfBoxes);
    for(std::vector<double> v: area) {
        for(int j = 0; j < numberOfBoxes; ++j) {
            std::vector<double> xy = {j / numberOfBoxes * (x2 - x1),
                                      j / numberOfBoxes * (y2 - y1)};
            v.push_back(function->calculation(xy));
        }
    }

    // Рисуем область.
//    for(int i = )
}

void MainWindow::paintEvent(QPaintEvent *) {
    axec_print();

    if(isOptimise) {
        area_print();
        function_print();
    }


}

void MainWindow::on_actionRun_triggered()
{
    optimisationMethod = run_calculation();
    isOptimise = true;
    // Рисуем кривую.
    repaint();
    // Выводим текст.
    std::vector<double> X_n = optimisationMethod->getSequenceOfX_i().back();
    double sequenceOfF_n = optimisationMethod->getSequenceOfF_i().back();
    int numberOfIterations = optimisationMethod->getNumberOfIterations();
    std::string result = "X_n = (" + std::to_string(X_n[0]) + "; " + std::to_string(X_n[1]) + "); F_n = " +
            std::to_string(sequenceOfF_n) + "; Number of iterations = " + std::to_string(numberOfIterations) + ".";
    ui->label->setText(QString::fromStdString(result));
}


void MainWindow::on_actionHelp_triggered()
{
    help_window.exec();
}

