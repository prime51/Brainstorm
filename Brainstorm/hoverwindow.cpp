#include "hoverwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

HoverWindow::HoverWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoMousePropagation);

    setFixedSize(100, 200);

    QLabel *nickname = new QLabel(this);
    nickname->setText("Prime");
    nickname->setStyleSheet("background-color:white");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(nickname);
    setLayout(mainLayout);
}

//void HoverWindow::hoverEnter(QEvent *event)
//{
//    show();
//}

//void HoverWindow::hoverLeave(QEvent *event)
//{
//    hide();
//}

//bool HoverWindow::event(QEvent *event)
//{
//    switch (event->type()) {
//    case QEvent::HoverEnter:
//        hoverEnter((event));
//        return true;
//        break;
//    case QEvent::HoverLeave:
//        hoverLeave((event));
//        return true;
//        break;
//    default:
//        break;
//    }
//    return QWidget::event(event);
//}
