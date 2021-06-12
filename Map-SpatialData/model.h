#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QSqlDatabase>
#include "Types.h"

class Model
{
public:
        Model(QString hostname="", QString databasename="", QString username="", QString password="");
        bool IsConnect();
        bool Insert(const QString &tablename, QString values);
        bool RunQuery(const QString &query);
        void Load(const QString &tablename, const Application::Types::DataSet &set);



private:
        QString hostname;
        QString databasename;
        QString username;
        QString password;
        QSqlDatabase database;
        bool isconnect = false;
};

#endif // MODEL_H
