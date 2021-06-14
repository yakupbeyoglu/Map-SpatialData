#include "model.h"
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
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

Application::Types::DataSet Model::SelectCovarage() const {
        QSqlQuery query(database);
        Application::Types::DataSet dataset;
        QString render = "SELECT ST_ASTEXT(passenger.location) from busstops, passenger where ST_Distance(passenger.location,busstops.location) < 100";

        query.prepare(render);
        if(query.exec()) {
                while(query.next()) {
                        auto value = query.value(0).toString();
                        value.replace("POINT(","");
                        value.replace(")","");
                        QStringList values = value.split(QRegExp("[\r\n\t ]+"));
                        Application::Types::Point point = {values.at(0).toInt(), values.at(1).toInt()};
                        dataset.push_back({"",value,point});

                }
                for(auto &l : dataset) {
                        qDebug()<<l.id<<" "<<l.name<<" "<< l.point.x<<" "<<l.point.y;
                }
        }
        return dataset;
}




Types::DataSet Model::Select(const QString &tablename, const QString &columnname,
                                          QString id) const {
        QSqlQuery query(database);
        Application::Types::DataSet dataset;
        //SELECT ST_AsText(g) FROM geom;
        QString column = columnname == "location" ? "ST_AsText(location)" : columnname;
        QString render = "SELECT "+column+" from "+ tablename;
        render+= id.isEmpty() ? ";" :" Where id = "+ id + ";";

        query.prepare(render);
        if(query.exec()) {
                while(query.next()) {
                        auto value = query.value(0).toString();
                        if(columnname == "id") {
                                dataset.push_back({value,"",{0,0}});
                        }
                        else if (columnname == "name")
                                dataset.push_back({"",value,{0,0}});

                        else if (columnname == "location") {
                                value.replace("POINT(","");
                                value.replace(")","");
                                QStringList values = value.split(QRegExp("[\r\n\t ]+"));

                                Application::Types::Point point = {values.at(0).toInt(), values.at(1).toInt()};

                                dataset.push_back({"",value,point});
                        }
                }
                for(auto &l : dataset) {
                        qDebug()<<l.id<<" "<<l.name<<" "<< l.point.x<<" "<<l.point.y;
                }
        }
        return dataset;
}

Application::Types::Point Model::Select(int id)const {
        QSqlQuery query(database);
        //SELECT ST_AsText(g) FROM geom;
        Application::Types::Point point = {0,0};
        QString render = "SELECT ST_AsText(location) from busstops WHERE id = "+QString::number(id)+';';
        query.prepare(render);
        if(query.exec()) {
                while(query.next()){
                        auto z = query.value(0).toString();
                        z.replace("POINT(","");
                        z.replace(")","");
                        QStringList l = z.split(QRegExp("[\r\n\t ]+"));

                         point = {l.at(0).toInt(), l.at(1).toInt()};
                }
        }
        return point;
}

// load fwill load data to database
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

                values += "POINT(" + QString::number(l.point.x) + ',' + QString::number(l.point.y) + ')';

                if(!Insert(tablename,values))
                       throw("Database Insert Error");
        }
}
}


