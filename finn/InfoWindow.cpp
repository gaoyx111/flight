#include "InfoWindow.h"
#include "detail.h"
#include "qtimer.h"
#include "ui_InfoWindow.h"
#include<loginwindow.h>
#include <QMessageBox>
#include<QSqlError>
#include<ticket.h>
#include<checkWindow.h>
extern passenger pa;
extern QString num;
extern int Cancelsignal;
extern int Buysignal;

void InfoWindow::showboughtticket(QScrollArea *scroller)
{
    deletticket(scroller);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(20);
#include <QMap>
#include <QDateTime>

    QVector<ticket> chosen;
    QVector<ticket> temp;
    QSqlQuery query;
    query.exec("USE flight");

    QString sql = "SELECT t.ticketnum, t.class, t.status, "
                  "f.flight_id, f.flight_company, f.startCity, f.stopCity, f.endCity, f.startport, f.stopport, f.endport, f.startTime, f.endTime, "
                  "f.economyClass, f.businessClass, f.firstClass, f.economyPrice, f.businessPrice, f.firstPrice "
                  "FROM ticket t "
                  "INNER JOIN flight_info f ON t.flight_id = f.flight_id "
                  "WHERE t.id = :id";

    query.prepare(sql);
    query.bindValue(":id", pa.getid());
    QDateTime today = QDateTime::currentDateTime();

    QMap<QString, ticket> ticketsMap; // 使用QMap来存储ticketnumber和对应的ticket对象

    if (query.exec()) {
        if (scroller == ui->scrollArea) {
            while (query.next()) {
                ticket tic;

                tic.ticketnumber = query.value("ticketnum").toString();
                tic.Class = query.value("class").toString();
                tic.status = query.value("status").toInt();

                flight *f = new flight(
                    query.value("flight_id").toString(),
                    query.value("startCity").toString(),
                    query.value("stopCity").toString(),
                    query.value("endCity").toString(),
                    query.value("startTime").toString(),
                    query.value("endTime").toString(),
                    query.value("flight_company").toString(),
                    query.value("startport").toString(),
                    query.value("stopport").toString(),
                    query.value("endport").toString(),
                    query.value("economyClass").toInt(),
                    query.value("businessClass").toInt(),
                    query.value("firstClass").toInt(),
                    query.value("economyPrice").toInt(),
                    query.value("businessPrice").toInt(),
                    query.value("firstPrice").toInt()
                    );
                tic.boughtmess = *f;
                tic.boughtmess.starttime = query.value("startTime").toString();
                QDateTime time = QDateTime::fromString(tic.boughtmess.starttime, "yyyy-MM-dd HH:mm:ss");

                // 使用ticketnumber作为key检查是否已经存在
                if (!ticketsMap.contains(tic.ticketnumber)) {
                    ticketsMap.insert(tic.ticketnumber, tic);
                    if (time < today) {
                        temp.push_back(tic); // 过期的
                    } else {
                        chosen.push_back(tic);
                        qDebug() << "放进的未过期票的出发时间" << tic.boughtmess.starttime;
                    }
                }
            }
            std::reverse(chosen.begin(), chosen.end());
            std::reverse(temp.begin(), temp.end());
            for (int i = 0; i < temp.size(); i++) {
                chosen.push_back(temp[i]);
            }
        } else if (scroller == ui->scrollArea_3) {
            while (query.next()) {
                ticket tic;

                tic.ticketnumber = query.value("ticketnum").toString();
                tic.Class = query.value("class").toString();
                tic.status = query.value("status").toInt();
                if (tic.status == 1) {
                    flight *f = new flight(
                        query.value("flight_id").toString(),
                        query.value("startCity").toString(),
                        query.value("stopCity").toString(),
                        query.value("endCity").toString(),
                        query.value("startTime").toString(),
                        query.value("endTime").toString(),
                        query.value("flight_company").toString(),
                        query.value("startport").toString(),
                        query.value("stopport").toString(),
                        query.value("endport").toString(),
                        query.value("economyClass").toInt(),
                        query.value("businessClass").toInt(),
                        query.value("firstClass").toInt(),
                        query.value("economyPrice").toInt(),
                        query.value("businessPrice").toInt(),
                        query.value("firstPrice").toInt()
                        );
                    tic.boughtmess = *f;
                    tic.boughtmess.starttime = query.value("startTime").toString();
                    QDateTime time = QDateTime::fromString(tic.boughtmess.starttime, "yyyy-MM-dd HH:mm:ss");

                    if (!ticketsMap.contains(tic.ticketnumber) && time > today) {
                        ticketsMap.insert(tic.ticketnumber, tic);
                        chosen.push_back(tic);
                    }
                }
            }
            std::reverse(chosen.begin(), chosen.end());
        } else if (scroller == ui->scrollArea_4) {
            qDebug() << "33333";
            while (query.next()) {
                ticket tic;

                tic.ticketnumber = query.value("ticketnum").toString();
                tic.Class = query.value("class").toString();
                tic.status = query.value("status").toInt();
                if (tic.status == 0) {
                    flight *f = new flight(
                        query.value("flight_id").toString(),
                        query.value("startCity").toString(),
                        query.value("stopCity").toString(),
                        query.value("endCity").toString(),
                        query.value("startTime").toString(),
                        query.value("endTime").toString(),
                        query.value("flight_company").toString(),
                        query.value("startport").toString(),
                        query.value("stopport").toString(),
                        query.value("endport").toString(),
                        query.value("economyClass").toInt(),
                        query.value("businessClass").toInt(),
                        query.value("firstClass").toInt(),
                        query.value("economyPrice").toInt(),
                        query.value("businessPrice").toInt(),
                        query.value("firstPrice").toInt()
                        );
                    tic.boughtmess = *f;
                    tic.boughtmess.starttime = query.value("startTime").toString();
                    QDateTime time = QDateTime::fromString(tic.boughtmess.starttime, "yyyy-MM-dd HH:mm:ss");

                    if (!ticketsMap.contains(tic.ticketnumber) && time > today) {
                        ticketsMap.insert(tic.ticketnumber, tic);
                        chosen.push_back(tic);
                    }
                }
            }
            std::reverse(chosen.begin(), chosen.end());
        } else if (scroller == ui->scrollArea_5) {
            qDebug() << "11111";
            while (query.next()) {
                ticket tic;

                tic.ticketnumber = query.value("ticketnum").toString();
                tic.Class = query.value("class").toString();
                tic.status = query.value("status").toInt();
                tic.boughtmess.starttime = query.value("startTime").toString();
                QDateTime time = QDateTime::fromString(tic.boughtmess.starttime, "yyyy-MM-dd HH:mm:ss");

                if (!ticketsMap.contains(tic.ticketnumber) && time < today) {
                    flight *f = new flight(
                        query.value("flight_id").toString(),
                        query.value("startCity").toString(),
                        query.value("stopCity").toString(),
                        query.value("endCity").toString(),
                        query.value("startTime").toString(),
                        query.value("endTime").toString(),
                        query.value("flight_company").toString(),
                        query.value("startport").toString(),
                        query.value("stopport").toString(),
                        query.value("endport").toString(),
                        query.value("economyClass").toInt(),
                        query.value("businessClass").toInt(),
                        query.value("firstClass").toInt(),
                        query.value("economyPrice").toInt(),
                        query.value("businessPrice").toInt(),
                        query.value("firstPrice").toInt()
                        );
                    tic.boughtmess = *f;
                    chosen.push_back(tic);
                }
            }
            std::reverse(chosen.begin(), chosen.end());
        }
    }
    if(chosen.size()==0)
    {
        qDebug()<<"未购买机票";
    }


    for(int i=0;i<chosen.size();i++)
    {
        QFont font("Arial", 20, QFont::Bold);
        qDebug()<<"已买机票"<<chosen[i].ticketnumber;
        QWidget *infoWidget = new QWidget();
        QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
        infoWidget->setFixedSize(570,155);
        QString id = chosen[i].boughtmess.id;
        QString company=chosen[i].boughtmess.company;
        QString logo="✈";
        QString depart="|";
        QString Class=chosen[i].Class;
        QLabel *flight_id=new QLabel(logo+company+id+depart+Class,infoWidget);
        flight_id->setMinimumSize(500,50);
        QPalette palette = flight_id->palette();
        palette.setColor(QPalette::WindowText, qRgb(178,178,178));
        flight_id->setPalette(palette);
        flight_id->move(10,2);


        QLabel *starttimelabel=new QLabel(chosen[i].boughtmess.starttime,infoWidget);
        QPalette pal = starttimelabel->palette();
        pal.setColor(QPalette::WindowText, qRgb(85, 170, 255));
        starttimelabel->setPalette(pal);
        starttimelabel->setMinimumSize(200,30);
        starttimelabel->move(10,40);
        QLabel *endtimelabel=new QLabel(chosen[i].boughtmess.endtime,infoWidget);
        endtimelabel->setMinimumSize(200,30);
        endtimelabel->setPalette(pal);
        endtimelabel->move(250,40);

        QLabel *startcitylabel = new QLabel(chosen[i].boughtmess.startcity,infoWidget);
        QLabel *endcitylael = new QLabel(chosen[i].boughtmess.endcity,infoWidget);
        startcitylabel->setFont(font);
        endcitylael->setFont(font);
        startcitylabel->move(30,75);
        endcitylael->move(300,75);

        QLabel *startportlabel = new QLabel(chosen[i].boughtmess.startport,infoWidget);
        QLabel *endportlabel= new QLabel(chosen[i].boughtmess.endport,infoWidget);
        startportlabel->setMinimumSize(200,30);
        endportlabel->setMinimumSize(200,30);
        startportlabel->move(10,110);
        endportlabel->move(275,110);

        QFont font1("Arial", 15);
        QLabel * link = new QLabel("> > > > >",infoWidget);
        link->setFont(font1);
        link->setPalette(pal);
        link->move(160,90);

        QLabel * costtime = new QLabel(chosen[i].boughtmess.costTime(),infoWidget);
        costtime->setPalette(palette);
        costtime->move(170,65);

        QFont font2("Arial", 20, QFont::Bold);

        // QString ticketnum=chosen[i].ticketnumber;
        // QLabel * ticnumlabel = new QLabel("订单号："+ticketnum,infoWidget);
        // QPalette pal2 = ticnumlabel->palette();
        // pal2.setColor(QPalette::WindowText, qRgb(255,170,127));
        // ticnumlabel->setPalette(pal2);
        // ticnumlabel->setMinimumSize(500,30);
        // ticnumlabel->move(10,160);
        double price=0;
        QSqlQuery query;
        query.exec("USE flight");

        // 查询 ticket 表以获取 flight_id
        query.prepare("SELECT flight_id, class, pa_id FROM ticket WHERE ticketnum = :ticketnum");
        query.bindValue(":ticketnum", chosen[i].ticketnumber);
        int totalPassengers = 1; // 总乘客数
        int economyCount = 0, businessCount = 0, firstCount = 0; // 各舱位乘客数
        if (query.exec()) {
            while (query.next()) {
                QString classType = query.value(1).toString();
                QString pa_id = query.value(2).toString();
                totalPassengers += !pa_id.isEmpty() ? 1 : 0; // 增加乘客数
                qDebug()<<"totalnumber="<<totalPassengers;
                // 根据舱位类型计数
                // if (classType == "经济舱") {
                //     economyCount++;
                // } else if (classType == "商务舱") {
                //     businessCount++;
                // } else if (classType == "头等舱") {
                //     firstCount++;
                // }
            }
        } else {
            qDebug() << "查询 ticket 失败: " << query.lastError().text();
            return;
        }
        if(chosen[i].Class=="经济舱")
        {
            price+=chosen[i].boughtmess.ecoprice*totalPassengers;
        }
        else if(chosen[i].Class=="商务舱")
        {
            price+=chosen[i].boughtmess.busprice*totalPassengers;
        }
        else if(chosen[i].Class=="头等舱")
        {
            price+=chosen[i].boughtmess.firprice*totalPassengers;
        }
        // price += chosen[i].boughtmess.ecoprice * (economyCount);
        // price += chosen[i].boughtmess.busprice * (businessCount);
        // price += chosen[i].boughtmess.firprice * (firstCount);

        qDebug()<<"price="<<price;
        QLabel * pricelabel =new QLabel("\u00A5"+QString::number(price),infoWidget);
        pricelabel->setFont(font2);
        pricelabel->move(450,10);

        QDateTime time=QDateTime::fromString(chosen[i].boughtmess.starttime,"yyyy-MM-dd HH:mm:ss");
        if(time<today)
        {
            QPushButton * detail = new QPushButton("查看详情",infoWidget);
            QObject::connect(detail, &QPushButton::clicked, this, [this, chosen, i]() { ondetailButtonClicked(chosen[i].ticketnumber); });

            detail->setStyleSheet("QPushButton { "
                                  "background-color: rgb(178,178,178);  color: white;"
                                  "}");
            detail->move(430,80);
        }
        else{
        if(chosen[i].status==1){
        QPushButton *change = new QPushButton("改签", infoWidget);
        QObject::connect(change, &QPushButton::clicked, this, [this, chosen, i]() { onChangeButtonClicked(chosen[i].ticketnumber); });

        change->setMinimumSize(50,30);
        change->setStyleSheet("QPushButton { "
                              "background-color:  rgb(85, 170, 255); color: white;"
                              "border-radius: 10px;  "
                              "}");
        change->move(430,50);
        QPushButton * cancelticket=new QPushButton("退票",infoWidget);
        QObject::connect(cancelticket, &QPushButton::clicked, this, [this, chosen, i,scroller]() { onCancelButtonClicked(chosen[i].ticketnumber,scroller); });


        cancelticket->setMinimumSize(50,30);

        cancelticket->setStyleSheet("QPushButton { "
                                    "background-color:  rgb(85, 170, 255); color: white;"
                                    "border-radius: 10px;  "
                                    "}");
        cancelticket->move(430,90);
        }
        else if(chosen[i].status==0)
        {
            QPushButton *pay = new QPushButton("支付", infoWidget);
            QObject::connect(pay, &QPushButton::clicked, this, [this, chosen, i]() { onPayButtonClicked(chosen[i].ticketnumber); });
            // connect(change, &QPushButton::clicked, this, &InfoWindow::showCheckWindow);
            pay->setMinimumSize(50,30);
            pay->setStyleSheet("QPushButton { "
                                  "background-color:  rgb(85, 170, 255); color: white;"
                                  "border-radius: 10px;  "
                                  "}");
            pay->move(430,50);
            QPushButton * cancelticket=new QPushButton("取消订单",infoWidget);
            QObject::connect(cancelticket, &QPushButton::clicked, this, [this, chosen, i,scroller]() { onCancelButtonClicked(chosen[i].ticketnumber,scroller); });

            cancelticket->setMinimumSize(50,30);

            cancelticket->setStyleSheet("QPushButton { "
                                        "background-color:  rgb(85, 170, 255); color: white;"
                                        "border-radius: 10px;  "
                                        "}");
            cancelticket->move(430,90);
        }

        QPushButton * detail = new QPushButton("查看详情",infoWidget);
        QObject::connect(detail, &QPushButton::clicked, this, [this, chosen, i]() { ondetailButtonClicked(chosen[i].ticketnumber); });

        detail->setStyleSheet("QPushButton { "
                              "background-color: white;  color: rgb(85, 170, 255);"
                              "}");
        detail->move(430,125);
        }
        infoWidget->setStyleSheet(
            "QWidget {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "                                stop:0 rgba(85, 170, 255, 128),"
            "                                stop:0.5 rgba(85, 170, 255, 0));"
            "    background-color: white;"
            "    border-radius: 15px;"
            "}"
            );
        vLayout->addWidget(infoWidget);

    }
    vLayout->addStretch(1);
    scroller->widget()->setLayout(vLayout);
}



