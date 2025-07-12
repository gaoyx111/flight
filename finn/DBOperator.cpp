#include "DBOperator.h"
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include<passenger.h>
#include<QRandomGenerator>
#include<DBOperator.h>
extern passenger pa;
DBOperator::DBOperator()
{   openFlag = false; }

void DBOperator::DBOpen()
{   //QString dsn;
    if(!openFlag)
    {
        /*
        dbcon = QSqlDatabase::addDatabase("QODBC");
        dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=G:/OneDrive/Desktop/software engineering train/software engineering train download/SQLTest/SQLDB.mdb");
        dbcon.setDatabaseName(dsn);
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "错误, SQLDB 数据库文件打开失败！";
        openFlag = true;
        */

        /*  QT 通过 ODBC 连接 MySQL 数据库； 数据源配置见《QT 通过 ODBC 连接 MySQL8.doc》 文档*/
        dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
        dbcon.setHostName("127.0.0.1");              // MySQL 服务器ip地址，本机
        dbcon.setPort(3306);                         // 端口号，默认
        dbcon.setDatabaseName("flight");           // ODBC 数据源名称
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "Error,  persondatabase 数据库文件打开失败！";
        else
            qDebug() <<"数据库打开成功";
        openFlag = true;
    }
}

void DBOperator::DBClose()
{   openFlag = false;
    dbcon.close();
}

void DBOperator::DBshow()
{
    if(!openFlag){
        dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
        dbcon.setHostName("127.0.0.1");              // MySQL 服务器ip地址，本机
        dbcon.setPort(3306);                         // 端口号，默认
        dbcon.setDatabaseName("flight");           // ODBC 数据源名称
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "Error,  persondatabase 数据库文件打开失败！";
        else
            qDebug() <<"数据库打开成功";
        openFlag = true;
    }

    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM administrator")) {
        while (query.next()) {
            int id = query.value("administrator_id").toInt();
            QString name = query.value("administrator_name").toString();
            qDebug() << "ID:" << id << "Name:" << name;
        }
    } else {
        qDebug() << "查询失败：" << query.lastError();
    }
}


bool DBOperator::DBadFind(QString id, QString password)
{
    if(!openFlag){
        dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
        dbcon.setHostName("127.0.0.1");              // MySQL 服务器ip地址，本机
        dbcon.setPort(3306);                         // 端口号，默认
        dbcon.setDatabaseName("flight");           // ODBC 数据源名称
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "Error,  persondatabase 数据库文件打开失败！";
        else
            qDebug() <<"数据库打开成功";
        openFlag = true;
    }

    QSqlQuery query;
    query.exec("USE flight");

    // 使用 prepare() 来准备查询，避免拼接字符串
    query.prepare("SELECT * FROM administrator WHERE administrator_id = :id AND administrator_password = :password");

    // 绑定参数
    query.bindValue(":id", id);
    query.bindValue(":password", password);

    // 执行查询
    if (query.exec()) {
        if (query.next()) {
            qDebug() << "该用户存在且登录成功";
            // 可以在这里设置相关的用户信息等
            return true;
        }
        qDebug() << "登录失败";
        return false;
    }
    return false;
}



// void DBOperator::setpa(QString newid,QString newname,QString newpassword,QString newrank,QString newnickname)
// {
//     pa.setpassenger(newid,newname,newpassword,newrank,newnickname);
// }

bool DBOperator::DBpaFind(QString id, QString password)
{
    QSqlQuery query;
    query.exec("USE flight");
    QString queryStr = "SELECT * FROM passenger WHERE passenger_id = :id AND passenger_password = :password";

    query.prepare(queryStr);
    query.bindValue(":id", id);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            qDebug() << "该用户存在且登录成功";

            // 将查询结果赋值给 pa 对象
            pa.setpassenger(query.value("passenger_id").toString(),
                            query.value("passenger_name").toString(),
                            query.value("passenger_password").toString(),
                            query.value("passenger_rank").toString(),
                            query.value("passenger_nickname").toString());
            return true;
        }
        qDebug() << "登录失败";
        return false;
    }
    return false;
}


void DBOperator::setpa(QString newid, QString newname, QString newpassword)
{
    QSqlQuery query;
    query.exec("USE flight");
    QString insertQuery = "INSERT INTO passenger (passenger_id, passenger_name, passenger_rank, passenger_password, passenger_nickname) VALUES (?, ?, ?, ?, ?)";
    query.prepare(insertQuery);

    int random_number = QRandomGenerator::global()->generate() % (50000 - 200 + 1) + 200;
    query.addBindValue(newid); // value1 是要插入到 passenger_id 的值
    query.addBindValue(newname); // value2 是要插入到 passenger_name 的值
    query.addBindValue(1); // value3 是要插入到 passenger_rank 的值
    query.addBindValue(newpassword); // value4 是要插入到 passenger_password 的值

    // 创建一个包含单个字符的 QString
    QString num=QString::number(random_number);
    QString nickname="用户"+num;
    query.addBindValue(nickname); // value5 是要插入到 passenger_nickname 的值

    if (!query.exec()) {
        // 插入失败，处理错误
        qDebug() << "插入失败: " << query.lastError().text();
    } else {
        // 插入成功
        qDebug() << "数据插入成功";
    }
}


void DBOperator::changeflight_econums(QString id, int num)
{
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("UPDATE flight_info SET economyClass = :num WHERE flight_id = :id");
    query.bindValue(":num", num - 1);
    query.bindValue(":id", id);
    if (query.exec())
    {
        qDebug() << "Update successful.";
    }
    else
    {
        qDebug() << "Update failed:" << query.lastError().text();
    }
}

void DBOperator::changeflight_busnums(QString id, int num)
{
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("UPDATE flight_info SET businessClass = :num WHERE flight_id = :id");
    query.bindValue(":num", num - 1);
    query.bindValue(":id", id);
    if (query.exec())
    {
        qDebug() << "Update successful.";
    }
    else
    {
        qDebug() << "Update failed:" << query.lastError().text();
    }
}

void DBOperator::changeflight_firnums(QString id, int num)
{
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("UPDATE flight_info SET firstClass = :num WHERE flight_id = :id");
    query.bindValue(":num", num - 1);
    query.bindValue(":id", id);
    if (query.exec())
    {
        qDebug() << "Update successful.";
    }
    else
    {
        qDebug() << "Update failed:" << query.lastError().text();
    }
}



QSqlQuery DBOperator::DBGetData(QString sqlstr, bool &sucessFlag)
{   QSqlQuery query = QSqlQuery(dbcon);
    query.exec("USE flight");
    sucessFlag = query.exec(sqlstr);
    return query;
}
