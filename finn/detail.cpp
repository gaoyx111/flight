#include "detail.h"
#include "passenger.h"
#include "qmessagebox.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_detail.h"
#include<qpushbutton.h>
extern QString num;
extern passenger pa;
extern int Cancelsignal;

detail::detail(QWidget *parent)
    : QDialog(parent), ui(new Ui::detail) {
    ui->setupUi(this);
    showdetail();
    if(Cancelsignal==1) {
        QPushButton *sure = new QPushButton("确认退票", this);
        sure->setMinimumSize(200, 60);
        sure->move(180, 550);
        connect(sure, &QPushButton::clicked, this, &detail::onSureButtonClicked);
    } else if(Cancelsignal==2) {
        QPushButton *sure = new QPushButton("确认取消", this);
        sure->setMinimumSize(200, 60);
        sure->move(180, 550);
        connect(sure, &QPushButton::clicked, this, &detail::onSureButtonClicked);
    }
    Cancelsignal = 0;
    setAttribute(Qt::WA_DeleteOnClose); // 设置窗口关闭时自动删除
}

detail::~detail()
{
    delete ui;
}

void detail::showdetail()
{
    ui->lbl_ticketnum->setText("订单号：" + num);
    QSqlQuery query;
    query.exec("USE flight");

    // 查询 ticket 表以获取 flight_id 和舱位类型
    query.prepare("SELECT flight_id, class FROM ticket WHERE ticketnum = :ticketnum");
    query.bindValue(":ticketnum", num);
    QString flight_id;
    QString classType;

    if (query.exec()) {
        if (query.next()) {
            flight_id = query.value(0).toString();
            classType = query.value(1).toString();
        }
    } else {
        qDebug() << "查询 ticket 失败: " << query.lastError().text();
        return;
    }

    // 查询 flight_info 表以获取航班详细信息和票价
    query.prepare("SELECT flight_company, startCity, stopCity, endCity, startport, stopport, endport, startTime, endTime, economyPrice, businessPrice, firstPrice FROM flight_info WHERE flight_id = :flight_id");
    query.bindValue(":flight_id", flight_id);
    double totalCost = 0; // 订单总额
    int economyPrice = 0, businessPrice = 0, firstPrice = 0;

    if (query.exec() && query.next()) {
        QString company = query.value(0).toString();
        QString startCity = query.value(1).toString();
        QString stopCity = query.value(2).toString();
        QString endCity = query.value(3).toString();
        QString startport = query.value(4).toString();
        QString stopport = query.value(5).toString();
        QString endport = query.value(6).toString();
        QString startTime = query.value(7).toString();
        QString endTime = query.value(8).toString();
        economyPrice = query.value(9).toInt();
        businessPrice = query.value(10).toInt();
        firstPrice = query.value(11).toInt();


        // 更新 UI 上的 label
        QDateTime dateTime1 = QDateTime::fromString(startTime, "yyyy-MM-dd HH:mm:ss");
        QDateTime dateTime2 = QDateTime::fromString(endTime, "yyyy-MM-dd HH:mm:ss");
        QString time1 = dateTime1.toString("HH:mm");  // "09:00"
        QString date1 = dateTime1.toString("yyyy-MM-dd");  // "2024-01-01"
        QString week1 = dateTime1.toString("dddd");  // "星期一"
        QString time2 = dateTime2.toString("HH:mm");  // "09:00"
        QString date2 = dateTime2.toString("yyyy-MM-dd");  // "2024-01-01"
        QString week2 = dateTime2.toString("dddd");  // "星期一"
        qint64 secondsDiff = qAbs(dateTime2.secsTo(dateTime1));  // 计算秒数差
        int hours = secondsDiff / 3600;  // 转换为小时
        int minutes = (secondsDiff % 3600) / 60;  // 转换为分钟
        QString spentTime = QString("%1h%2min").arg(hours).arg(minutes);

        QStringList parts = startTime.split(' ');
        QString timePart = parts.size() >= 2 ? parts[1] : QString();
        QString datePart = parts.size() >= 2 ? parts[0] : QString();

        QStringList endparts = endTime.split(' ');
        QString endTimePart = endparts.size() >= 2 ? endparts[1] : QString();
        QString enddatePart = endparts.size() >= 2 ? endparts[0] : QString();

        QDate date = QDate::fromString(datePart, "yyyy-MM-dd");
        int dayOfWeek = date.dayOfWeek();
        QString weekDays[] = {
            "周一", "周二", "周三", "周四", "周五", "周六", "周日"
        };

        ui->lbl_place->setText(startCity + "—>" + endCity);
        ui->lbl_startport->setText(startport);
        ui->lbl_endport->setText(endport);
        ui->lbl_starttime->setText(timePart);
        ui->lbl_endtime->setText(endTimePart);
        ui->lbl_lasttime->setText(spentTime);
        ui->lbl_day->setText(datePart);
        ui->lbl_week->setText(weekDays[dayOfWeek - 1]);

        ui->lbl_flightinfo->setText("✈" + company + flight_id);
        QFont font("Arial", 10);
        ui->lbl_flightinfo->setFont(font);

        if (!stopCity.isEmpty()) {
            ui->lbl_flyclass->setText("中转");
            QLabel *stopmessage = new QLabel("中转信息   中转城市：" + stopCity + "    中转站点：" + stopport, this);
            QPalette pal3 = stopmessage->palette();
            pal3.setColor(QPalette::WindowText, qRgb(85, 170, 255));
            stopmessage->setPalette(pal3);
            stopmessage->move(20, 380);
        } else {
            ui->lbl_flyclass->setText("直飞");
        }
    } else {
        qDebug() << "查询 flight_info 失败: " << query.lastError().text();
    }

    // 查询 ticket 表以获取乘客信息并填充到QTableWidget
    query.prepare("SELECT id, pa_id, pa_name FROM ticket WHERE ticketnum = :ticketnum");
    query.bindValue(":ticketnum", num);
    if (query.exec()) {
        ui->tableWidget->setRowCount(0); // 清空表格
        int row = 0;
        while (query.next()) {
            QString passengerId = query.value(0).toString(); // id
            QString paId = query.value(1).toString(); // pa_id
            QString passengerName = query.value(2).toString(); // pa_name

            if (row == 0) {
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(pa.getname()));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(pa.getid()));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(num));
                row++;
            }

            if (!paId.isEmpty() && !passengerName.isEmpty()) {
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(passengerName));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(paId));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(num));
                row++;
            }
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }
    // 根据舱位类型确定票价
    int pricePerPerson = (classType == "经济舱") ? economyPrice : (classType == "商务舱") ? businessPrice : firstPrice;
  //  qDebug()<<pricePerPerson;
    // 计算订单总额
    int totalPassengers = ui->tableWidget->rowCount(); // 获取QTableWidget上的乘客人数
    //qDebug()<<totalPassengers;
    totalCost = totalPassengers * pricePerPerson;
   // qDebug()<<totalCost;
    ui->lbl_money->setText("¥" + QString::number(totalCost));
    ui->tableWidget->resizeColumnsToContents();
}

