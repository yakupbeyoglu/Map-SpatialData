#pragma once
#include <QApplication>
#include "applicationwidget.h"
#include "model.h"
#include "Types.h"
namespace Application {
class Application
{
public:
        Application(int argc, char *argv[]);

public slots:
        void SelectWholeArea(bool busstate, bool passengerstate);
signals:
        void SetFooter(const Types::DataSet &id, const Types::DataSet &name, const Types::DataSet &location);

private :
        QApplication app;
        Model *model;
        ApplicationWidget w;
};
}


