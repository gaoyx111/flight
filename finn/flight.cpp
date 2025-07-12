#include "flight.h"
flight::flight(){}
flight::flight(QString id,QString startcity,QString stopcity,QString endcity,QString starttime,QString endtime,QString company,QString startport,QString stopport,QString endport,int eco,int bus,int fir,int ecoprice,int busprice,int firprice)
{
    this->id=id;
    this->startcity=startcity;
    this->stopcity=stopcity;
    this->endcity=endcity;
    this->starttime=starttime;
    this->endtime=endtime;
    this->company=company;
    this->startport=startport;
    this->stopport=stopport;
    this->endport=endport;
    this->eco=eco;
    this->bus=bus;
    this->fir=fir;
    this->ecoprice=ecoprice;
    this->busprice=busprice;
    this->firprice=firprice;
}
QString flight::costTime()const
{

        QString format = "yyyy-MM-dd HH:mm:ss";

        // 将QString转换为QDateTime
        QDateTime time1 = QDateTime::fromString(starttime, format);
        QDateTime time2 = QDateTime::fromString(endtime, format);

        // 检查时间是否有效
        if (!time1.isValid() || !time2.isValid()) {
            qDebug() << "Invalid time format.";
        }

        // 计算时间差
        qint64 diff = time1.msecsTo(time2); // 获取毫秒差

        // 将毫秒转换为不同的时间单位
        qint64 seconds = diff / 1000; // 秒
        qint64 minutes = seconds / 60; // 分钟
        qint64 hours = minutes / 60; // 小时
        qint64 days = hours / 24; // 天

        qint64 hour=hours;
        qint64 min=minutes-60*hour;
        QString costtime = QString("%1h%2min").arg(hour).arg(min);
        return costtime;

}
int flight::timeDifference() const {
    QDateTime startDateTime = QDateTime::fromString(starttime, "yyyy-MM-dd HH:mm:ss");
    QDateTime endDateTime = QDateTime::fromString(endtime, "yyyy-MM-dd HH:mm:ss");

    if (!startDateTime.isValid() || !endDateTime.isValid()) {
        // 如果时间无效，可以返回一个特殊值或者抛出异常
        return 0; // 或者抛出异常
    }

    // 计算时间差（以分钟为单位）
    int differenceInMinutes = startDateTime.secsTo(endDateTime) / 60;
    return differenceInMinutes;
}

