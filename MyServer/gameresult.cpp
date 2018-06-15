#include "gameresult.h"

GameResult::GameResult()
{
    db.setFileName(":/UserBank");
}

GameResult::~GameResult()
{

}

void GameResult::set_name(QString n)
{
    this->name = n;
}

void GameResult::set_time(QString t)
{
    this->time = t;
}

void GameResult::add_q_id(QString q)
{
    q_list.append(q);
}

void GameResult::add_response(QString r)
{
    r_list.append(r);
}

void GameResult::write_result()
{
    QString filepath = db.absolutePath() + "/" + name + "/game.txt";


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

}

QString GameResult::read_result()
{

}
