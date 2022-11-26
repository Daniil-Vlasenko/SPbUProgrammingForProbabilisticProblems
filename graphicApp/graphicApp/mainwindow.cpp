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


void MainWindow::on_actionRun_triggered()
{

}


void MainWindow::on_actionHelp_triggered()
{
    help_window.exec();
}

