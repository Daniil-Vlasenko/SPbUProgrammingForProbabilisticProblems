#ifndef SELECT_FUNCTION_H
#define SELECT_FUNCTION_H

#include <QDialog>
#include "../../terminalApp/mathLibrary.h"

namespace Ui {
class Select_function;
}

class Select_function : public QDialog
{
    Q_OBJECT

public:
    explicit Select_function(QWidget *parent = nullptr);
    ~Select_function();

    int functionId = 0;
    double x = 0, y = 0, x1 = -5, x2 = 5, y1 = -5, y2 = 5;

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Select_function *ui;     
};

#endif // SELECT_FUNCTION_H