InfoWindow::InfoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    connect(ui->BackButton,&QPushButton::clicked,this,&InfoWindow::close);
    pa.show();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;
    }
    QString passengerId = pa.getid();
    QSqlQuery query(db);
    query.exec("USE flight");
    query.prepare("SELECT passenger_biethday FROM passenger WHERE passenger_id = :id");
    query.bindValue(":id", passengerId);
    if (!query.exec()) {
        qDebug() << "查询失败：" << query.lastError().text();
        return;
    }
    if (query.next()) {
        QString birthday = query.value(0).toString();
        ui->birthday_2->setText(birthday);
    } else {
        qDebug() << "未找到该用户的生日信息";
    }
    ui->name_15->setText(pa.getname());
    ui->newname->setText(pa.getname());
    ui->telenumber_3->setText(pa.getid());
    ui->newphone->setText(pa.getid());
    ui->cn_15->setText(pa.getnickname());
    ui->newnickname->setText(pa.getnickname());

    stackedWidget = ui->stackedWidget;

    personInfoPage = ui->stackedWidget->widget(1);
    orderPage = ui->stackedWidget->widget(0);
    couponPage = ui->stackedWidget->widget(2);
    travelerInfoPage = ui->stackedWidget->widget(3);
    infoPage=ui->stackedWidget->widget(4);

    stackedWidget->addWidget(personInfoPage);
    stackedWidget->addWidget(orderPage);
    stackedWidget->addWidget(couponPage);
    stackedWidget->addWidget(travelerInfoPage);
    stackedWidget->addWidget(infoPage);

    stackedWidget->setCurrentWidget(couponPage);

    connect(ui->PersonInfoButton, &QPushButton::clicked, this, &InfoWindow::on_PersonInfo_clicked);
    connect(ui->OrderButton, &QPushButton::clicked, this, &InfoWindow::on_order_clicked);
    // connect(ui->CouponButton, &QPushButton::clicked, this, &InfoWindow::on_coupon_clicked);
    connect(ui->TravelerInfoButton, &QPushButton::clicked, this, &InfoWindow::on_TravelerInfo_clicked);

    connect(ui->allButton,&QPushButton::clicked,this,&InfoWindow::on_allbtn_clicked);
    connect(ui->waitforgoButton,&QPushButton::clicked,this,&InfoWindow::on_gobtn_clicked);
    connect(ui->waitforpayButton,&QPushButton::clicked,this,&InfoWindow::on_paybtn_clicked);
    connect(ui->finishButton,&QPushButton::clicked,this,&InfoWindow::on_finish_clicked);

}

