#include "question.h"

Question::Question(QObject *parent) : QObject(parent) {}

Question::~Question() {}

void Question::SetQuestion(QString &_id, QString &_descrip, QString &ans,
                      QString &A, QString &B, QString &C, QString &D)
{
    id = _id;
    description = _descrip;
    answer = ans;
    optionA = A;
    optionB = B;
    optionC = C;
    optionD = D;
}

QString Question::GetID() const {
    return id;
}

QString Question::GetAnswer() const {
    return answer;
}

QString Question::GetDescript() const {
    return description;
}

QString Question::GetOption(option type) const {
    switch (type) {
        case A:
            return optionA;
            break;
        case B:
            return optionB;
            break;
        case C:
            return optionC;
            break;
        case D:
            return optionD;
            break;
        default:
            return QString();
            break;
    }
}

bool Question::isEmpty() const {
    return id.isEmpty() || description.isEmpty();
}
