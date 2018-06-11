#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/new/prefix1/C:/Users/Young/Pictures/ico.jpg"));//Set UI icon
    w.show();
    return a.exec();
}
