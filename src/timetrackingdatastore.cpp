#include <iostream>
#include <fstream>
#include <QDate>
#include <QDateTime>
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
        if (ifs)
        {
            timetrackitems_ = new picojson::value();
            picojson::parse(*timetrackitems_, ifs);
        }
        else
        {
            timetrackitems_ = new picojson::value(picojson::object_type, true);
        }
    }

//    cout << timetrackitems_->serialize() << endl;
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

    ofstream ofs("timetrack.json");
    ofs << timetrackitems_->serialize(true) << endl;
    return true;
}

bool TimeTrackingDataStore::writejson()
{
    return true;
}

QString TimeTrackingDataStore::getTrackSummary(QString date)
{
    QString trackitems = "";

    picojson::object& obj = timetrackitems_->get<picojson::object>();
    picojson::array array;
    array.clear();
    string stdstr = date.toStdString();
    if (obj.find(stdstr) == obj.end())
    {
        return "";
    }

    array = obj[stdstr].get<picojson::array>();

    QDateTime prevtime;
    QDateTime curtime;
    string workitem = "";
    QString str = "";
    QString fmt = "yyyy-MM-dd hh:mm";
    int hour, min;
    int delta = 0;
    bool firstdat = true;

    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
    {
        picojson::object& o = it->get<picojson::object>();
        str = QString::fromStdString(stdstr + " " + o["time"].get<string>());
        workitem = o["workitem"].get<string>();
        if (firstdat)
        {
            prevtime = QDateTime::fromString(str, fmt);
            firstdat = false;
        }
        else
        {
            /*
             * format :
             * [starttime] [endtime] [worktime] [workitem]
             *
             */
            curtime = QDateTime::fromString(str, fmt);
            delta = curtime.secsTo(prevtime);
            hour = delta / 60/60;
            min = (delta - hour * 60 * 60) / 60;
            char wtime[8];
            sprintf(wtime, "%02d:%02d", hour, min);

            trackitems += curtime.toString("hh:mm") + "\t" +
                            prevtime.toString("hh:mm") + "\t" +
                            QString::fromLocal8Bit(wtime) + "\t" +
                            QString::fromStdString(workitem) + "\n";
            prevtime = curtime;

        }
    }

    return trackitems;
}

QString TimeTrackingDataStore::getTrackItems(QString date)
{
    string trackitems = "";

    picojson::object& obj = timetrackitems_->get<picojson::object>();
    picojson::array array;
    array.clear();
    string stdstr = date.toStdString();
    if (obj.find(stdstr) == obj.end())
    {
        return "";
    }

    array = obj[stdstr].get<picojson::array>();

    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
    {
        picojson::object& o = it->get<picojson::object>();
        trackitems += o["time"].get<string>() + "\t" +
                o["workitem"].get<string>() + "\n";
    }

    return QString::fromStdString(trackitems);
}
