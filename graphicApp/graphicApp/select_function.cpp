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
    functionId = ui->comboBox->currentIndex();

    x = ui->lineEdit_x->text().toDouble();
    y = ui->lineEdit_y->text().toDouble();
    z = ui->lineEdit_z->text().toDouble();
    x1 = ui->lineEdit_x1->text().toDouble();
    x2 = ui->lineEdit_x2->text().toDouble();
    y1 = ui->lineEdit_y1->text().toDouble();
    y2 = ui->lineEdit_y2->text().toDouble();
    z1 = ui->lineEdit_z1->text().toDouble();
    z2 = ui->lineEdit_z2->text().toDouble();

    close();
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


void Select_function::on_pushButton_Cancel_clicked()
{
    close();
}

