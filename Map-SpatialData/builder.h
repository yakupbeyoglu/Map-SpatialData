#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
#include <QSqlDatabase>
class Builder
{
public:
        Builder(QString filename);
        void load(QString filename);
};

#endif // BUILDER_H
