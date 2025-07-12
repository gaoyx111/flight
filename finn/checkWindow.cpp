#include "checkWindow.h"
#include "flight.h"
#include "paymentdialog.h"
#include "placeorder.h"
#include "ui_checkWindow.h"
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>
#include<DBOperator.h>
#include<QList>
#include<QSqlRecord>
#include<QSqlError>
#include<QLabel>
#include<QWidget>
#include<QMessageBox>
#include<QCalendarWidget>
#include<ticket.h>
#include <QRandomGenerator>
#include <QString>
#include <QStringBuilder>
#include <QRandomGenerator>
#include <QString>
#include <QStringBuilder>
#include<QVector>
extern DBOperator op;
extern QVector<flight> fl;
extern passenger pa;
extern QString num;
extern int Buysignal;
extern int fromhomepage;
extern flight flightfrompage;
bool comparestartTime(const flight& flight1, const flight& flight2) {
    QDateTime dateTime1 = QDateTime::fromString(flight1.starttime, "yyyy-MM-dd HH:mm:ss");
    QDateTime dateTime2 = QDateTime::fromString(flight2.starttime, "yyyy-MM-dd HH:mm:ss");

    return dateTime1 < dateTime2;
}

bool comparecostTime(const flight& flight1, const flight& flight2) {
    return flight1.timeDifference() < flight2.timeDifference();
}


bool comparePrice(const flight& flight1, const flight& flight2) {
    return flight1.ecoprice < flight2.ecoprice;
}
bool checkWindow::oncheckButtonClicked() {
    QMessageBox::information(this, "查询信息", "点击查询按钮");

    // 执行查询逻辑，并显示机票信息


    return true;
}



void checkWindow::setstartcity()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM startCities")) {
        while (query.next()) {
            QString city = query.value("CityName").toString();
            startcity<<city;
            //            qDebug()<<"打开数据库";
            //            qDebug() << "city:"<<city;
        }
    } else {
        qDebug() << "查询失败：" ;
    }

}

void checkWindow::setendcity()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM endCities")) {
        while (query.next()) {
            QString city = query.value("CityName").toString();
            endcity<<city;
            //            qDebug()<<"打开数据库";
            //            qDebug() << "city:"<<city;
        }
    } else {
        qDebug() << "查询失败：" ;
    }

}

void checkWindow::setstopcity()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM stopCities")) {
        while (query.next()) {
            QString city = query.value("CityName").toString();
            stopcity<<city;
            //            qDebug()<<"打开数据库";
            //            qDebug() << "city:"<<city;
        }
    } else {
        qDebug() << "查询失败：" ;
    }

}


