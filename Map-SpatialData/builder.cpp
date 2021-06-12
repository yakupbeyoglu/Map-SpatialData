#include "builder.h"
#include <QtDebug>

Builder:: Builder(QString &filename):file(filename)
{
        if(!file.open(QIODevice::ReadOnly)){
                throw ("File Not Found");
        }

}
Application::Types::DataSet Builder::ParseFile() {
        QTextStream filestream(&file);
        return Parser(filestream);
}

Application::Types::DataSet Builder::Parser(QTextStream &stream) {
        Application::Types::DataSet dataset;

        for(auto line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
                QStringList l = line.split(QRegExp("[,-]"));
                if(l.size() == 4) {
                        // for busstops.txt
                        dataset.push_back({l.at(0),l.at(1),l.at(2).toInt(),l.at(3).toInt()});
                }
                else if(l.size() == 3 ) {
                        //for Passenger.txt
                        dataset.push_back({l.at(0),NULL,l.at(1).toInt(),l.at(2).toInt()});
                }
                else
                        throw("File Not well defined");
        }

        return dataset;
}
