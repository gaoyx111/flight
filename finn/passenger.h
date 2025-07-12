#ifndef PASSENGER_H
#define PASSENGER_H
#include<QString>
#include<ticket.h>
#include<QVector>
class passenger
{
    QString id;
    QString name;
    QString password;
    QString rank;
    QString nickname;
    QString birthday;
public:

    passenger();
    void setpassenger(QString newid,QString newname,QString newpassword,QString newrank,QString newnickname);
    void show();
    QString getid();
    QString getname();
    QString getpassword();
    QString getrank();
    QString getnickname();
    QVector<ticket> bought_ticket;
    void setbirtday(QString bir)
    {
        birthday=bir;
    }
};

#endif // PASSENGER_H
