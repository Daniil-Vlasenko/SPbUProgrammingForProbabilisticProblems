#ifndef SELECT_METHOD_H
#define SELECT_METHOD_H

#include <QDialog>

namespace Ui {
class Select_method;
}

class Select_method : public QDialog
{
    Q_OBJECT

public:
    explicit Select_method(QWidget *parent = nullptr);
    ~Select_method();

private:
    Ui::Select_method *ui;
};

#endif // SELECT_METHOD_H
