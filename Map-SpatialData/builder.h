#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "Configs.h"
#include "Types.h"

class Builder
{
public:
        explicit Builder(QString &filename);
        Application::Types::DataSet ParseFile();



private:
        static Application::Types::DataSet Parser(QTextStream &stream);
        QFile file;

};

#endif // BUILDER_H
