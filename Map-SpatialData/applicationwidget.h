#pragma once
#include <QtWidgets>
#include <QVector>
#include <QPixmap>
#include "sidewidget.h"
#include "customwidget.h"
#include "footer.h"
#include "Types.h"
#include "model.h"
#include "Configs.h"

class ApplicationWidget : public QWidget
{
        Q_OBJECT
public:
        explicit ApplicationWidget(QWidget *parent = nullptr) {
                model = new Application::Model(Application::Configs::Model::hostname,
                               Application::Configs::Model::databasename,
                               Application::Configs::Model::username,
                               Application::Configs::Model::password);

               if(model->IsConnect()){
                       qDebug("Yes i am connected");
               }
               else
                       qDebug("not connected");
                mainwidget = new CustomWidget();
                sidewidget = new SideWidget();
                footer = new Footer();
                layout = new QGridLayout(this);
                layout->addWidget(mainwidget,0,0);
                layout->addWidget(sidewidget,0,1);
                layout->addWidget(footer,1,0,1,2);
                this->setLayout(layout);

                QObject::connect(mainwidget,&CustomWidget::MouseLocation,
                                sidewidget, &SideWidget::GetCoordination);

                QObject::connect(sidewidget,&SideWidget::buseventcall,
                                 mainwidget, &CustomWidget::BusStateChange);

                QObject::connect(sidewidget,&SideWidget::passengereventcall,
                                 mainwidget, &CustomWidget::PassengerStateChange);
                QObject::connect(sidewidget,&SideWidget::wholeareaselection,
                                this, &ApplicationWidget::SelectWholeArea);

        }

        void SetBusStop(Application::Types::DataSet set) {
                mainwidget->SetBusses(set);
        }

        void SetPassengerStop(Application::Types::DataSet set) {
                mainwidget->SetPassenger(set);
        }
  public slots:

        void SelectWholeArea(bool busstate, bool passengerstate) {

                Application::Types::DataSet busvaluesid;
                Application::Types::DataSet busvaluesname;
                Application::Types::DataSet busvalueslocation;
                if( busstate ) {
                       busvaluesid = model->Select("busstops","id");
                       busvaluesname = model->Select("busstops","name");
                       busvalueslocation = model->Select("busstops","location");
                       QString query = "SELECT id from busstops;\nSELECT name from busstops;\nSELECT ST_AsText(location) from busstops;\n ";
                       footer->SetMessagebox(query, busvaluesid,busvaluesname,busvalueslocation);
                }

                if( passengerstate ) {
                       busvaluesid = model->Select("passenger","id");
                       busvaluesname = {};
                       busvalueslocation = model->Select("passenger","location");
                       QString query = "SELECT id from passenger;\nSELECT ST_AsText(location) from passenger;\n ";
                       footer->SetMessagebox(query, busvaluesid,busvaluesname,busvalueslocation);
                }


        }



private:
        SideWidget *sidewidget;
        CustomWidget   *mainwidget;
        Footer *footer;
        QGridLayout * layout;
        Application::Model *model;
};

