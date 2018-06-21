#ifndef USERBANK_H
#define USERBANK_H

#include "user.h"

#include <QDir>
#include <QString>
#include <QList>

class UserBank
{
public:
    UserBank();
    bool addUser(const User *user);
    User* getUser(QString userName);

private:
    QDir userDB;
    int userNum;
    QList<QString> userNameList;
};

#endif // USERBANK_H