InfoWindow::~InfoWindow()
{
    delete ui;
}

// 跳转到个人信息页面
void InfoWindow::on_PersonInfo_clicked()
{

    stackedWidget->setCurrentWidget(couponPage);  // 切换到个人信息页面
}

// 跳转到订单页面
void InfoWindow::on_order_clicked()
{
    stackedWidget->setCurrentWidget(orderPage);
    // showboughtticket();
    ui->stackedWidget_2->setCurrentWidget(ui->page);
    showboughtticket(ui->scrollArea);
}

// 跳转到优惠券页面
void InfoWindow::on_coupon_clicked()
{
    stackedWidget->setCurrentWidget(travelerInfoPage);  // 切换到优惠券页面
}

// 跳转到旅客信息页面info常用旅客
void InfoWindow::on_TravelerInfo_clicked()
{
    stackedWidget->setCurrentWidget(infoPage);  // 切换到旅客信息页面
    makepa();
}

void InfoWindow::on_allbtn_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page);
    showboughtticket(ui->scrollArea);
}

void InfoWindow::on_gobtn_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_2);
    showboughtticket(ui->scrollArea_3);
}

void InfoWindow::on_paybtn_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_3);
    showboughtticket(ui->scrollArea_4);
}

void InfoWindow::on_finish_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_4);
    showboughtticket(ui->scrollArea_5);
}

