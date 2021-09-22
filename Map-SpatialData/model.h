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
        Application::Types::Point Select(int id)const;
        Application::Types::DataSet Select(const QString &tablename, const QString &columnname, QString id="") const;
        Application::Types::DataSet SelectCovarage() const;
        bool RunQuery(const QString &query)const;
        void Load(const QString &tablename, const Application::Types::DataSet &set);
        bool Clear(QString tablename);



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
