#include "select_function.h"
#include "ui_select_function.h"

Select_function::Select_function(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select_function)
{
    ui->setupUi(this);
}

Select_function::~Select_function()
{
    delete ui;
}

void Select_function::on_pushButton_OK_clicked()
{

}


void Select_function::on_comboBox_currentIndexChanged(int index)
{
    if(index == 3) {
        ui->lineEdit_z->setEnabled(1);
        ui->label_9->setEnabled(1);
        ui->lineEdit_z1->setEnabled(1);
        ui->lineEdit_z2->setEnabled(1);
        ui->label_7->setEnabled(1);
    }
    else {
        ui->lineEdit_z->setDisabled(1);
        ui->label_9->setDisabled(1);
        ui->lineEdit_z1->setDisabled(1);
        ui->lineEdit_z2->setDisabled(1);
        ui->label_7->setDisabled(1);
    }
}

