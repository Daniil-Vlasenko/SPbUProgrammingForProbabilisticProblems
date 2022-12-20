#include "select_function.h"
#include "ui_select_function.h"

Select_function::Select_function(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select_function)
{
    ui->setupUi(this);

    QLocale lo(QLocale::C);
    lo.setNumberOptions(QLocale::RejectGroupSeparator);
    auto val = new QDoubleValidator(-MAXFLOAT, MAXFLOAT, 10, this);
    val->setLocale(lo);

    ui->lineEdit_x->setValidator(val);
    ui->lineEdit_y->setValidator(val);
    ui->lineEdit_x1->setValidator(val);
    ui->lineEdit_x2->setValidator(val);
    ui->lineEdit_y1->setValidator(val);
    ui->lineEdit_y2->setValidator(val);
}

Select_function::~Select_function()
{
    delete ui;
}

void Select_function::on_pushButton_OK_clicked()
{
    functionId = ui->comboBox->currentIndex();    

//    if(isNumber(ui->lineEdit_x->text().toStdString()) and isNumber(ui->lineEdit_y->text().toStdString()) and
//       isNumber(ui->lineEdit_x1->text().toStdString()) and isNumber(ui->lineEdit_y1->text().toStdString()) and
//       isNumber(ui->lineEdit_x2->text().toStdString()) and isNumber(ui->lineEdit_y2->text().toStdString())) {

//    }
    x = ui->lineEdit_x->text().toDouble();
    y = ui->lineEdit_y->text().toDouble();
    x1 = ui->lineEdit_x1->text().toDouble();
    x2 = ui->lineEdit_x2->text().toDouble();
    y1 = ui->lineEdit_y1->text().toDouble();
    y2 = ui->lineEdit_y2->text().toDouble();

    close();
}

void Select_function::on_pushButton_Cancel_clicked()
{
    close();
}

