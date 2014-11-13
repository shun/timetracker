#ifndef TIMETRACKINGDATASTORE_H
#define TIMETRACKINGDATASTORE_H

#include <QObject>>
#include "picojson.h"

class TimeTrackingDataStore : public QObject
{
public:
    TimeTrackingDataStore();
    bool loadjson();
    bool writejson(QString trackitems);
    QString getTrackItems(QDate date);

private :
    picojson::value *timetrackitems_;
};

#endif // TIMETRACKINGDATASTORE_H
