#include "model.h"
#include <QtDebug>
#include <QSqlError>
Model::Model(QString hostname, QString databasename,
             QString username, QString password) :
                        hostname(hostname), databasename(databasename),
                        username(username), password(password)
{

        database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName(hostname);
        database.setDatabaseName(databasename);
        database.setUserName(username);
        database.setPassword(password);
        if(database.open())
                isconnect = true;
        else
                qDebug() << database.lastError().text();
}

bool  Model::IsConnect() {
        return isconnect;
}

