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
    return app.exec();
}
