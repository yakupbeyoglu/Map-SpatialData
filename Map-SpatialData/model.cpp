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
                qDebug() << database.lastError().text();

}

bool Model::RunQuery(const QString &query) {


}

void Model::Load(const QString &tablename, const Application::Types::DataSet &set) {
        QRegExp reg("\\d*");
        for(auto &l : set) {
                QString values = "";
                QString id;
                if(reg.exactMatch(l.id))
                        values += l.id;
                else
                        values += '\''+l.id+'\'';
                values+=',';
                values += l.name!=NULL ? '\''+l.name+"',":"";
                //POINT(3,5)"
                values += "POINT(" + QString::number(l.x) + ',' + QString::number(l.y) + ')';

                if(!Insert(tablename,values))
                       throw("Database Insert Error");
        }
}


