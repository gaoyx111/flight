#ifndef DBOPERATOR_H
#define DBOPERATOR_H

#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include<passenger.h>
class DBOperator
{ private:
    QSqlDatabase dbcon;
    bool openFlag;
public:
    DBOperator();
    void DBOpen();
    void DBClose();
    void DBshow();
    bool DBadFind(QString id,QString password);
    bool DBpaFind(QString id,QString password);
    void setpa(QString newid,QString newname,QString newpassword);
    void changeflight_econums(QString id,int num);
    void changeflight_busnums(QString id, int num);
    void changeflight_firnums(QString id, int num);


    QSqlQuery DBGetData(QString sqlstr, bool &sucessFlag);
};

#endif // DBOPERATOR_H
