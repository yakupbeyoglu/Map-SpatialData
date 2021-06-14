#include "application.h"
#include "Configs.h"
namespace Application {

Application::Application(int argc, char *argv[]):app(argc, argv)
{
         model = new Model(Configs::Model::hostname,
                        Configs::Model::databasename,
                        Configs::Model::username,
                        Configs::Model::password);

        if(model->IsConnect()){
                qDebug("Yes i am connected");
        }
        else
                qDebug("not connected");
       // modeltest.Select(5);
       auto v =  model->Select("busstops","location");
       auto v2 = model->Select("passenger","location");
       w.SetBusStop(v);
       w.SetPassengerStop(v2);

        w.show();
        app.exec();

}

}