void InfoWindow::on_BackButton_clicked()
{
    emit returnToHome();
    this->close();
}


void InfoWindow::on_EditButton_9_clicked()
{
    stackedWidget->setCurrentWidget(personInfoPage);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;
    }
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("SELECT passenger_name, passenger_nickname, passenger_biethday FROM passenger WHERE passenger_id=:id");
    query.bindValue(":id", pa.getid());

    if (!query.exec()) {
        qDebug() << "查询失败：" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString name = query.value("passenger_name").toString();
        QString nickname = query.value("passenger_nickname").toString();
        QString birthday = query.value("passenger_biethday").toString();

        ui->newname->setText(name);
        ui->newnickname->setText(nickname);
        ui->newphone->setText(pa.getid());

        if (birthday.isEmpty()) {
            ui->dateEdit->setDate(QDate(2000, 1, 1));
        } else {
            ui->dateEdit->setDate(QDate::fromString(birthday, "yyyy-MM-dd"));
        }
    } else {
        qDebug() << "没有找到该用户数据";
    }
}



void InfoWindow::updatename(QString newname, QString newnick, QString newgender, QString bir, QString id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;
    }

    QString updateSql = "UPDATE passenger SET passenger_name=:newValue, passenger_nickname=:newval, passenger_biethday=:newb WHERE passenger_id=:id";
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare(updateSql);
    query.bindValue(":newValue", newname);
    query.bindValue(":newval", newnick);
    query.bindValue(":newb", bir);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "更新失败";
        QMessageBox::warning(this, "更新失败", "更新信息失败，请稍后重试。", QMessageBox::Ok);
    } else {
        qDebug() << "更新成功" << query.lastError().text();
        QMessageBox::information(this, "更新成功", "您的信息已成功更新。", QMessageBox::Ok);
    }

    // 更新控件文本
    ui->name_15->setText(newname);
    ui->newname->setText(newname);
    ui->telenumber_3->setText(id);
    ui->newphone->setText(id);
    ui->cn_15->setText(newnick);
    ui->newnickname->setText(newnick);
    ui->birthday_2->setText(bir);  // 设置生日

    // 更新性别单选框
    if (newgender == "男") {
        ui->male->setChecked(true);
    } else if (newgender == "女") {
        ui->female->setChecked(true);
    }
}

