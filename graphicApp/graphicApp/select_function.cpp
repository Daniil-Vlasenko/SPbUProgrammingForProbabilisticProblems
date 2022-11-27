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
    functionInt = ui->comboBox->currentIndex();
    switch(functionInt) {
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
    x_0.resize(dimensions);
    box.resize(dimensions);


    x = ui->lineEdit_x->text().toDouble();
    y = ui->lineEdit_y->text().toDouble();
    z = ui->lineEdit_z->text().toDouble();
    x1 = ui->lineEdit_x1->text().toDouble();
    x2 = ui->lineEdit_x2->text().toDouble();
    y1 = ui->lineEdit_y1->text().toDouble();
    y2 = ui->lineEdit_y2->text().toDouble();
    z1 = ui->lineEdit_z1->text().toDouble();
    z2 = ui->lineEdit_z2->text().toDouble();

    x_0.push_back(x);
    x_0.push_back(y);
    if(dimensions > 2) {
        x_0.push_back(z);
    }

    std::pair<double, double> b1(x1, x2);
    std::pair<double, double> b2(y1, y2);
    std::pair<double, double> b3(z1, z2);

    box.push_back(b1);
    box.push_back(b2);
    if(dimensions > 2) {
        box.push_back(b3);
    }

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

