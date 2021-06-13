#include "model.h"
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
namespace Application{
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


Model::Model(const Model &&other) {
        database = std::move(other.database);
}

Model &Model::operator = (const Model &&other) {
        database = std::move(other.database);
}

bool  Model::IsConnect()const {
        return isconnect;
}

bool Model::Insert(const QString &tablename, QString values)const {
        QSqlQuery query(database);
        QString render  = "INSERT INTO "+tablename+" ";
        query.prepare(render+"VALUES("+values+")");
        if(query.exec())
                return true;
        else
                return false;
}



QStringList Model::Select(const QString &tablename, const QString &columnname, QString id) const {
        QStringList outputlist;
        QSqlQuery query(database);
        //SELECT ST_AsText(g) FROM geom;
        QString column = columnname == "location" ? "ST_AsText(location)" : columnname;
        QString render = "SELECT "+column+" from "+ tablename;
        render+= id.isEmpty() ? ";" :" Where id = "+ id + ";";

        query.prepare(render);
        if(query.exec()) {
                while(query.next()) {
                        auto value = query.value(0).toString();
                        qDebug()<<value;


                }
        }
        return outputlist;

}

QString Model::Select(int id)const {
        QSqlQuery query(database);
        //SELECT ST_AsText(g) FROM geom;

        QString render = "SELECT ST_AsText(location) from busstops WHERE id = "+QString::number(id)+';';
        query.prepare(render);
        if(query.exec()) {
                while(query.next()){
                        auto z = query.value(0).toString();
                        z.replace("POINT(","");
                        z.replace(")","");
                        QStringList l = z.split(QRegExp("[\r\n\t ]+"));

                        qDebug()<<z;
                }
        }


}

bool Model::RunQuery(const QString &query)const {


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
}


