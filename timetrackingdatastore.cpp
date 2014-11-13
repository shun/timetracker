#include <iostream>>
#include <fstream>
#include <QDate>
#include <QStringList>
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

bool TimeTrackingDataStore::storeTrackItems(QString date, QString items)
{
    picojson::object& obj = timetrackitems_->get<picojson::object>();
    picojson::array& array = obj[date.toStdString()].get<picojson::array>();
    array.clear();
    QStringList list = items.split("\n");
    QStringList tmp;
    string key;
    for (int idx = 0; idx < list.size(); idx++)
    {
        tmp = list.at(idx).split("\t");
        picojson::object newobj;
        newobj.insert(make_pair("time", picojson::value(tmp[0].toStdString())));
        newobj.insert(make_pair("worktime", picojson::value(tmp[1].toStdString())));
        picojson::value iv(newobj);
        array.push_back(iv);
    }

    cout << timetrackitems_->serialize() << endl;
    return true;
}

bool TimeTrackingDataStore::writejson()
{
    return true;
}

QString TimeTrackingDataStore::getTrackItems(QDate date)
{
    QString trackitems = "";

    return trackitems;
}
