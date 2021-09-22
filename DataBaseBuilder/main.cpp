#include "../Map-SpatialData/builder.h"
#include "../Map-SpatialData/model.h"
#include <iostream>
int main(int argc, char *argv[])
{
        Application::Model modeltest(Application::Configs::Model::hostname,
                        Application::Configs::Model::databasename,
                        Application::Configs::Model::username,
                        Application::Configs::Model::password);
        if(modeltest.IsConnect()){
                qDebug("Yes i am connected");
        }
        else
                qDebug("not connected");


        if(argc > 2) {
                QString filepath1 = argv[1];
                QString filepath2 = argv[2];
                std::cout<<filepath1.toStdString()<<" "<<filepath2.toStdString()<<std::endl;
                std::cout<<"database clear process"<<std::endl;

                // clear database
                if(!modeltest.Clear("busstops"))
                        throw("Error on database busstop clean");
                if(!modeltest.Clear("passenger"))
                        throw("Error on database passenger clean");

                std::cout<<"Files parsed"<<std::endl;

                Builder buildbus(filepath1);
                Builder buildpassenger(filepath2);

                auto parsedbus = buildbus.ParseFile();
                auto parsedpassenger = buildpassenger.ParseFile();


                modeltest.Load("busstops",parsedbus);
                modeltest.Load("passenger",parsedpassenger);
                std::cout<<"Database Created"<<std::endl;




        }

        return 0;
}