void checkWindow::maketicket(QString startcity,QString stopcity,QString endcity,QString godate,QScrollArea *scroller)
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(20);
    QVector<flight>firstchosen;
    QVector<flight> chosen;
    QSqlQuery query;
    query.exec("USE flight");
    QDateTime today=QDateTime::currentDateTime();
    if (query.exec("SELECT * FROM flight_info")) {
        while (query.next()) {
            QString startTimeStr = query.value("startTime").toString(); // 假设这是从数据库中获取的时间字符串
            QStringList parts = startTimeStr.split(' ');
            QString timePart = parts.size() >= 2 ? parts[1] : QString();
            QString datePart = parts.size()>=2?parts[0]:QString();

            QString endTimeStr = query.value("endTime").toString(); // 假设这是从数据库中获取的时间字符串
            QStringList endparts = endTimeStr.split(' ');
            QString endTimePart = endparts.size() >= 2 ? endparts[1] : QString();
            QString enddatePart = endparts.size()>=2?parts[0]:QString();

            QDateTime time=QDateTime::fromString(query.value("startTime").toString(),"yyyy-MM-dd HH:mm:ss");
            if(query.value("startCity").toString()==startcity&&query.value("endCity").toString()==endcity&&datePart==godate&&time>today)
            {
                flight * f=new flight(query.value("flight_id").toString(),query.value("startCity").toString(),query.value("stopCity").toString(),query.value("endCity").toString(),query.value("startTime").toString(),query.value("endTime").toString(),query.value("flight_company").toString(),query.value("startport").toString(),query.value("stopport").toString(),query.value("endport").toString(),query.value("economyClass").toInt(),query.value("businessClass").toInt(),query.value("firstClass").toInt(),query.value("economyPrice").toInt(),query.value("businessPrice").toInt(),query.value("firstPrice").toInt());
                firstchosen.push_back(*f);
            }
        }

        if(ui->direct->isChecked())
        {
            for(int i = 0; i < firstchosen.size(); ++i)
            {
                if(firstchosen[i].stopcity.isEmpty()) // 使用isEmpty()来检查QString是否为空
                {
                    chosen.push_back(firstchosen[i]);
                }
            }
        }


        else if(stopcity=="不限")
        {
            for(int i=0;i<firstchosen.size();i++)
            {
                chosen.push_back(firstchosen[i]);
            }
        }
        else{
            for(int i=0;i<firstchosen.size();i++)
            {
                if(firstchosen[i].stopcity==stopcity)
                {
                    chosen.push_back(firstchosen[i]);
                }
            }}

    } else {
        qDebug() << "查询失败：" ;
    }
    if(ui->chose->currentText()=="发时最早")
    {
        std::sort(chosen.begin(), chosen.end(), comparestartTime);
    }
    else if(ui->chose->currentText()=="耗时最短")
    {
        std::sort(chosen.begin(),chosen.end(),comparecostTime);
        for(int i=0;i<chosen.size();i++)
        {
            qDebug()<<chosen[i].timeDifference();
        }
    }
    else if(ui->chose->currentText()=="价格最低")
    {
        std::sort(chosen.begin(),chosen.end(),comparePrice);
    }
    if(chosen.size() == 0||firstchosen.size()==0)
    {
        QWidget *Widget_2 = new QWidget();
        QVBoxLayout *Layout_2 = new QVBoxLayout(Widget_2);
        QLabel *notion_2 = new QLabel("未找到符合条件的机票", Widget_2);
        notion_2->setAlignment(Qt::AlignCenter); // 设置标签居中对齐
        Layout_2->addWidget(notion_2); // 将标签添加到布局中
        vLayout->addWidget(Widget_2); // 将包含标签的 Widget 添加到滚动区域的布局中
    }
    for(int i=0;i<chosen.size();i++)
    {
        qDebug()<<"找到机票"<<chosen[i].startport<<chosen[i].endport;
        QWidget *infoWidget = new QWidget();
        infoWidget->setFixedSize(730,160);
        QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
        QFont font("Arial", 25, QFont::Bold);


        QLabel *startportlabel = new QLabel(chosen[i].startport, infoWidget);
        // startportlabel->setFont(font);
        startportlabel->setMinimumSize(300, 50);
        startportlabel->move(30,70);

        QLabel *endportlabel = new QLabel(chosen[i].endport, infoWidget);
        // endportlabel->setFont(font);
        endportlabel->setMinimumSize(300, 50);
        endportlabel->move(290,70);

        QString id = chosen[i].id;
        QString company=chosen[i].company;
        QLabel *flight_id=new QLabel(company+id,infoWidget);
        flight_id->setMinimumSize(300,50);
        QPalette palette = flight_id->palette();
        palette.setColor(QPalette::WindowText, qRgb(178,178,178)); // 红色
        flight_id->setPalette(palette);
        flight_id->move(30,110);


        QString string=QString::number(chosen[i].eco);
        QLabel *economyclass = new QLabel("经济舱：余"+string, infoWidget);
        economyclass->setMinimumSize(150,30);
        economyclass->move(450,20);

        string=QString::number(chosen[i].bus);
        QLabel *businessclass = new QLabel("商务舱：余"+string, infoWidget);
        businessclass->setMinimumSize(150,30);
        businessclass->move(450,65);

        string=QString::number(chosen[i].fir);
        QLabel *firstclass = new QLabel("头等舱：余"+string, infoWidget);
        firstclass->setMinimumSize(150,30);
        firstclass->move(450,110);


        QString startTimeStr = chosen[i].starttime; // 假设这是从数据库中获取的时间字符串
        QStringList parts = startTimeStr.split(' ');
        QString timePart = parts.size() >= 2 ? parts[1] : QString();

        QString endTimeStr = chosen[i].endtime; // 假设这是从数据库中获取的时间字符串
        QStringList endparts = endTimeStr.split(' ');
        QString endTimePart = endparts.size() >= 2 ? endparts[1] : QString();

        QLabel *starttimelabel = new QLabel(timePart, infoWidget);
        starttimelabel->setFont(font);
        starttimelabel->setMinimumSize(150, 50);
        starttimelabel->move(30,30);
        QLabel *endtimelabel = new QLabel(endTimePart, infoWidget);
        endtimelabel->setFont(font);
        endtimelabel->setMinimumSize(150, 50);
        endtimelabel->move(290,30);

        if(!chosen[i].stopcity.isEmpty())
        {
            QFont font4("Arial", 10);
            QLabel *stop = new QLabel("中转"+chosen[i].stopcity,infoWidget);
            stop->setPalette(palette);
            stop->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

            stop->setFont(font4);
            stop->move(195,60);
        }

        // m_flightId = chosen[i].id;          // 设置航班ID
        // m_cabinClass = "经济舱";            // 设置舱位等级
        // m_selectedFlight = chosen[i];
        QPushButton *buyeco = new QPushButton("购买经济舱", infoWidget);
        // buyeco->setFont(font);
        buyeco->setStyleSheet("QPushButton { "
                              "background-color:  rgb(85, 170, 255); color: white;"
                              "border-radius: 10px;  "
                              "}");
        // 显式按值捕获变量 chosen 和 i，并显式捕获 flightId
        connect(buyeco, &QPushButton::clicked, this, [this, chosen, i]() {
            QString flightId = chosen[i].id;
            QString cabinClass = "经济舱";
            const flight& selectedFlight = chosen[i];
            this->onBuyButtonClickedSlot(flightId, cabinClass, selectedFlight);
        });
        buyeco->move(570,20);

        QPushButton *buybus = new QPushButton("购买商务舱", infoWidget);
        // buybus->setFont(font);
        buybus->setStyleSheet("QPushButton { background-color:rgb(85, 170, 255); color: white; border-radius: 10px;}");
        connect(buybus, &QPushButton::clicked, this, [this, chosen, i]() {
            QString flightId = chosen[i].id;
            QString cabinClass = "商务舱";
            const flight& selectedFlight = chosen[i];
            this->onBuyButtonClickedSlot(flightId, cabinClass, selectedFlight);
        });
        buybus->move(570,65);

        QPushButton *buyfir = new QPushButton("购买头等舱", infoWidget);
        // buyfir->setFont(font);
        buyfir->setStyleSheet("QPushButton { background-color:rgb(85, 170, 255); color: white;border-radius: 10px; }");
        connect(buyfir, &QPushButton::clicked, this, [this, chosen, i]() {
            QString flightId = chosen[i].id;
            QString cabinClass = "头等舱";
            const flight& selectedFlight = chosen[i];
            this->onBuyButtonClickedSlot(flightId, cabinClass, selectedFlight);
        });
        buyfir->move(570,110);


        QFont font1("Arial", 12, QFont::Bold);
        string=QString::number(chosen[i].ecoprice);
        QLabel *ecoprice=new QLabel("\u00A5"+string,infoWidget);
        ecoprice->setFont(font1);
        ecoprice->move(680,20);

        string =QString::number(chosen[i].busprice);
        QLabel *busprice=new QLabel("\u00A5"+string,infoWidget);
        busprice->setFont(font1);
        busprice->move(680,65);

        string =QString::number(chosen[i].firprice);
        QLabel *firprice=new QLabel("\u00A5"+string,infoWidget);
        firprice->setFont(font1);
        firprice->move(680,110);

        QLabel * d1 = new QLabel("——✈——",infoWidget);
        d1->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        d1->setFont(font1);
        QPalette pal3 = d1->palette();
        pal3.setColor(QPalette::WindowText, qRgb(85,170,255));
        d1->setPalette(palette);
        d1->setMinimumSize(100,10);
        d1->move(183,45);

        QLabel * costtime = new QLabel(chosen[i].costTime(),infoWidget);
        costtime->setPalette(palette);
        costtime->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

        costtime->move(195,30);
        QLabel picture(infoWidget);
        picture.setPixmap(QPixmap("path/to/your/image.png")); // 确保路径正确

        infoWidget->setStyleSheet(
            "QWidget {"
            "    background-color: white;"

            "    border-radius: 15px;" // 设置圆角大小
            "}"
            );
        // 将信息 widget 添加到垂直布局中
        // 创建水平布局
        QHBoxLayout *hLayout = new QHBoxLayout;

        // 在布局的开始处添加弹簧
        hLayout->addStretch(1);

        // 添加其他组件
        hLayout->addWidget(infoWidget); // 假设 infoWidget 是一个 QWidget*

        // 在布局的末尾处添加弹簧
        hLayout->addStretch(1);

        // 创建一个 QWidget 作为水平布局的容器
        QWidget *hContainer = new QWidget;

        // 将水平布局设置到容器上
        hContainer->setLayout(hLayout);

        // 将容器添加到垂直布局中
        vLayout->addWidget(hContainer);

    }
    vLayout->addStretch(1);
    // 将布局设置到滚动区域的窗口内容

    scroller->widget()->setLayout(vLayout);
}

