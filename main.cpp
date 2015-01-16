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
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("datastore", &store);

    return app.exec();
}
