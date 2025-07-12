#include <QApplication>
#include<Qlist>
#include<QString>
#include<QTextStream>
#include<QFile>
#include<QDebug>
#include<Qvector>



class administrator
{
    //用于登陆
    QString name;  //姓名
    QString ID;    //ID
    administrator(QString na,QString I)
    {
        name=na;
        ID=I;
    }
};

class passenger
{
    QString name;//乘客姓名
    QString ID;//身份证号
    int range;//会员等级
    // passenger *next;
public:
    passenger(QString na,QString I,int a)
    {
        name=na;
        ID=I;
        range=a;
    }
};

class cl
{
    int nums;//舱位数
    double price;//票价
public:
    void setnums(int n)
    {
        nums=n;
    }
    void setprice(double p)
    {
        price=p;
    }
};

class flight
{
    QString campany;//航空公司

    QString startCity;//出发地
    QString stopCity;//中转站
    QString endCity;//目的地

    QString startport;//起飞机场
    QString stopport;//中转机场
    QString endport;//到达机场

    QString startTime;//出发时间
    QString endTime;//到达时间

    QString flNum;//航班号
    cl Class[3];//1、头等舱  2、商务舱  3、经济舱
public:
    void setcampany(QString c)
    {
        campany=c;
    }
    void setstartCity(QString city)
    {
        startCity=city;
    }
    void setendCity(QString city)
    {
        endCity=city;
    }
    void setClass(int n1,int n2,int n3,double p1,double p2,double p3)
    {
        Class[1].setnums(n1);
        Class[1].setprice(p1);
        Class[2].setnums(n2);
        Class[2].setprice(p2);
        Class[3].setnums(n3);
        Class[3].setprice(p3);
    }
    void setstartTime(QString time)
    {
        startTime=time;
    }
    void setendTime(QString time)
    {
        endTime=time;
    }
    void setflNum(QString n)
    {
        flNum=n;
    }
    QString getcampany()
    {
        return campany;
    }
    QString getstartCity()
    {
        return startCity;
    }
    QString getendCity()
    {
        return endCity;
    }
    QString getstartTime()
    {
        return startTime;
    }
    QString getendTime()
    {
        return endTime;
    }
};
