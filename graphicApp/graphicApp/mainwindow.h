#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "select_function.h"
#include "select_method.h"
#include "help.h"
#include "../../terminalApp/mathLibrary.h"

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

private slots:
    void on_actionSelect_function_triggered();
    void on_actionSelect_method_triggered();
    void on_actionRun_triggered();
    void on_actionHelp_triggered();

    OptimizationMethod* run_calculation();
    std::string run_text();
};
#endif // MAINWINDOW_H
