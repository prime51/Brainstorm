#include "mainpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPage *w = new MainPage;

    if (w->loginPage->exec() == QDialog::Accepted) {
        w->setWindowTitle("BrainStorm MainPage");
        w->show();
        return a.exec();
    }

    return 0;
}
