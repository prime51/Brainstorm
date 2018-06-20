#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QString>

#include "questionClass/questionbank.h"
#include "questionClass/question.h"

namespace Ui {
class GamePage;
}

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = 0);
    ~GamePage();

    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void gameEnds();
    void queReady();
    void messageToServer(QString text);

public slots:
    void on_click_next();

    void prepareQuestions(QString queMessage);    // analyse question from server
    void startGame();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::GamePage *ui;

    qint32 score;                  // 当前得分
    qint32 curQ;                   // 当前第几题
    qint32 queTotal;               // 总共的答题数
    qint32 timeID;                 // 计时器ID

    QuestionBank db;            // 题库
    QList<Question*> listQue;    // 题目队列

    void checkAnswer();
    void setQueTotal(qint32 n);

    void nextQuestion();
    void showQuestion() const;
};

#endif // WIDGET_H
