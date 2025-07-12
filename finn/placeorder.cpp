#include "placeorder.h"
#include "passenger.h"
#include "paymentdialog.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "qdialog.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_placeorder.h"
#include "paymentdialog.h"
extern passenger pa;
QString num;
QString fid;

PlaceOrder::PlaceOrder(QWidget *parent,QString randomNumberString)
    : QMainWindow(parent)
    , ui(new Ui::PlaceOrder)
{
    ui->setupUi(this);
//    ui->tableWidget->setStyleSheet("QTableWidget::item:selected { color: blue; }");
    num=randomNumberString;
    passengerquery(randomNumberString);
}

PlaceOrder::~PlaceOrder()
{
    delete ui;
}

void PlaceOrder::passengerquery(QString randomNumberString) {
    //显示表格
    ui->tableWidget->clearContents();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;
    }
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("SELECT other_id, other_name FROM other_passenger WHERE id = :id");
    query.bindValue(":id", pa.getid());
    if (query.exec()) {
        ui->tableWidget->insertRow(0);

        QTableWidgetItem *item1 = new QTableWidgetItem("是");
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0, 0, item1);
        panum++;

        QTableWidgetItem *item2 = new QTableWidgetItem(pa.getname());
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(pa.getid());
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0, 2, item3);

        int row = 1;
        while (query.next()) {
            if (ui->tableWidget->rowCount() <= row) {
                ui->tableWidget->insertRow(row);
            }

            QString other_id = query.value(0).toString();
            QString other_name = query.value(1).toString();

            QTableWidgetItem *item1 = new QTableWidgetItem("否");
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(other_name);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 1, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem(other_id);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 2, item3);

            row++;
        }
        if (row == 1) {
            qDebug() << "没有其他乘客信息";
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }

    //显示票
    ui->lbl_num->setText("订单号："+randomNumberString);
    query.exec("USE flight");
    query.prepare("SELECT flight_id, class FROM ticket WHERE ticketnum = :num and id = :id");
    query.bindValue(":num", randomNumberString);
    query.bindValue(":id", pa.getid());

    if (query.exec()) {
        if (query.next()) {
            QString flight_id = query.value(0).toString();
            fid=flight_id;
            class_type = query.value(1).toString();
            if (class_type == "经济舱") {
                ui->economyClassChoose->setChecked(true);
            } else if (class_type == "商务舱") {
                ui->businessClassChoose->setChecked(true);
            } else if (class_type == "头等舱") {
                ui->firstClassChoose->setChecked(true);
            }

            QSqlQuery flightQuery;
            flightQuery.exec("USE flight");
            flightQuery.prepare("SELECT flight_company, startCity, endCity, startport, endport, startTime, endTime, economyPrice, businessPrice, firstPrice FROM flight_info WHERE flight_id = :flight_id");
            flightQuery.bindValue(":flight_id", flight_id);

            if (flightQuery.exec()) {
                if (flightQuery.next()) {
                    QString flight_company = flightQuery.value(0).toString();
                    QString startCity = flightQuery.value(1).toString();
                    QString endCity = flightQuery.value(2).toString();
                    QString startport = flightQuery.value(3).toString();
                    QString endport = flightQuery.value(4).toString();
                    QString startTime = flightQuery.value(5).toString();
                    QString endTime = flightQuery.value(6).toString();
                    ep=flightQuery.value(7).toString();
                    bp=flightQuery.value(8).toString();
                    fp=flightQuery.value(9).toString();
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
                    QString spentTime = QString("%1小时%2分钟").arg(hours).arg(minutes);
                    orderInfo = QString("订单号：%1\n航班号：%2\n出发城市：%3 %4\n到达城市：%5 %6\n出发时间：%7 %8\n到达时间：%9 %10\n飞行时间：%11")
                                    .arg(randomNumberString)
                                    .arg(flight_company + flight_id)
                                    .arg(startCity)
                                    .arg(startport)  // 将出发机场放到出发城市的后面
                                    .arg(endCity)
                                    .arg(endport)    // 将到达机场放到到达城市的后面
                                    .arg(date1)
                                    .arg(time1)
                                    .arg(date2)
                                    .arg(time2)
                                    .arg(spentTime);

                    ui->beginTime_7->setText(time1);
                    ui->arrivalTime_7->setText(time2);
                    ui->fromWhere_7->setText(startCity);
                    ui->fromWhere_8->setText(startport);
                    ui->toWhere_7->setText(endCity);
                    ui->toWhere_8->setText(endport);
                    ui->flightNumber->setText(flight_company + flight_id);
                    ui->spentTime->setText(spentTime);
                    ui->date->setText(date1);
                    ui->week->setText(week1);
                    ui->economyClassChoose->setText("经济舱 ￥"+ep);
                    ui->businessClassChoose->setText("商务舱 ￥"+bp);
                    ui->firstClassChoose->setText("头等舱 ￥"+fp);

                } else {
                    qDebug() << "没有找到对应的航班信息";
                }
            } else {
                qDebug() << "查询航班信息失败: " << flightQuery.lastError().text();
            }

        } else {
            qDebug() << "没有找到对应的票务信息";
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }
}

