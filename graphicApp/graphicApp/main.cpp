#include "mainwindow.h"
#include <QApplication>
#include "../../terminalApp/mathLibrary.h"


int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(1100, 700);
    w.setMaximumSize(1100, 700);
    w.show();
    return a.exec();
}