void deleteticket()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;
    }

    // QSqlQuery query(db);
    // query.exec("USE flight");

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
    // QSqlQuery countQuery;
    // countQuery.prepare("SELECT COUNT(*) FROM ticket WHERE ticketnum = :ticketnum AND id = :id");
    // countQuery.bindValue(":ticketnum", num);
    // countQuery.bindValue(":id", pa.getid());

    // if (!countQuery.exec()) {
    //     qDebug() << "查询失败: " << countQuery.lastError().text();
    //     return;
    // }

    // if (countQuery.next()) {
    //     int totalPassengersIncludingBuyer = countQuery.value(0).toInt(); // 包括购票人本人

    //     // 查询其他乘客的数量（pa_id 和 pa_name 不为空）
    //     QSqlQuery otherPassengersQuery;
    //     otherPassengersQuery.prepare("SELECT COUNT(*) FROM ticket WHERE ticketnum = :ticketnum AND (pa_id IS NOT NULL AND pa_id <> '') AND id = :id");
    //     otherPassengersQuery.bindValue(":ticketnum", num);
    //     otherPassengersQuery.bindValue(":id", pa.getid());

    //     if (!otherPassengersQuery.exec()) {
    //         qDebug() << "查询失败: " << otherPassengersQuery.lastError().text();
    //         return;
    //     }

    //     if (otherPassengersQuery.next()) {
    //         int otherPassengersCount = otherPassengersQuery.value(0).toInt(); // 其他乘客的数量
    //         int totalPassengers = totalPassengersIncludingBuyer + otherPassengersCount; // 总乘客数

            // 更新flight_info表中的剩余座位数
            QSqlQuery updateQuery;
            updateQuery.prepare("SELECT flight_id, class FROM ticket WHERE ticketnum = :ticketnum");
            updateQuery.bindValue(":ticketnum", num);

            if (updateQuery.exec() && updateQuery.next()) {
                QString flightId = updateQuery.value(0).toString();
                QString classType = updateQuery.value(1).toString();
                QString updateField;

                if (classType == "经济舱") {
                    updateField = "economyClass";
                } else if (classType == "商务舱") {
                    updateField = "businessClass";
                } else if (classType == "头等舱") {
                    updateField = "firstClass";
                }

                if (!updateField.isEmpty()) {
                    updateQuery.prepare(QString("UPDATE flight_info SET %1 = %1 + :totalPassengers WHERE flight_id = :flight_id").arg(updateField));
                    updateQuery.bindValue(":totalPassengers", totalPassengers);
                    updateQuery.bindValue(":flight_id", flightId);

                    if (!updateQuery.exec()) {
                        qDebug() << "更新 flight_info 失败: " << updateQuery.lastError().text();
                    } else {
                        qDebug() << "航班票数更新成功";
                    }
                }
            }
    //     }
    // }

    // 删除ticket表中订单数据
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM ticket WHERE ticketnum = :ticketnum AND id = :id");
    deleteQuery.bindValue(":ticketnum", num);
    deleteQuery.bindValue(":id", pa.getid());
    if (!deleteQuery.exec()) {
        qDebug() << "删除失败: " << deleteQuery.lastError().text();
    } else {
        qDebug() << "删除成功";
    }
}

void detail::onSureButtonClicked()
{
    deleteticket();
    QMessageBox msgBox;
    msgBox.setText("退票成功");
    msgBox.setWindowTitle("退票");
    this->close();
    msgBox.exec();
}

void detail::closeEvent(QCloseEvent *event) {
    emit closed(); // 发射关闭信号
    QDialog::closeEvent(event);
}