void PlaceOrder::on_choosePassenger_clicked()
{
    QList<QModelIndex> selectedIndexes = ui->tableWidget->selectionModel()->selectedIndexes();
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) {
            QTableWidgetItem *item = ui->tableWidget->item(index.row(), 0);
            if (item && item->text() != "是") {
                item->setText("是");
                panum++;
            }
        }
    }
}

void PlaceOrder::on_choosePassenger_2_clicked()
{
    QList<QModelIndex> selectedIndexes = ui->tableWidget->selectionModel()->selectedIndexes();
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0 && index.row() != 0) {
            QTableWidgetItem *item = ui->tableWidget->item(index.row(), 0);
            if (item && item->text() != "否") {
                item->setText("否");
                panum--;
            }
        }
    }
}

void PlaceOrder::on_subitOrder_clicked()
{
    // 计算票价
    if (class_type == "经济舱") {
        checkprice = panum * ep.toInt();
    } else if (class_type == "商务舱") {
        checkprice = panum * bp.toInt();
    } else if (class_type == "头等舱") {
        checkprice = panum * fp.toInt();
    }

    // 获取选中的乘客
    QList<QPair<QString, QString>> selectedPassengers;
    for (int row = 1; row < ui->tableWidget->rowCount(); ++row) {
        QString isSelected = ui->tableWidget->item(row, 0)->text();
        if (isSelected == "是") {
            QString pa_id = ui->tableWidget->item(row, 2)->text();
            QString pa_name = ui->tableWidget->item(row, 1)->text();
            selectedPassengers.append(qMakePair(pa_id, pa_name));
        }
    }

    // 更新 flight_info 表中的票数
    QSqlQuery queryUpdate;
    queryUpdate.exec("USE flight");
    QString fieldName;
    if (class_type == "经济舱") {
        fieldName = "economyClass";
    } else if (class_type == "商务舱") {
        fieldName = "businessClass";
    } else if (class_type == "头等舱") {
        fieldName = "firstClass";
    }
    queryUpdate.prepare(QString("UPDATE flight_info SET %1 = %1 - :panum WHERE flight_id = :fid").arg(fieldName));
    queryUpdate.bindValue(":panum", panum);
    queryUpdate.bindValue(":fid", fid);
    if (queryUpdate.exec()) {
        qDebug() << "更新成功";
    } else {
        qDebug() << "更新失败: " << queryUpdate.lastError().text();
    }

    // 如果没有乘客被选中，则直接显示支付对话框
    if (selectedPassengers.isEmpty()) {
        PaymentDialog dialog(orderInfo, panum, checkprice, this);
        dialog.class_type = this->class_type;
        dialog.exec();
        return;
    }

    // 删除原有的记录
    QSqlQuery queryDel;
    queryDel.exec("USE flight");
    queryDel.prepare("DELETE FROM ticket WHERE ticketnum = :num AND id = :id");
    queryDel.bindValue(":num", num);
    queryDel.bindValue(":id", pa.getid());
    if (!queryDel.exec()) {
        qDebug() << "删除原有记录失败: " << queryDel.lastError().text();
        return;
    }

    // 插入新的记录
    QSqlQuery queryIns;
    queryIns.exec("USE flight");
    queryIns.prepare("INSERT INTO ticket (ticketnum, id, flight_id, class, status, pa_id, pa_name) VALUES (?, ?, ?, ?, ?, ?, ?)");

    int status = 0; // 状态值，假设为0
    for (const auto& passenger : selectedPassengers) {
        queryIns.addBindValue(num);  // 票号
        queryIns.addBindValue(pa.getid());  // 乘客ID
        queryIns.addBindValue(fid);  // 航班ID
        queryIns.addBindValue(class_type);  // 舱位
        queryIns.addBindValue(status);  // 状态
        queryIns.addBindValue(passenger.first);  // pa_id
        queryIns.addBindValue(passenger.second);  // pa_name

        if (!queryIns.exec()) {
            qDebug() << "插入乘客信息失败: " << queryIns.lastError().text();
            return;
        }
    }

    // 显示支付对话框
    PaymentDialog dialog(orderInfo, panum, checkprice, this);
    dialog.class_type = this->class_type;
    dialog.exec();
}
