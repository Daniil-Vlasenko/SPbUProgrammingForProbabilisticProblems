#ifndef SELECT_METHOD_H
#define SELECT_METHOD_H

#include <QDialog>
#include "../../terminalApp/mathLibrary.h"

namespace Ui {
class Select_method;
}

class Select_method : public QDialog
{
    Q_OBJECT

public:
    explicit Select_method(QWidget *parent = nullptr);
    ~Select_method();

private slots:
    void on_radioButton_G_clicked();

    void on_radioButton_P_clicked();

    void on_radioButton_PT1_clicked();

    void on_radioButton_PT2_clicked();

    void on_radioButton_PT3_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::Select_method *ui;

    int optimisationMethodId = 1, terminationMethodIdP = 1, terminationMethodIdG = 1, numberOfiterations = 1000;
    double epsP = 0.001, epsG = 0.001, p = 0.5, b = 0.5, a = 0.5;
};

#endif // SELECT_METHOD_H