void InfoWindow::refreshCouponPage()
{
    ui->name_15->setText(ui->newname->text());
    ui->cn_15->setText(ui->newnickname->text());
    if (ui->male->isChecked()) {
        ui->sex_15->setText("男");
    } else if (ui->female->isChecked()) {
        ui->sex_15->setText("女");
    }
}

void InfoWindow::on_okbutton_clicked()
{
    QString name = ui->newname->text();
    QString nickname = ui->newnickname->text();
    QString gender;
    if (ui->male->isChecked()) {
        gender = "男";
        ui->sex_15->setText("男");
    } else if (ui->female->isChecked()) {
        gender = "女";
        ui->sex_15->setText("女");
    }

    QDate birthday = ui->dateEdit->date();
    QString birthdayString = birthday.toString("yyyy-MM-dd"); // 格式化日期为字符串
    //    qDebug() << birthdayString;
    QString id = pa.getid();
    ui->birthday_2->setText(birthdayString);

    updatename(name, nickname, gender, birthdayString, id);

    QTimer::singleShot(0, this, [=]() {
        refreshCouponPage();
        stackedWidget->setCurrentWidget(couponPage);
    });
}

void InfoWindow::makepa()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("USE flight");

    query.prepare("SELECT other_id, other_name FROM other_passenger where id=:id");
    query.bindValue(":id", pa.getid());

    // 获取 scrollArea_2 的滚动区域内容
    QWidget *scrollWidget = ui->scrollArea_2->widget();
    QVBoxLayout *vLayout = qobject_cast<QVBoxLayout*>(scrollWidget->layout());
    if (!vLayout) {
        vLayout = new QVBoxLayout();
        scrollWidget->setLayout(vLayout);
    }
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    // 执行查询
    if (query.exec()) {
        // 清空之前的内容
        QLayoutItem *child;
        while ((child = vLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // 逐个显示所有旅客信息
        while (query.next()) {
            QString otherid = query.value("other_id").toString();
            QString othername = query.value("other_name").toString();

            QWidget *infoWidget = new QWidget();
            QHBoxLayout *infoLayout = new QHBoxLayout(infoWidget);

            // 左侧布局
            QVBoxLayout *leftLayout = new QVBoxLayout();
            leftLayout->setSpacing(0);
            leftLayout->setContentsMargins(0, 0, 0, 0);

            // 电话号码行
            QLabel *idLabel = new QLabel("电话号码：", infoWidget);
            idLabel->setFont(QFont("Microsoft YaHei UI", 11, QFont::Bold));
            idLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(85, 170, 255);");

            QLabel *idValueLabel = new QLabel(otherid, infoWidget);
            idValueLabel->setFont(QFont("Microsoft YaHei UI", 9));
            idValueLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(0, 0, 0);");

            QHBoxLayout *idLayout = new QHBoxLayout();
            idLayout->addWidget(idLabel);
            idLayout->addWidget(idValueLabel);
            idLayout->setSpacing(0);
            idLayout->setContentsMargins(0, 0, 0, 0);

            // 姓名行
            QLabel *nameLabel = new QLabel("姓名", infoWidget);
            nameLabel->setFont(QFont("Microsoft YaHei UI", 12, QFont::Bold));
            nameLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(0, 0, 0);");

            QLabel *nameValueLabel = new QLabel(othername, infoWidget);
            nameValueLabel->setFont(QFont("Microsoft YaHei UI", 9));
            nameValueLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(0, 0, 0);");

            QHBoxLayout *nameLayout = new QHBoxLayout();
            nameLayout->addWidget(nameLabel);
            nameLayout->addWidget(nameValueLabel);
            nameLayout->setSpacing(0);
            nameLayout->setContentsMargins(0, 0, 0, 0);

            // 身份证行
            QLabel *idCardLabel = new QLabel("身份证：", infoWidget);
            idCardLabel->setFont(QFont("Microsoft YaHei UI", 11, QFont::Bold));
            idCardLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(85, 170, 255);");

            QLabel *idCardValueLabel = new QLabel("保密", infoWidget);
            idCardValueLabel->setFont(QFont("Microsoft YaHei UI", 9));
            idCardValueLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgb(0, 0, 0);");

            QHBoxLayout *idCardLayout = new QHBoxLayout();
            idCardLayout->addWidget(idCardLabel);
            idCardLayout->addWidget(idCardValueLabel);
            idCardLayout->setSpacing(0);
            idCardLayout->setContentsMargins(0, 0, 0, 0);

            leftLayout->addLayout(nameLayout);
            leftLayout->addLayout(idCardLayout);
            leftLayout->addLayout(idLayout);


            // 右侧布局（操作按钮）
            QVBoxLayout *rightLayout = new QVBoxLayout();

            QPushButton *modifyButton = new QPushButton("修改信息", infoWidget);
            modifyButton->setFont(QFont("Microsoft YaHei UI", 9));
            modifyButton->setStyleSheet("background-color: rgb(85, 170, 255); color: rgb(255, 255, 255); border-radius: 12px;");
            modifyButton->setFixedSize(100, 40);
            modifyButton->setProperty("other_id", otherid);
            modifyButton->setProperty("other_name", othername);
            rightLayout->addWidget(modifyButton);
            connect(modifyButton, &QPushButton::clicked, this, &InfoWindow::onModifyButtonClicked);

            QPushButton *deleteButton = new QPushButton("删除旅客", infoWidget);
            deleteButton->setFont(QFont("Microsoft YaHei UI", 9));
            deleteButton->setStyleSheet("background-color: rgb(85, 170, 255); color: rgb(255, 255, 255); border-radius: 12px;");
            deleteButton->setFixedSize(100, 40);
            deleteButton->setProperty("other_id", otherid);
            rightLayout->addWidget(deleteButton);
            connect(deleteButton, &QPushButton::clicked, this, &InfoWindow::onDeleteButtonClicked);

            // 设置左右布局之间的间距（确保按钮区域与信息区域间隔更大）
            infoLayout->addLayout(leftLayout);
            infoLayout->addSpacing(220); // 增加左右间距，分开信息部分和按钮部分
            infoLayout->addLayout(rightLayout);

            infoWidget->setFixedSize(550, 140);
            infoLayout->setContentsMargins(20, 10, 20, 10);

            infoWidget->setStyleSheet("QWidget { background-color: white; border-radius: 15px; margin: 5px; }");

            // 将信息显示的 QWidget 添加到滚动区域的布局中
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

    } else {
        qDebug() << "查询旅客信息失败";
    }
}


void InfoWindow::onModifyButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString otherid = button->property("other_id").toString();
    QString othername = button->property("other_name").toString();
    ui->idEdit->setReadOnly(true);
    ui->noneEdit->setReadOnly(true);
    ui->nameEdit->setText(othername);  // 姓名
    ui->idEdit->setText(otherid);   // 电话
    ui->noneEdit->setText("保密"); // 身份证号
    ui->nameEdit->setFocus();
}

void InfoWindow::deletePassenger(const QString &otherid) {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("USE flight");
    query.prepare("SELECT id FROM other_passenger WHERE other_id = :other_id");
    query.bindValue(":other_id", otherid);
    if (!query.exec()) {
        qDebug() << "查询失败：" << query.lastError().text();
        QMessageBox::critical(this, "查询失败", "无法查询旅客信息，请稍后再试。");
        return;
    }
    if (query.next()) {
        QString dbId = query.value("id").toString();
        if (dbId == pa.getid()) {
            query.prepare("DELETE FROM other_passenger WHERE other_id = :other_id");
            query.bindValue(":other_id", otherid);
            if (query.exec()) {
                qDebug() << "删除成功，旅客ID：" << otherid;
                makepa();
            } else {
                qDebug() << "删除失败：" << query.lastError().text();
                QMessageBox::critical(this, "删除失败", "删除旅客信息时发生错误，请稍后再试。");
            }
        } else {
            QMessageBox::warning(this, "删除失败", "数据库中的 id 与当前用户的 id 不匹配，无法删除该旅客信息。");
        }
    } else {
        QMessageBox::warning(this, "删除失败", "没有找到对应的旅客信息，无法删除。");
    }
}



void InfoWindow::onDeleteButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString otherid = button->property("other_id").toString();  // 从按钮中获取旅客ID
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除确认", "确定要删除此旅客信息吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        deletePassenger(otherid);
    }
}

