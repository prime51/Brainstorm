#ifndef HOVERSENSITIVELABEL_H
#define HOVERSENSITIVELABEL_H

#include "hoverwindow.h"

#include <QObject>
#include <QtWidgets>
#include <QTimerEvent>

class HoverSensitiveLabel : public QLabel
{
    Q_OBJECT

public:
    explicit HoverSensitiveLabel(QWidget *parent = 0);

signals:
    void enterLabel();
    void moveInLabel();
    void leaveLabel();

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    HoverWindow *hover;
    int timeID;
};

#endif // HOVERSENSITIVELABEL_H
