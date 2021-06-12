#include "model.h"
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
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

bool Model::Insert(const QString &tablename, QString values) {
        QSqlQuery query(database);
        QString render  = "INSERT INTO "+tablename+" ";
        query.prepare(render+"VALUES("+values+")");
        if(query.exec())
                return true;
        else
                return false;
}

bool Model::RunQuery(const QString &query) {


}