void InfoWindow::on_cancelbtn_clicked()
{
    ui->nameEdit->setText("");  // 姓名
    ui->idEdit->setText("");   // 电话
    ui->noneEdit->setText(""); // 身份证号
}


void InfoWindow::on_changebtn_clicked()
{
    if(ui->nameEdit->text().trimmed()==""){
        ui->nameEdit->setFocus();
        ui->lbl_Note->setText("旅客姓名不能为空！");
        ui->lbl_Note->setStyleSheet("color:red");
        return;
    }
    else{
        QString other_id = ui->idEdit->text().trimmed(); // 获取 other_id
        QString new_name = ui->nameEdit->text().trimmed(); // 获取新的姓名

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        query.exec("USE flight");
        query.prepare("UPDATE other_passenger SET other_name = :new_name WHERE other_id = :other_id AND id = :user_id");
        query.bindValue(":new_name", new_name);
        query.bindValue(":other_id", other_id);
        query.bindValue(":user_id", pa.getid());

        if (!query.exec()) {
            qDebug() << "更新失败：" << query.lastError().text();
            QMessageBox::critical(this, "更新失败", "更新旅客信息失败，请稍后重试。");
        } else {
            QMessageBox::information(this, "更新成功", "旅客姓名已成功更新！");
            makepa();
        }
    }
}


