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

void GameResult::write_result(QString t)
{
    QString filepath = userDB.absolutePath() + "/" + name;
    QFile *gameInfo = new QFile;
    gameInfo->setFileName(filepath + "/game.txt");
    if (!gameInfo->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "create game file failed";
        return false;
    }

    QTextStream stream(gameInfo);
    for(int i=0;i<question_list.size();i++)
    {
        stream << question_list[i] << "," << response_list[i] << "," << time << endl;
    }
}

void GameResult::write_result(QString text)
{
    text += ","
    text += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    QString filepath = userDB.absolutePath() + "/" + name;
    QFile *gameInfo = new QFile;
    gameInfo->setFileName(filepath + "/game.txt");
    if (!gameInfo->open(QIODevice::WriteOnly | QIODevice::Text) | QIODevice::Append) {
        qDebug() << "create game file failed";
        return false;
    }

    QTextStream stream(gameInfo);
    stream << text << endl;
}

QString GameResult::read_result()
{

    QString filepath = userDB.absolutePath() + "/" + name;
    QFile *gameInfo = new QFile;
    gameInfo->setFileName(filepath + "/game.txt");

    QTextStream stream(gameInfo);
    QString text = stream.readAll();

    return text;
}