void checkWindow::makesmallticket(QString startcity,QString stopcity,QString endcity,QString godate,QScrollArea *scroller)
{
    QDateTime today =QDateTime::currentDateTime();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(20);
    QVector<flight>firstchosen;
    QVector<flight> chosen;
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM flight_info")) {
        while (query.next()) {
            QString startTimeStr = query.value("startTime").toString(); // 假设这是从数据库中获取的时间字符串
            QStringList parts = startTimeStr.split(' ');
            QString timePart = parts.size() >= 2 ? parts[1] : QString();
            QString datePart = parts.size()>=2?parts[0]:QString();

            QString endTimeStr = query.value("endTime").toString(); // 假设这是从数据库中获取的时间字符串
            QStringList endparts = endTimeStr.split(' ');
            QString endTimePart = endparts.size() >= 2 ? endparts[1] : QString();
            QString enddatePart = endparts.size()>=2?parts[0]:QString();

            QDateTime time=QDateTime::fromString(query.value("startTime").toString(),"yyyy-MM-dd HH:mm:ss");
            if(query.value("startCity").toString()==startcity&&query.value("endCity").toString()==endcity&&datePart==godate&&time>today)
            {
                flight * f=new flight(query.value("flight_id").toString(),query.value("startCity").toString(),query.value("stopCity").toString(),query.value("endCity").toString(),query.value("startTime").toString(),query.value("endTime").toString(),query.value("flight_company").toString(),query.value("startport").toString(),query.value("stopport").toString(),query.value("endport").toString(),query.value("economyClass").toInt(),query.value("businessClass").toInt(),query.value("firstClass").toInt(),query.value("economyPrice").toInt(),query.value("businessPrice").toInt(),query.value("firstPrice").toInt());
                firstchosen.push_back(*f);
            }
        }
        for(int i=0;i<firstchosen.size();i++)
        {
            chosen.push_back(firstchosen[i]);
        }


    } else {
        qDebug() << "查询失败：" ;
    }
    if(ui->chose->currentText()=="发时最早")
    {
        std::sort(chosen.begin(), chosen.end(), comparestartTime);
    }
    else if(ui->chose->currentText()=="用时最短")
    {
        std::sort(chosen.begin(),chosen.end(),comparecostTime);
    }
    else if(ui->chose->currentText()=="价格最低")
    {
        std::sort(chosen.begin(),chosen.end(),comparePrice);
    }
    if(chosen.size() == 0||firstchosen.size()==0)
    {
        QWidget *Widget_2 = new QWidget();
        QVBoxLayout *Layout_2 = new QVBoxLayout(Widget_2);
        QLabel *notion_2 = new QLabel("未找到符合条件的机票", Widget_2);
        notion_2->setAlignment(Qt::AlignCenter); // 设置标签居中对齐
        Layout_2->addWidget(notion_2); // 将标签添加到布局中
        vLayout->addWidget(Widget_2); // 将包含标签的 Widget 添加到滚动区域的布局中
    }
    for(int i=0;i<chosen.size();i++)
    {
        qDebug()<<"找到机票"<<chosen[i].startport<<chosen[i].endport;
        QWidget *infoWidget = new QWidget();
        infoWidget->setFixedSize(470,120);
        QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
        QFont font("Arial", 18, QFont::Bold);


        QLabel *startportlabel = new QLabel(chosen[i].startport, infoWidget);
        // startportlabel->setFont(font);
        startportlabel->setMinimumSize(150, 30);
        startportlabel->move(25,50);

        QLabel *endportlabel = new QLabel(chosen[i].endport, infoWidget);
        // endportlabel->setFont(font);
        endportlabel->setMinimumSize(150, 30);
        endportlabel->move(280,50);

        QString id = chosen[i].id;
        QString company=chosen[i].company;

        QLabel *flight_id=new QLabel(company+id,infoWidget);
        flight_id->setMinimumSize(300,50);
        QPalette palette = flight_id->palette();
        palette.setColor(QPalette::WindowText, qRgb(178,178,178)); // 红色
        flight_id->setPalette(palette);
        flight_id->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        flight_id->move(10,70);

        QString startTimeStr = chosen[i].starttime; // 假设这是从数据库中获取的时间字符串
        QStringList parts = startTimeStr.split(' ');
        QString timePart = parts.size() >= 2 ? parts[1] : QString();

        QString endTimeStr = chosen[i].endtime; // 假设这是从数据库中获取的时间字符串
        QStringList endparts = endTimeStr.split(' ');
        QString endTimePart = endparts.size() >= 2 ? endparts[1] : QString();

        QLabel *starttimelabel = new QLabel(timePart, infoWidget);
        starttimelabel->setFont(font);
        starttimelabel->setMinimumSize(150, 50);
        starttimelabel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        starttimelabel->move(30,10);
        QLabel *endtimelabel = new QLabel(endTimePart, infoWidget);
        endtimelabel->setFont(font);
        endtimelabel->setMinimumSize(150, 50);
        endtimelabel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        endtimelabel->move(280,10);

        if(!chosen[i].stopcity.isEmpty())
        {
            QFont font4("Arial", 10);
            QLabel *stop = new QLabel("中转"+chosen[i].stopcity,infoWidget);
            stop->setPalette(palette);
            stop->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

            stop->setFont(font4);
            stop->move(185,40);
        }

        QFont font1("Arial", 12, QFont::Bold);

        QLabel * d1 = new QLabel("——✈——",infoWidget);
        d1->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        d1->setFont(font1);
        QPalette pal3 = d1->palette();
        pal3.setColor(QPalette::WindowText, qRgb(85,170,255));
        d1->setPalette(palette);
        d1->setMinimumSize(100,10);
        d1->move(173,25);

        QLabel * costtime = new QLabel(chosen[i].costTime(),infoWidget);
        costtime->setPalette(palette);
        costtime->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

        costtime->move(185,10);

        QPushButton * detailbutton = new QPushButton("查看详情",infoWidget);
        detailbutton->setStyleSheet("QPushButton { background-color:rgba(0, 0, 0, 0); color: rgb(85, 170, 255);}");
        connect(detailbutton, &QPushButton::clicked, this, [this, chosen, i]() {
            QString flightId = chosen[i].id;
            QString cabinClass = "经济舱";
            const flight& selectedFlight = chosen[i];
            this->onShowDetailButtonClickedSlot( selectedFlight);
        });
        detailbutton->move(370,80);


        QLabel picture(infoWidget);
        picture.setPixmap(QPixmap("path/to/your/image.png")); // 确保路径正确

        infoWidget->setStyleSheet(
            "QWidget {"
            "    background-color: white;"

            "    border-radius: 15px;" // 设置圆角大小
            "}"
            );
        // 将信息 widget 添加到垂直布局中
        vLayout->addWidget(infoWidget);
    }

    // 将布局设置到滚动区域的窗口内容
    vLayout->addStretch(1);
    scroller->widget()->setLayout(vLayout);
}


