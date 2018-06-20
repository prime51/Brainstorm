#ifndef HOVERWINDOW_H
#define HOVERWINDOW_H

#include <QWidget>
#include <QTimerEvent>

class HoverWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HoverWindow(QWidget *parent = nullptr);
//    void hoverShow();
//    void hoverHide();

//protected:
//    void hoverEnter(QEvent *event);
//    void hoverLeave(QEvent *event);
//    bool event(QEvent *event);

};

#endif // HOVERWINDOW_H
