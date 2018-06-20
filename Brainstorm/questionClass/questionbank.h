#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QList>

#include "question.h"

class QuestionBank : public QObject
{
    Q_OBJECT
public:
    QuestionBank(QObject *parent = nullptr);
    Question* GetQuestion(qint32 id);
    QList<Question*> GetQuestion(QList<qint32> id);
    qint32 GetQueNum() const;       // get the number of questions

private:
    QFile db;
    qint32 queNum;
};

#endif // QUESTIONBANK_H
