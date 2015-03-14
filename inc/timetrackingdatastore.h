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
    Q_INVOKABLE QString getTrackItems(QString date);
    Q_INVOKABLE QString getTrackSummary(QString date);

private :
    picojson::value *timetrackitems_;
};

#endif // TIMETRACKINGDATASTORE_H
