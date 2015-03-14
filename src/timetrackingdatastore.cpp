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
    qDebug() << __FUNCTION__;
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
        newobj.insert(make_pair("workitem", picojson::value(tmp[1].toStdString())));
        picojson::value iv(newobj);
        array.push_back(iv);
    }

    obj.insert(make_pair(stdstr, picojson::value(array)));
    cout << timetrackitems_->serialize() << endl;

    writejson();
    return true;
}

bool TimeTrackingDataStore::writejson()
{
    ofstream ofs("timetrack.json");
    ofs << timetrackitems_->serialize() << endl;
    return true;
}

QString TimeTrackingDataStore::getTrackItems(QString date)
{
    string trackitems = "";
    picojson::object& obj = timetrackitems_->get<picojson::object>();

    if (obj.find(date.toStdString()) == obj.end())
    {
        return "";
    }

    picojson::array& dat = obj[date.toStdString()].get<picojson::array>();
    picojson::array::iterator it;
    picojson::object item;

    for (it = dat.begin(); it < dat.end(); it++)
    {
        if (trackitems.length() != 0)
        {
            trackitems += "\n";
        }
        item = it->get<picojson::object>();
        trackitems += item["time"].get<std::string>() + "\t" + item["workitem"].get<std::string>();
    }

    return QString::fromStdString(trackitems);
}