void checkWindow::deletticket(QScrollArea *scroller)
{
    QWidget *scrollAreaWidgetContents = scroller->widget();
    if (scrollAreaWidgetContents->layout()) {
        // 删除布局中的所有控件
        QLayoutItem *child;
        while ((child = scrollAreaWidgetContents->layout()->takeAt(0)) != nullptr) {
            if (child->widget() != nullptr) {
                child->widget()->deleteLater(); // 删除控件
            }
            delete child; // 删除布局项
        }
        delete scrollAreaWidgetContents->layout();

        // 注意：不要删除 scrollAreaWidgetContents
    }
    if (scrollAreaWidgetContents->layout() == nullptr) {
        qDebug() << "Layout has been successfully deleted.";
    } else {
        qDebug() << "Error: Layout still exists after deletion.";
    }

}
void checkWindow:: showflight()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM flight_info")) {
    } else {
        qDebug() << "查询失败：" ;
    }
}
checkWindow::checkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::checkWindow)
{
    ui->setupUi(this);
    connect(ui->BackButton,&QPushButton::clicked,this,&checkWindow::close);
    QDate today = QDate::currentDate();
    ui->date_2->setMinimumDate(today);
    ui->dateEdit->setMinimumDate(today);
    ui->dateEdit_2->setMinimumDate(today);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &checkWindow::onDepartureDateChanged);
    ui->stackedWidget->addWidget(ui->page_2);
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    if(Buysignal==1)
    {
        qDebug()<<"显示提示";
        QLabel* sign=new QLabel("请重新选择机票",this);
        sign->setMinimumSize(600,40);
        QFont font = sign->font();
        font.setPointSize(15);
        sign->setFont(font);
        sign->setStyleSheet("color: red");
        sign->move(430,40);
    }

    addFlightInfoToLayout();
    setstartcity();
    foreach (const QString &city, startcity) {
        ui->fromplace->addItem(city);
        ui->city1->addItem(city);
        ui->city2->addItem(city);
        // ui->fromWhere_2->addItem(city);
    }
    setendcity();
    foreach (const QString &city, endcity) {
        ui->toplace->addItem(city);
        // ui->toWhere_2->addItem(city);
    }
    setstopcity();
    foreach (const QString &city, stopcity) {
        ui->stopplace->addItem(city);
        // ui->toWhere_2->addItem(city);
    }
    qDebug() << "Number of cities fetched:" << stopcity.size();
    // 显示 comboBox
    qDebug()<<"录入城市";
    // ui->fromWhere->show();
    showflight();
    if(fromhomepage==1)
    {
        qDebug()<<"fromhomepage==1";
        qDebug()<<flightfrompage.id<<"this is id";
        qDebug()<<flightfrompage.startcity<<"this is city";
        QString starttime=flightfrompage.starttime;
        QStringList parts = starttime.split(' ');
        QString datePart = parts.size()>=2?parts[0]:QString();

        ui->fromplace->setCurrentText(flightfrompage.startcity);
        ui->toplace->setCurrentText(flightfrompage.endcity);
        QDateTime time1=QDateTime::fromString(flightfrompage.starttime,"yyyy-MM-dd HH:mm:ss");
        ui->date_2->setDateTime(time1);
        maketicket(flightfrompage.startcity,flightfrompage.stopcity,flightfrompage.endcity,datePart,ui->scrollArea);
        fromhomepage=0;
    }

}


