#include "questionbank.h"

#include <QDebug>
#include <QTextCodec>
#include <QtGlobal>

QuestionBank::QuestionBank(QObject *parent) : QObject(parent)
{
    db.setFileName(":/database/data");
    if (!db.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Database file open failed.";
    }

    queNum = 0;
    while (!db.atEnd()) {
        db.readLine();
        queNum++;
    }
//    qDebug() << queNum;

    db.close();
}

Question *QuestionBank::GetQuestion(qint32 id)
{
    Question *que;
    if (id > queNum) {
        qDebug() << "Required question id is too large!";
        return nullptr;
    }

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    if (!db.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Database file open failed.";
        return nullptr;
    }
    QTextStream fin(&db);
    fin.setCodec(codec);
    for (qint32 num = 0; num < queNum; num++) {
        QString line;
        fin >> line;
        if (num == id) {
            QString index, name, A, B, C, D, correct;
            index = line.section(",", 0, 0);
            name = line.section(",", 1, 1);
            A = line.section(",", 2, 2);
            B = line.section(",", 3, 3);
            C = line.section(",", 4, 4);
            D = line.section(",", 5, 5);
            correct = line.section(",", 6, 6);
            que = new Question();
            que->SetQuestion(index, name, correct, A, B, C, D);
            break;
        }
    }

    db.close();

    return que;
}

QList<Question*> QuestionBank::GetQuestion(QList<qint32> id)
{
    QList<Question*> que;
    if (id.size() > queNum) {
        qDebug() << "Required question id is too large!";
        return que;
    }

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    if (!db.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Database file open failed.";
        return que;
    }
    QTextStream fin(&db);
    fin.setCodec(codec);
    std::sort(id.begin(), id.end());
    for (qint32 num = 0, i = 0; num < queNum && i < id.size(); num++) {
        QString line;
        fin >> line;
        if (num == id[i]) {
            i++;
            QString index, name, correct, A, B, C, D;
            index = line.section(",", 0, 0);
            name = line.section(",", 1, 1);
            A = line.section(",", 2, 2);
            B = line.section(",", 3, 3);
            C = line.section(",", 4, 4);
            D = line.section(",", 5, 5);
            correct = line.section(",", 6, 6);
            Question *question = new Question();
            question->SetQuestion(index, name, correct, A, B, C, D);
//            qDebug() << id << " " << name << " " << A << " "
//                     << B << " " << C << " " << correct;
            que.append(question);
        }
    }

    db.close();

    return que;
}

qint32 QuestionBank::GetQueNum() const
{
    return queNum;
}
