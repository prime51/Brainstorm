#include "userbank.h"

#include <QDebug>
#include <QTextStream>

UserBank::UserBank()
{
    // 将QDir设置成UserBank所在路径
    QString userBankPath = QDir::currentPath() + "/UserBank";
    userDB = QDir(userBankPath);
//    qDebug() << QDir::currentPath() + "/UserBank";

    // 如果UserBank文件夹不存在，则创建一个
    if (!userDB.exists()) {
        userDB.mkdir(userBankPath);
    }

    // 获取UserBank文件夹下有几个文件（即获得用户的数量）
    userNum = 0;
    userNameList.clear();
    userDB.setFilter(QDir::Dirs);
    foreach (QFileInfo userDir, userDB.entryInfoList()) {
        if (userDir.fileName() == "." || userDir.fileName() == "..")
            continue;
        userNum++;
        userNameList.append(userDir.fileName());
    }
//    qDebug() << userNum << " " << userNameList[0];
}

bool UserBank::addUser(const User *user)
{
    QString userName = user->name;
    // 判断用户是否存在
    foreach (QString name, userNameList) {
        if (userName == name)
            return false;
    }
    // 若用户名未被使用，则新建一个用户文件夹
    userDB.mkdir(userName);
    userNameList.append(userName);

    QString filepath = userDB.absolutePath() + "/" + userName;
    QFile *basicInfo = new QFile, *gameInfo = new QFile;
    basicInfo->setFileName(filepath + "/basic.txt");
    gameInfo->setFileName(filepath + "/game.txt");
    if (!basicInfo->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "create basic file failed";
        return false;
    }
    if (!gameInfo->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "create game file failed";
        return false;
    }

    QTextStream stream(basicInfo);
    stream << "Name: " << user->name << endl;
    stream << "ID: " << user->id << endl;
    stream << "Password: " << user->password << endl;
    stream << "Level: " << user->level << endl;
    stream << "Exp: " << user->exp << endl;
    stream << "Rank: " << user->rank << endl;
    stream << "Coin: " << user->coin << endl;
    stream << "Total_game: " << user->totalGame << endl;
    stream << "Winning_game: " << user->winningGame << endl;
    stream << "Winning_rate: " << user->winningRate << endl;


    basicInfo->close();
    gameInfo->close();

    return true;
}

User* UserBank::getUser(QString userName)
{
    QFile *basicInfo;
    User* user = nullptr;

    // 判断用户是否存在
    bool userExist = false;
    foreach (QString name, userNameList) {
        if (userName == name) {
            QString filepath = userDB.absolutePath() + "/" + userName;
            userExist = true;
            basicInfo = new QFile(filepath + "/basic.txt");
            break;
        }
    }
    if (!userExist) return user;

    basicInfo->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(basicInfo);
    QString name, id, passwd, level, exp,
            rank, coin, totalGame, winningGame, winningRate;
    QString tmp;
    stream >> tmp >> name;
//    qDebug() << tmp;
    stream >> tmp >> id;
//    qDebug() << tmp;
    stream >> tmp >> passwd;
//    qDebug() << tmp;
    stream >> tmp >> level;
//    qDebug() << tmp;
    stream >> tmp >> exp;
//    qDebug() << tmp;
    stream >> tmp >> rank;
//    qDebug() << tmp;
    stream >> tmp >> coin;
//    qDebug() << tmp;
    stream >> tmp >> totalGame;
//    qDebug() << tmp;
    stream >> tmp >> winningGame;
//    qDebug() << tmp;
    stream >> tmp >> winningRate;
//    qDebug() << tmp;
    user = new User;
    user->name = name;
    user->id = id.toInt();
    user->level = level.toInt();
    user->password = passwd;
    user->exp = exp.toInt();
    user->rank = rank;
    user->coin = coin.toInt();
    user->totalGame = totalGame.toInt();
    user->winningGame = winningGame.toInt();
    user->winningRate = winningRate.toDouble();

    return user;
}
