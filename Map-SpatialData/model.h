#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QSqlDatabase>
#include "Types.h"

namespace Application {
class Model
{
public:
        explicit Model(QString hostname="", QString databasename="", QString username="", QString password="");
        explicit Model(const Model &other) = delete;
        explicit Model(const Model &&other);

        Model &operator = (const Model &&other);
        Model &operator = (const Model &other) = delete;

        bool IsConnect()const;
        bool Insert(const QString &tablename, QString values)const;
        QString Select(int id)const;
        QStringList Select(const QString &tablename, const QString &columnname, QString id="") const;
        bool RunQuery(const QString &query)const;
        void Load(const QString &tablename, const Application::Types::DataSet &set);



private:
        QString hostname;
        QString databasename;
        QString username;
        QString password;
        QSqlDatabase database;
        bool isconnect = false;
};
}

#endif // MODEL_H
