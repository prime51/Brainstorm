#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>

enum option { A, B, C, D };

class Question : public QObject
{
    Q_OBJECT
public:
    Question(QObject *parent = nullptr);
    ~Question();

    void SetQuestion(QString &_id, QString &_descrip, QString &ans,
                     QString &A, QString &B, QString &C, QString &D);
    QString GetID() const;
    QString GetAnswer() const;
    QString GetDescript() const;
    QString GetOption(option type) const;

    bool isEmpty() const;

private:
    QString id;
    QString description;
    QString optionA, optionB, optionC, optionD;
    QString answer;
};

#endif // QUESTION_H