void InfoWindow::on_addbtn_clicked()
{
    ui->idEdit->setReadOnly(false);
    ui->noneEdit->setReadOnly(false);
    if(ui->nameEdit->text().trimmed()==""){
        ui->nameEdit->setFocus();
        ui->lbl_Note->setText("旅客姓名不能为空！");
        ui->lbl_Note->setStyleSheet("color:red");
        return;
    }
    else if(ui->idEdit->text().trimmed()==""){
        ui->idEdit->setFocus();
        ui->lbl_Note->setText("旅客电话不能为空！");
        ui->lbl_Note->setStyleSheet("color:red");
        return;
    }
    else if(ui->noneEdit->text().trimmed()==""){
        ui->noneEdit->setFocus();
        ui->lbl_Note->setText("请添加旅客的身份证号");
        ui->lbl_Note->setStyleSheet("color:red");
        return;
    }
    else{
        QString name = ui->nameEdit->text().trimmed();
        QString phone = ui->idEdit->text().trimmed();

        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            qWarning() << "Database not open!";
            return;
        }
        QSqlQuery query;
        query.exec("USE flight");
        query.prepare("INSERT INTO other_passenger (id, other_id, other_name) VALUES (:id, :other_id, :other_name)");
        query.bindValue(":id", pa.getid());
        query.bindValue(":other_id", phone);
        query.bindValue(":other_name", name);
        if (!query.exec()) {
            ui->lbl_Note->setText("插入数据失败！");
            ui->lbl_Note->setStyleSheet("color:red");
            qWarning() << "Insert failed: " << query.lastError().text();
        } else {
            ui->lbl_Note->setText("数据添加成功！");
            ui->lbl_Note->setStyleSheet("color:green");
            ui->nameEdit->clear();
            ui->idEdit->clear();
            ui->noneEdit->clear();
            makepa();
        }
    }
}


