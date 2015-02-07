#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "timetrackingdatastore.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    TimeTrackingDataStore store;
    store.loadjson();
    store.getTrackItems("2015-01-17");
    engine.rootContext()->setContextProperty("datastore", &store);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
