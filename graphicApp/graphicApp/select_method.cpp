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

void Select_method::on_radioButton_G_clicked()
{
    ui->frame_3->setDisabled(1);
    ui->frame_5->setEnabled(1);
}


void Select_method::on_radioButton_P_clicked()
{
    ui->frame_5->setDisabled(1);
    ui->frame_3->setEnabled(1);
}


void Select_method::on_radioButton_PT1_clicked()
{
    ui->frame_8->setDisabled(1);
    ui->frame_7->setEnabled(1);
}


void Select_method::on_radioButton_PT2_clicked()
{
    ui->frame_7->setDisabled(1);
    ui->frame_8->setEnabled(1);
}


void Select_method::on_radioButton_PT3_clicked()
{
    ui->frame_7->setDisabled(1);
    ui->frame_8->setEnabled(1);
}


void Select_method::on_pushButton_Cancel_clicked()
{
    close();
}


void Select_method::on_pushButton_OK_clicked()
{
    if(ui->radioButton_P->isChecked()) {
        optimisationMethodId = 1;
        if(ui->radioButton_PT1->isChecked()) {
            terminationMethodIdP = 1;
        }
        else if(ui->radioButton_PT2->isChecked()) {
            terminationMethodIdP = 2;
        }
        else {
            terminationMethodIdP = 3;
        }
    }
    else {
        optimisationMethodId = 2;
        if(ui->radioButton_GT1->isChecked()) {
            terminationMethodIdG = 1;
        }
        else if(ui->radioButton_GT2->isChecked()) {
            terminationMethodIdG = 2;
        }
        else {
            terminationMethodIdG = 3;
        }
    }
    p = ui->lineEdit_Pp->text().toDouble();
    b = ui->lineEdit_Pb->text().toDouble();
    a = ui->lineEdit_Pa->text().toDouble();
    epsP = ui->lineEdit_PEps->text().toDouble();
    numberOfiterations = ui->lineEdit_Pn->text().toInt();
    epsG = ui->lineEdit_GEps->text().toDouble();

    close();
}