void InfoWindow::on_exitBtn_clicked()
{
    emit closeAllWindows(); // 发出关闭所有窗口的信号
    this->close();
}

void InfoWindow::onCancelButtonClicked(const QString& ticketNumber, QScrollArea *scroller) {
    qDebug() << "取消按钮已按下";
    Cancelsignal = 2;
    num = ticketNumber;
    detail *d = new detail();
    connect(d, &QObject::destroyed, this, [this, scroller]() {
        this->deletticket(scroller);
        this->showboughtticket(scroller);
    });
    d->show();
    // deletticket(scroller);
}

void InfoWindow::ondetailButtonClicked(const QString& ticketNumber)
{
    num = ticketNumber;
    detail* d=new detail();
    d->show();
}

void InfoWindow::onChangeButtonClicked(const QString& ticketNumber)
{
    num=ticketNumber;
    qDebug()<<"改签按钮已按下";
    Buysignal=1;
    checkWindow * c=new checkWindow();
    c->show();
}

void InfoWindow::onPayButtonClicked(const QString& ticketNumber)
{
    qDebug() << "支付按下";

    // 创建自定义对话框
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("支付");
    dialog->setFont(QFont(dialog->font().family(), 12));

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *infoLabel = new QLabel("请选择支付方式：");
    layout->addWidget(infoLabel);
    QRadioButton *creditCardButton = new QRadioButton("信用卡支付", dialog);
    QRadioButton *alipayButton = new QRadioButton("支付宝支付", dialog);
    QRadioButton *wechatPayButton = new QRadioButton("微信支付", dialog);
    layout->addWidget(creditCardButton);
    layout->addWidget(alipayButton);
    layout->addWidget(wechatPayButton);
    creditCardButton->setChecked(true);

    QPushButton *okButton = new QPushButton("支付", dialog);
    QPushButton *cancelButton = new QPushButton("取消", dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // 连接按钮的信号到槽函数
    connect(okButton, &QPushButton::clicked, this, [ ticketNumber, dialog, creditCardButton, alipayButton, wechatPayButton]() {
        QRadioButton *selectedButton = creditCardButton->isChecked() ? creditCardButton :
                                           alipayButton->isChecked() ? alipayButton :
                                           wechatPayButton;
        if (selectedButton) {
            qDebug() << "选中的支付方式:" << selectedButton->text();
            // 这里添加处理支付的代码
            QSqlDatabase db = QSqlDatabase::database(); // 获取默认数据库连接
            if (db.isOpen()) {
                QSqlQuery query;
                query.exec("USE flight");
                qDebug()<<"nihao";
                if (db.transaction()) { // 开始事务
                    query.prepare("UPDATE ticket SET status = 1 WHERE ticketnum = :tn");
                    query.bindValue(":tn", ticketNumber);
                    if (query.exec()) {
                        db.commit(); // 提交事务
                        qDebug() << "票状态更新成功";
                        QMessageBox::information(dialog, "支付成功", "您已成功支付。");
                    } else {
                        db.rollback(); // 回滚事务
                        qDebug() << "更新票状态失败: " << query.lastError().text();
                        QMessageBox::warning(dialog, "支付失败", "更新票状态失败。");
                    }
                } else {
                    qDebug() << "开始事务失败";
                    QMessageBox::warning(dialog, "支付失败", "开始事务失败。");
                }
            } else {
                qDebug() << "数据库未打开";
                QMessageBox::warning(dialog, "支付失败", "数据库未打开。");
            }
            dialog->accept(); // 关闭对话框
        } else {
            qDebug() << "没有选择支付方式";
            QMessageBox::warning(dialog, "支付失败", "请选择支付方式。");
        }
    });

    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}

void InfoWindow::onButtonClicked(const QString& ticketNumber,QScrollArea *scroller)
{
    qDebug()<<"退票按钮已按下";
    Cancelsignal=1;
    num = ticketNumber;
    detail *d = new detail();
    connect(d, &QObject::destroyed, this, [this, scroller]() {
        this->deletticket(scroller);
        this->showboughtticket(scroller);
    });
    d->show();
}
void InfoWindow::deletticket(QScrollArea *scroller)
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
    // showboughtticket(scroller);
}