checkWindow::~checkWindow()
{
    delete ui;
}

void checkWindow::on_BackButton_clicked()
{

}
void checkWindow::on_TicketButton_clicked()
{
    // stackedWidget->setCurrentWidget(TicketPage);
    // ui->stackedWidget_2->setCurrentWidget(ui->page);
}



int counts=0;

void checkWindow::addFlightInfoToLayout()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT * FROM flight_info")) {
        while (query.next()) {
            flight * f=new flight(query.value("flight_id").toString(),query.value("startCity").toString(),query.value("stopCity").toString(),query.value("endCity").toString(),query.value("startTime").toString(),query.value("endTime").toString(),query.value("flight_company").toString(),query.value("startport").toString(),query.value("stopport").toString(),query.value("endport").toString(),query.value("economyClass").toInt(),query.value("businessClass").toInt(),query.value("firstClass").toInt(),query.value("economyPrice").toInt(),query.value("businessPrice").toInt(),query.value("firstPrice").toInt());
            fl.push_back(*f);
        }
        qDebug()<<fl.size();
    } else {
        qDebug() << "查询失败：" ;
    }
}

void checkWindow::on_checkButton_clicked()
{
    QString from=ui->fromplace->currentText();
    QString stop=ui->stopplace->currentText();
    QString to=ui->toplace->currentText();
    QDate goDate = ui->date_2->date();

    // 将QDate转换为QString，格式为"YYYY-MM-DD"
    QString godate = goDate.toString("yyyy-MM-dd");
    deletticket(ui->scrollArea);
    maketicket(from,stop,to,godate,ui->scrollArea);
}

