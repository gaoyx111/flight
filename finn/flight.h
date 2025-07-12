#ifndef FLIGHT_H
#define FLIGHT_H
#include<QString>
#include<QDateTime>
class flight
{
public:
    QString id;
    QString startcity;
    QString  stopcity;
    QString endcity;
    QString starttime;
    QString endtime;
    QString company;
    QString startport;
    QString stopport;
    QString endport;
    int eco;
    int bus;
    int fir;
    int ecoprice;
    int busprice;
    int firprice;
public:
    flight();
    flight(QString id,QString startcity,QString stopcity,QString endcity,QString starttime,QString endtime,QString company,QString startport,QString stopport,QString endport,int eco,int bus,int fir,int ecoprice,int busprice,int firprice);
    QString costTime()const;
    int timeDifference() const;

};

#endif // FLIGHT_H
