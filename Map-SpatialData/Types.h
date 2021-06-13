#pragma once
#include <QVector>
#include <QString>

namespace Application {
        namespace Types {

                struct Point{
                        int x;
                        int y;
                };

                struct Data{
                   QString id;
                   QString name;
                   Point point;
                };



                using DataSet = QVector<Data>;
        }
}
