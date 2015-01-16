#ifndef TIMETRACKINGDATASTORE_H
#define TIMETRACKINGDATASTORE_H

#include <QObject>
#include "picojson.h"

class TimeTrackingDataStore : public QObject
{
    Q_OBJECT

public:
    TimeTrackingDataStore();
    bool loadjson();
    bool writejson();
    Q_INVOKABLE bool storeTrackItems(QString date, QString items);
    QString getTrackItems(QDate date);

private :
    picojson::value *timetrackitems_;
};

#endif // TIMETRACKINGDATASTORE_H
