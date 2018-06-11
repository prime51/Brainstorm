#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    //两个按键分别对应的槽函数
    void on_login_in_clicked();
    void on_forget_psd_clicked();
};

class Dialog:public QDialog
{
    Q_OBJECT;

public:
    explicit Dialog(QDialog *parent=0);
    ~Dialog();
    void dialogUse();

private slots:
    //这两个槽函数是当用户登陆到系统之后我规划要做的事情，但是后面我没有对其进行实现
    void findClick();
    void enableFindButton();
private:
    QDialog *dialog;
};

#endif // MAINWINDOW_H
