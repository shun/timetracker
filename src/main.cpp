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
    engine.rootContext()->setContextProperty("datastore", &store);
    engine.load(QUrl(QStringLiteral("qrc:/res/qml/main.qml")));

    return app.exec();
}
