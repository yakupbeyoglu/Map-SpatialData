#pragma once
#include <QVector>
#include <QString>

namespace Application {
        namespace Types {

                struct Data{
                   QString id;
                   QString name;
                   int x;
                   int y;
                };

                using DataSet = QVector<Data>;
        }
}
