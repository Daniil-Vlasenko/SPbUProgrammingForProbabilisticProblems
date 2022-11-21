#include "select_method.h"
#include "ui_select_method.h"

Select_method::Select_method(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select_method)
{
    ui->setupUi(this);
}

Select_method::~Select_method()
{
    delete ui;
}
