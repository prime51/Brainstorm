#include "hoversensitivelabel.h"

HoverSensitiveLabel::HoverSensitiveLabel(QWidget *parent)
    : QLabel(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    hover = new HoverWindow(this);
}

void HoverSensitiveLabel::hoverEnter(QHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
    repaint();

    timeID = startTimer(500);
}

void HoverSensitiveLabel::hoverLeave(QHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(false);
    this->setFont(font);
    repaint();

    killTimer(timeID);
    hover->hide();
}

void HoverSensitiveLabel::hoverMove(QHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
    repaint();
}

void HoverSensitiveLabel::timerEvent(QTimerEvent *event)
{
    QPoint curPos;
    curPos.setX(cursor().pos().x() +10);
    curPos.setY(cursor().pos().y() + 10);
    hover->move(curPos);
    hover->show();
}

bool HoverSensitiveLabel::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
