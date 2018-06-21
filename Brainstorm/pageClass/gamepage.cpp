#include "gamepage.h"
#include "ui_gamepage.h"

#include <QPainter>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QtGlobal>

GamePage::GamePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePage)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    score = 0;      // 原始分数
    curQ = 0;       // 题目序号

    ui->nextQue->setText("Next");
    ui->remainTime->display(10);    // 初始时间
    ui->radioButton_A->adjustSize();
    ui->radioButton_B->adjustSize();
    ui->radioButton_C->adjustSize();
    ui->radioButton_D->adjustSize();
    ui->description->adjustSize();
    ui->description->setScaledContents(true);
    ui->description->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
    ui->description->setWordWrap(true);
    ui->description->setAlignment(Qt::AlignTop);

    // connect question preparation ready signal to startGame slot function
    connect(this, &GamePage::queReady, this, &GamePage::startGame);
    // go to the next question when nextBtn is clicked
    connect(ui->nextQue, &QPushButton::clicked, this, &GamePage::on_click_next);
}

GamePage::~GamePage()
{
    delete ui;

    for (qint32 i = 0; i < listQue.size(); i++) {
        if (listQue[i] != nullptr)
            delete listQue[i];
    }
}

void GamePage::setQueTotal(qint32 n)
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

void GamePage::prepareQuestions(QString queMessage)
{
    int queNum = queMessage.section(";", 0, 0).toInt();
    setQueTotal(queNum);
    qDebug() << "preparing questions";
    for (int i = 1; i <= queNum; i++) {
        QString queString = queMessage.section(";", i, i);
        qDebug() << queString;;

        QString id, descript, A, B, C, D, answer;
        id = queString.section("+", 0, 0);
        descript = queString.section("+", 1, 1);
        A = queString.section("+", 2, 2);
        B = queString.section("+", 3, 3);
        C = queString.section("+", 4, 4);
        D = queString.section("+", 5, 5);
        answer = queString.section("+", 6, 6);

        Question *que = new Question;
        que->SetQuestion(id, descript, answer, A, B, C, D);
        listQue.append(que);
    }

    emit queReady();

//    QList<qint32> queID = generateUniqueRandNumbers(db.GetQueNum(), queTotal);
//    for (int i = 0; i < queID.size(); i++)
//        qDebug() << queID[i];
//    listQue = db.GetQuestion(queID);
//    for (int i = 0; i < queID.size(); i++)
//        qDebug() << queID[i];
}

void GamePage::startGame()
{
    showQuestion();

    timeID = startTimer(1000);      // 间隔1s
}

void GamePage::nextQuestion()
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

void GamePage::showQuestion() const
{
    const Question *que = listQue[curQ];
    QString id = que->GetID();
    QString descrip =que->GetDescript();
    QString opA = que->GetOption(A);
    QString opB = que->GetOption(B);
    QString opC = que->GetOption(C);
    QString opD = que->GetOption(D);

    qDebug() << id << " " << descrip << " " << opA << " " << opB << " "
             << opC << " " << opD;

    ui->description->setText(descrip);
    if (opA == "blank") ui->radioButton_A->hide();
    else {
        ui->radioButton_A->setText(opA);
        ui->radioButton_A->show();
    }

    if (opB == "blank") ui->radioButton_B->hide();
    else {
        ui->radioButton_B->setText(opB);
        ui->radioButton_B->show();
    }

    if (opC == "blank") ui->radioButton_C->hide();
    else {
        ui->radioButton_C->setText(opC);
        ui->radioButton_C->show();
    }

    if (opD == "blank") ui->radioButton_D->hide();
    else {
        ui->radioButton_D->setText(opD);
        ui->radioButton_D->show();
    }
}

void GamePage::checkAnswer()
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

void GamePage::on_click_next()
{
    checkAnswer();
    nextQuestion();
}

void GamePage::timerEvent(QTimerEvent *event)
{
    ui->remainTime->display(ui->remainTime->value() - 1);
    if (ui->remainTime->value() == 0) {
        checkAnswer();
        nextQuestion();
    }
}

void GamePage::paintEvent(QPaintEvent *event)
{

    // 画家
    QPainter p(this);  // 画家  this 是指以当前窗口为图纸 画图

    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/resources/images/background"));
}

void GamePage::closeEvent(QCloseEvent *event)
{
    emit gameEnds();
    event->accept();
}
