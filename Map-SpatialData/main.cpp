#include <QApplication>
#include "customwidget.h"
#include "model.h"
#include "builder.h"
#include "Configs.h"
#include <QtDebug>
#include "application.h"
int main(int argc, char *argv[])
{

//Model(QString hostname="", QString databasename="", QString username="", QString password="");
        Application::Model modeltest(Application::Configs::Model::hostname,
                        Application::Configs::Model::databasename,
                        Application::Configs::Model::username,
                        Application::Configs::Model::password);

        if(modeltest.IsConnect()){
                qDebug("Yes i am connected");
        }
        else
                qDebug("not connected");
       // modeltest.Select(5);
       auto v =  modeltest.Select("busstops","location");
     //   QStringList Model::Select(const QString &tablename, const QString &columnname, QString id)

      /*  QString passangerfilepath = "/home/yakup/git/Map-SpatialData/Data/Passenger.txt";
        QString passangertablename = "passenger";
        QString busstopsfilepath = "/home/yakup/git/Map-SpatialData/Data/busstops.txt";
        QString busstopstablename = "busstops";
        Builder buildpassanger(passangerfilepath);
        Builder buildbusstops(busstopsfilepath);

        auto parsedpassanger = buildpassanger.ParseFile();
        auto parsedbusstops = buildbusstops.ParseFile();
        modeltest.Load(passangertablename,parsedpassanger);
        modeltest.Load(busstopstablename, parsedbusstops);*/

       Application::Application app(argc,argv);

//        return app.exec();
}
