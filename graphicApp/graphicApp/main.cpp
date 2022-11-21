#include "mainwindow.h"
#include <QApplication>
#include "../../terminalApp/mathLibrary.h"


int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(1000, 600);
    w.setMaximumSize(1000, 600);
    w.show();
    return a.exec();
}
