#include <iostream>>
#include <fstream>
#include <QDate>
#include "timetrackingdatastore.h"

using namespace std;

TimeTrackingDataStore::TimeTrackingDataStore() :
    timetrackitems_(NULL)
{
}

bool TimeTrackingDataStore::loadjson()
{
    ifstream ifs("timetrack.json");

    if (NULL == timetrackitems_)
    {
        timetrackitems_ = new picojson::value();
    }
    picojson::parse(*timetrackitems_, ifs);

    cout << timetrackitems_->serialize() << endl;
    return true;
}

bool TimeTrackingDataStore::writejson(QString trackitems)
{
    return true;
}

QString TimeTrackingDataStore::getTrackItems(QDate date)
{
    QString trackitems = "";

    return trackitems;
}