void checkWindow::onBuyButtonClickedSlot(QString m_flightId, QString m_cabinClass, flight m_selectFlight) {
    ticket tic;
    tic.Class = m_cabinClass;
    if (Buysignal == 1) {
        QSqlQuery queryUpdate;
        queryUpdate.exec("USE flight");

        // // 步骤1: 查询ticket表，统计购买这张票的人数
        // QSqlQuery countQuery;
        // countQuery.exec("USE flight");
        // countQuery.prepare("SELECT COUNT(*) FROM ticket WHERE ticketnum = :ticketnum AND id = :id");
        // countQuery.bindValue(":ticketnum", num);
        // countQuery.bindValue(":id", pa.getid());

        // if (countQuery.exec() && countQuery.next()) {
        //     int mainPassengerCount = countQuery.value(0).toInt(); // 买票人本人的数量

        //     QSqlQuery otherPassengersQuery;
        //     otherPassengersQuery.exec("USE flight");
        //     otherPassengersQuery.prepare("SELECT COUNT(*) FROM ticket WHERE ticketnum = :ticketnum AND (pa_id IS NOT NULL AND pa_id <> '') AND id = :id");
        //     otherPassengersQuery.bindValue(":ticketnum", num);
        //     otherPassengersQuery.bindValue(":id", pa.getid());

        //     if (otherPassengersQuery.exec() && otherPassengersQuery.next()) {
        //         int otherPassengersCount = otherPassengersQuery.value(0).toInt(); // 其他乘机人的数量
        //         int totalPassengers = mainPassengerCount + otherPassengersCount; // 总乘客数
        // 计算购票人本人和所有其他乘客的总数
        QSqlQuery query;
        query.exec("USE flight");

        // 查询 ticket 表以获取 flight_id
        query.prepare("SELECT flight_id, class, pa_id FROM ticket WHERE ticketnum = :ticketnum");
        query.bindValue(":ticketnum", num);
        int totalPassengers = 1; // 总乘客数
        //int economyCount = 0, businessCount = 0, firstCount = 0; // 各舱位乘客数
        if (query.exec()) {
            while (query.next()) {
                QString classType = query.value(1).toString();
                QString pa_id = query.value(2).toString();
                totalPassengers += !pa_id.isEmpty() ? 1 : 0; // 增加乘客数
                qDebug()<<"totalnumber="<<totalPassengers;
            }
        } else {
            qDebug() << "查询 ticket 失败: " << query.lastError().text();
            return;
        }

                // 步骤2: 更新flight_info表，增加原来航班的舱位数量
                QSqlQuery updateQueryOld;
                updateQueryOld.exec("USE flight");
                updateQueryOld.prepare("SELECT flight_id, class FROM ticket WHERE ticketnum = :ticketnum AND id = :id");
                updateQueryOld.bindValue(":ticketnum", num);
                updateQueryOld.bindValue(":id", pa.getid());
                if (updateQueryOld.exec() && updateQueryOld.next()) {
                    QString oldFlightId = updateQueryOld.value(0).toString();
                    qDebug()<<oldFlightId;
                    QString updateFieldOld = m_cabinClass == "经济舱" ? "economyClass" :
                                                 m_cabinClass == "商务舱" ? "businessClass" : "firstClass";
                    QString updateQueryOldStr = QString("UPDATE flight_info SET %1 = %1 + :totalPassengers WHERE flight_id = :oldFlightId").arg(updateFieldOld);
                    updateQueryOld.prepare(updateQueryOldStr);
                    updateQueryOld.bindValue(":totalPassengers", totalPassengers);
                    updateQueryOld.bindValue(":oldFlightId", oldFlightId);
                    if (!updateQueryOld.exec()) {
                        qDebug() << "增加原来航班舱位数量失败: " << updateQueryOld.lastError().text();
                        return;
                    }
                }

                // 更新flight_info表，减少新航班的舱位数量
                QSqlQuery updateQueryNew;
                updateQueryNew.exec("USE flight");
                updateQueryNew.prepare("SELECT class FROM ticket WHERE ticketnum = :ticketnum AND id = :id");
                updateQueryNew.bindValue(":ticketnum", num);
                updateQueryNew.bindValue(":id", pa.getid());
                if (updateQueryNew.exec() && updateQueryNew.next()) {
                    QString updateFieldNew = m_cabinClass == "经济舱" ? "economyClass" :
                                                 m_cabinClass == "商务舱" ? "businessClass" : "firstClass";
                    QString updateQueryNewStr = QString("UPDATE flight_info SET %1 = %1 - :totalPassengers WHERE flight_id = :newFlightId").arg(updateFieldNew);
                    updateQueryNew.prepare(updateQueryNewStr);
                    updateQueryNew.bindValue(":totalPassengers", totalPassengers);
                    updateQueryNew.bindValue(":newFlightId", m_flightId);
                    qDebug()<<m_flightId;
                    if (!updateQueryNew.exec()) {
                        qDebug() << "减少改签航班舱位数量失败: " << updateQueryNew.lastError().text();
                        return;
                    }
                }

                // 更新票信息
                queryUpdate.exec("USE flight");
                queryUpdate.prepare("UPDATE ticket SET flight_id = :newFlightId, class = :newClass WHERE ticketnum = :oldTicketNum AND id = :id");
                queryUpdate.bindValue(":newFlightId", m_flightId);
                queryUpdate.bindValue(":newClass", m_cabinClass);
                queryUpdate.bindValue(":oldTicketNum", num);
                queryUpdate.bindValue(":id", pa.getid());
                if (!queryUpdate.exec()) {
                    qDebug() << "改签更新失败: " << queryUpdate.lastError().text();
                    return;
                } else {
                    qDebug() << "改签更新成功";
                    QMessageBox::information(this, "改签成功", "您的座位号与原来相同。\n差价问题无需担心，我们会为您处理。");
                }
                Buysignal = 0;
                return;
            }
//        }
//    }

    QString randomNumberString;
    for (int i = 0; i < 11; ++i) {
        int digit = QRandomGenerator::global()->bounded(0, 10); // 生成 0 到 9 的随机数
        randomNumberString += QString::number(digit);
    }
    tic.ticketnumber = randomNumberString;
    tic.boughtmess = m_selectFlight;
    pa.bought_ticket.push_back(tic);

    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("INSERT INTO ticket (ticketnum, id, flight_id, class, status) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(randomNumberString);  // 票号
    query.addBindValue(pa.getid());         // 乘客ID
    query.addBindValue(m_flightId);         // 航班ID
    query.addBindValue(tic.Class);          // 舱位
    query.addBindValue(0);

    if (!query.exec()) {
        qDebug() << "插入数据失败: " << query.lastError().text();
    } else {
        qDebug() << "插入数据成功!";
    }

    PlaceOrder* po = new PlaceOrder(nullptr, randomNumberString);
    po->show();
}

void checkWindow::onShowDetailButtonClickedSlot(flight m_selectFlight)
{
    // QMessageBox msgBox;

    // msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    // msgBox.setDefaultButton(QMessageBox::Yes);
    // int ret = msgBox.exec();

    // ...（其余代码不变）
    // ...

    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setText("机票详情"); // 设置主消息
    msgBox.setInformativeText("航空公司：" + m_selectFlight.company + "\n"
                              "航班号："+m_selectFlight.id+"\n"
                              "出发地城市：" + m_selectFlight.startcity + "\n"
                              "出发站台："+m_selectFlight.startport+"\n"
                              "出发时间："+m_selectFlight.starttime+"\n"
                              "中转地城市："+m_selectFlight.stopcity+"\n"
                              "中转站台："+m_selectFlight.stopport+"\n"
                              "目的地城市：" + m_selectFlight.endcity+"\n"
                              "到达站台："+m_selectFlight.endport+"\n"
                              "到达时间："+m_selectFlight.endtime+"\n"
                              "经济舱：余"+QString::number(m_selectFlight.eco)+"\t"+"￥"+QString::number(m_selectFlight.ecoprice)+"\n"
                              "商务舱：余"+QString::number(m_selectFlight.bus)+"\t"+"￥"+QString::number(m_selectFlight.busprice)+"\n"
                              "头等舱：余"+QString::number(m_selectFlight.fir)+"\t"+"￥"+QString::number(m_selectFlight.firprice)+"\n"
                              );

    // 创建自定义按钮
    QPushButton *economyButton = msgBox.addButton("购买经济舱", QMessageBox::ActionRole);
    QPushButton *businessButton = msgBox.addButton("购买商务舱", QMessageBox::ActionRole);
    QPushButton *firstClassButton = msgBox.addButton("购买头等舱", QMessageBox::RejectRole); // 假设"取消"是"购买头等舱"的替代

    // 连接按钮的信号到槽函数
    QObject::connect(economyButton, &QPushButton::clicked, this, [this, m_selectFlight]() {
        onBuyButtonClickedSlot(m_selectFlight.id, "经济舱", m_selectFlight);
    });

    QObject::connect(businessButton, &QPushButton::clicked, this, [this, m_selectFlight]() {
        onBuyButtonClickedSlot(m_selectFlight.id, "商务舱", m_selectFlight);
    });

    QObject::connect(firstClassButton, &QPushButton::clicked, this, [this, m_selectFlight]() {
        onBuyButtonClickedSlot(m_selectFlight.id, "头等舱", m_selectFlight);
    });

    // 显示消息框并等待用户响应
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
        // 用户选择了购买经济舱
        break;
    case QMessageBox::No:
        // 用户选择了购买商务舱
        break;
    case QMessageBox::Cancel:
        // 用户选择了购买头等舱或取消
        break;
    }

}
void checkWindow::on_sigle_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void checkWindow::on_goandback_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void checkWindow::on_pushButton_clicked()
{
    QString startcity=ui->city1->currentText();
    QString endcity=ui->city2->currentText();
    QDate date1=ui->dateEdit->date();
    QDate date2=ui->dateEdit_2->date();
    QString godate = date1.toString("yyyy-MM-dd");
    QString backdate=date2.toString("yyyy-MM-dd");
    deletticket(ui->scrollArea_2);
    deletticket(ui->scrollArea_3);
    makesmallticket(startcity,"",endcity,godate,ui->scrollArea_2);
    makesmallticket(endcity,"",startcity,backdate,ui->scrollArea_3);
}

void checkWindow::onDepartureDateChanged(const QDate &date)
{
    ui->dateEdit_2->setMinimumDate(date);
}
