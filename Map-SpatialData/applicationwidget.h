#pragma once
#include <QtWidgets>
#include <QVector>
#include <QPixmap>
#include "sidewidget.h"
#include "customwidget.h"
#include "footer.h"
#include "Types.h"


class ApplicationWidget : public QWidget
{
        Q_OBJECT
public:
        explicit ApplicationWidget(QWidget *parent = nullptr) {
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

        }

        void SetBusStop(Application::Types::DataSet set) {
                mainwidget->SetBusses(set);
        }

        void SetPassengerStop(Application::Types::DataSet set) {
                mainwidget->SetPassenger(set);
        }


private:
        SideWidget *sidewidget;
        CustomWidget   *mainwidget;
        Footer *footer;
        QGridLayout * layout;
};

