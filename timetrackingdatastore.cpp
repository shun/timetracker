#include <iostream>>
#include <fstream>
#include <QDate>
#include <QStringList>
#include <qDebug>
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
    picojson::array array;
    array.clear();
    string stdstr = date.toStdString();
    if (obj.find(stdstr) != obj.end())
    {
        obj.erase(stdstr);
    }
    QStringList list = items.split("\n");
    QStringList tmp;
    string key;
    for (int idx = 0; idx < list.size(); idx++)
    {
        tmp = list.at(idx).split("\t");
        if (tmp.size() != 2) continue;

        picojson::object newobj;
        newobj.insert(make_pair("time", picojson::value(tmp[0].split(" ")[0].toStdString())));
        newobj.insert(make_pair("worktime", picojson::value(tmp[1].toStdString())));
        picojson::value iv(newobj);
        array.push_back(iv);
    }

    obj.insert(make_pair(stdstr, picojson::value(array)));
    cout << timetrackitems_->serialize() << endl;

    ofstream ofs("timetrack_new.json");
    ofs << timetrackitems_->serialize() << endl;
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
