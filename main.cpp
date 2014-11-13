#include <QApplication>
#include <QQmlApplicationEngine>
#include "timetrackingdatastore.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    TimeTrackingDataStore store;
    store.loadjson();
    store.storeTrackItems("2014-10-14","09:00\taaaaaaa\n10:00\tbbbbbbbb");
    return app.exec();
}
