#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QSqlDatabase>

class Model
{
public:
        Model(QString hostname="", QString databasename="", QString username="", QString password="");
        bool IsConnect();



private:
        QString hostname;
        QString databasename;
        QString username;
        QString password;
        QSqlDatabase database;
        bool isconnect = false;
};

#endif // MODEL_H
