#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "select_function.h"
#include "select_method.h"
#include "help.h"
#include "../../terminalApp/mathLibrary.h"
#include "qpainter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    Select_function select_function_window;
    Select_method select_method_window;
    Help help_window;
    OptimizationMethod* optimisationMethod;    
    bool isOptimise;
    bool isAreaDrawn;

    OptimizationMethod* run_calculation();   
    void function_print();
    void area_print();
    void axec_print();
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_actionSelect_function_triggered();
    void on_actionSelect_method_triggered();
    void on_actionRun_triggered();
    void on_actionHelp_triggered();
};
#endif // MAINWINDOW_H
