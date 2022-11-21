#ifndef SELECT_FUNCTION_H
#define SELECT_FUNCTION_H

#include <QDialog>

namespace Ui {
class Select_function;
}

class Select_function : public QDialog
{
    Q_OBJECT

public:
    explicit Select_function(QWidget *parent = nullptr);
    ~Select_function();

private:
    Ui::Select_function *ui;
};

#endif // SELECT_FUNCTION_H
