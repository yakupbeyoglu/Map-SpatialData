#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "model.h"
#include "builder.h"
#include "Configs.h"
#include <QtDebug>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
//Model(QString hostname="", QString databasename="", QString username="", QString password="");
        Model modeltest(Application::Configs::Model::hostname,
                        Application::Configs::Model::databasename,
                        Application::Configs::Model::username,
                        Application::Configs::Model::password);

        if(modeltest.IsConnect()){
                qDebug("Yes i am connected");
        }
        else
                qDebug("not connected");
        modeltest.Insert("busstops","3,\"yakup\",POINT(3,5)");

        QString filename = "/home/yakup/git/Map-SpatialData/Data/Passenger.txt";

        Builder build(filename);
        auto parsed = build.ParseFile();



        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                        QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        return app.exec();
}
