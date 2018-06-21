#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();

    QString name;
    int id;
    int level;
    int exp;
    QString rank;
    int coin;
    int totalGame;
    int winningGame;
    double winningRate;
    QString password;
};

#endif // USER_H
