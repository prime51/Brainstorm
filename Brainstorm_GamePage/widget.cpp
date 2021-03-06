#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QtGlobal>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setQueTotal(5);
    prepareQuestions();

    score = 0;      // 原始分数
    curQ = 0;       // 题目序号

    showQuestion();
    ui->nextQue->setText("Next");
    ui->remainTime->display(10);    // 初始时间
    timeID = startTimer(1000);      // 间隔1s

    connect(ui->nextQue, &QPushButton::clicked, this, &on_click_next);
}

Widget::~Widget()
{
    delete ui;

    for (qint32 i = 0; i < listQue.size(); i++) {
        if (listQue[i] != nullptr)
            delete listQue[i];
    }
}

void Widget::setQueTotal(qint32 n)
{
    queTotal = n;
}

QList<qint32> generateUniqueRandNumbers(qint32 MAXNUM, qint32 queNum) {
    QList<qint32> numbersList;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    for (qint32 i = 0; i < queNum; i++) {
        numbersList.append(qrand() % MAXNUM);

        while (true) {
            qint32 j;
            for (j = 0; j < i; j++) {
                if (numbersList[i] == numbersList[j])
                    break;
            }
            if (j < i) {
                numbersList[i] = rand() % MAXNUM;
                continue;
            } else if (j == i) {
                break;
            }
        }
    }

    std::sort(numbersList.begin(), numbersList.end());
    for (qint32 i = 0; i < queNum; i++)
        qDebug() << numbersList[i];

    return numbersList;
}

void Widget::prepareQuestions()
{
    QList<qint32> queID = generateUniqueRandNumbers(db.GetQueNum(), queTotal);
    for (int i = 0; i < queID.size(); i++)
        qDebug() << queID[i];
    listQue = db.GetQuestion(queID);
    for (int i = 0; i < queID.size(); i++)
        qDebug() << queID[i];
}

void Widget::nextQuestion()
{
    curQ++;
    if (curQ == queTotal) {
        killTimer(timeID);
        QString msg;
        msg.sprintf("<center><h1>Final score: %d/%d</h1></center>", score, queTotal);
        QMessageBox::information(this, "Final score", msg);
        this->close();
    } else {
        ui->remainTime->display(10);
        ui->radioButton_A->setCheckable(false);
        ui->radioButton_B->setCheckable(false);
        ui->radioButton_C->setCheckable(false);
        ui->radioButton_D->setCheckable(false);
        ui->radioButton_A->setCheckable(true);
        ui->radioButton_B->setCheckable(true);
        ui->radioButton_C->setCheckable(true);
        ui->radioButton_D->setCheckable(true);
        showQuestion();
    }
}

void Widget::showQuestion() const
{
    const Question *que = listQue[curQ];
    QString id = que->GetID();
    QString descrip =que->GetDescript();
    QString opA = que->GetOption(A);
    QString opB = que->GetOption(B);
    QString opC = que->GetOption(C);
    QString opD = que->GetOption(D);

    ui->description->setText(descrip);
    if (opA == "blank") ui->radioButton_A->hide();
    else ui->radioButton_A->setText(opA);

    if (opB == "blank") ui->radioButton_B->hide();
    else ui->radioButton_B->setText(opB);

    if (opC == "blank") ui->radioButton_C->hide();
    else ui->radioButton_C->setText(opC);

    if (opD == "blank") ui->radioButton_D->hide();
    else ui->radioButton_D->setText(opD);
}

void Widget::checkAnswer()
{
    QString choice;
    if (ui->radioButton_A->isChecked())
        choice = "1";
    else if (ui->radioButton_B->isChecked())
        choice = "2";
    else if (ui->radioButton_C->isChecked())
        choice = "3";
    else if (ui->radioButton_D->isChecked())
        choice = "4";
    else
        return ;

    if (choice == listQue[curQ]->GetAnswer())
        score += 1;
    return ;
}

void Widget::on_click_next()
{
    checkAnswer();
    nextQuestion();
}

void Widget::timerEvent(QTimerEvent *event)
{
    ui->remainTime->display(ui->remainTime->value() - 1);
    if (ui->remainTime->value() == 0) {
        checkAnswer();
        nextQuestion();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{

    // 画家
    QPainter p(this);  // 画家  this 是指以当前窗口为图纸 画图

    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/background"));
}
