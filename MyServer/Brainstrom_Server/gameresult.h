#ifndef GAMERESULT_H
#define GAMERESULT_H
#include <QString>
#include <QList>
#include <QDir>
#include <QTextStream>

class GameResult
{
public:
    GameResult();
    ~GameResult();
    void set_name(QString n);
    void add_q_id(QString q);
    void add_response(QString r);
    void set_time(QString t);
    void write_result(QString t);
    QString read_result();

    QString name;
    QList<QString> question_list;
    QList<QString> response_list;
    QString time;
    QDir db;
};

#endif // GAMERESULT_H
