#include "customerservicepage.h"
#include "loginwindow.h"
#include "checkWindow.h"
#include "DBOperator.h"
#include "homepage.h"
#include "InfoWindow.h"
#include "managerlogin.h"
#include "managerwindow.h"
#include "placeorder.h"
#include "registerwindow.h"
#include<passenger.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<flight.h>
passenger pa;
DBOperator op;
QVector<flight> fl;
QVector<flight> chosen_fl;
int Cancelsignal=0;//是否有取消按键
int Buysignal=0;//是否改签
int fromhomepage=0;
flight flightfrompage;

int main(int argc, char *argv[])
{
    DBOperator dbo;
    dbo.DBOpen();
    dbo.DBshow();
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FlightProject_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    LoginWindow w;
    w.show();
    // PlaceOrder w;
    // w.show();
    return a.exec();
}

/*
int main(int argc, char *argv[])
{
    QVector<flight>f;

    f[0].setcampany("东航");
    f[0].setflNum("ABC15456");
    f[0].setstartCity("上海");
    f[0].setendCity("北京");
    f[0].setClass(10,20,30,3000,2000,1000);
    f[0].setstartTime("7:00");
    f[0].setendTime("18:00");
    QFile file("D:/mycode/planeSystem/flight.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<f[0].getcampany()<<f[0].getstartCity()<<"-->"<<f[0].getendCity()<<f[0].getstartTime()<<"-"<<f[0].getendTime();
    file.close();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
