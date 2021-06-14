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

private :
        QApplication app;
        Model *model;
        ApplicationWidget w;
};
}


