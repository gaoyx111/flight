#include "managerwindow.h"
#include "qsqlerror.h"
#include "ui_managerwindow.h"
#include "loginwindow.h"
#include <QMessageBox>

ManagerWindow::ManagerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    stackedWidget = ui->stackedWidget;

    flightPage = ui->stackedWidget->widget(1);
    userPage = ui->stackedWidget->widget(0);

    flightTable=ui->flightlist;
    userTable=ui->userlist;
    ui->flightlist->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    // delegate = new CustomItemDelegate(ui->flightlist);
    // ui->flightlist->setItemDelegate(delegate);
    ui->flightlist->setStyleSheet("QTableWidget::item:selected { color: blue; }");
    ui->userlist->setStyleSheet("QTableWidget::item:selected { color: blue; }");

    stackedWidget->addWidget(flightPage);
    stackedWidget->addWidget(userPage);

    stackedWidget->setCurrentWidget(flightPage);
    flightquery();
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_userPageButton_clicked()
{
    stackedWidget->setCurrentWidget(userPage);
    userquery();
}


void ManagerWindow::on_FlightPageButton_clicked()
{
    stackedWidget->setCurrentWidget(flightPage);
    flightquery();
}


void ManagerWindow::on_exitButton_clicked()
{
    this->hide();
    LoginWindow* lw=new LoginWindow();
    lw->show();
}

void ManagerWindow::flightquery(){
    ui->flightlist->clearContents();
    //打开数据库
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT flight_id, flight_company, startCity, startTime, endCity, endTime FROM flight_info")) {
        int rowCount = 0;
        while (query.next()) {
            rowCount++;
        }
        // 设置 QTableWidget 行数和列数
        ui->flightlist->setRowCount(rowCount);

        query.first();
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem* flightIDItem = new QTableWidgetItem(query.value(0).toString());
            flightIDItem->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 0, flightIDItem);

            QTableWidgetItem* flightCompanyItem = new QTableWidgetItem(query.value(1).toString());
            flightCompanyItem->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 1, flightCompanyItem);

            QTableWidgetItem* departurePlaceItem = new QTableWidgetItem(query.value(2).toString());
            departurePlaceItem->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 2, departurePlaceItem);

            QTableWidgetItem* departTimeItem = new QTableWidgetItem(query.value(3).toString());
            departTimeItem->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 3, departTimeItem);

            QTableWidgetItem* arrvalPlace = new QTableWidgetItem(query.value(4).toString());
            arrvalPlace->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 4, arrvalPlace);

            QTableWidgetItem* arrivalTime = new QTableWidgetItem(query.value(5).toString());
            arrivalTime->setTextAlignment(Qt::AlignCenter);
            ui->flightlist->setItem(row, 5, arrivalTime);

            query.next();
        }
    } else {
        qDebug() << "查询失败：" ;
    }
}

void ManagerWindow::userquery(){
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "数据库未打开";
        return;// 返回空列表
    }
    QSqlQuery query;
    query.exec("USE flight");
    if (query.exec("SELECT administrator_id, administrator_name, administrator_password FROM administrator")) {
        int rowCount = 0;
        while (query.next()) {
            rowCount++;
        }
        // 设置 QTableWidget 行数和列数
        ui->userlist->setRowCount(rowCount);

        query.first();
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem* flightIDItem = new QTableWidgetItem(query.value(0).toString());
            flightIDItem->setTextAlignment(Qt::AlignCenter);
            ui->userlist->setItem(row, 0, flightIDItem);

            QTableWidgetItem* flightCompanyItem = new QTableWidgetItem(query.value(1).toString());
            flightCompanyItem->setTextAlignment(Qt::AlignCenter);
            ui->userlist->setItem(row, 1, flightCompanyItem);

            QString secret=query.value(2).toString();
            // int len=secret.length();
            // QString s="";
            // for(int i=0;i<len;i++) s+='*';                            //掩码 待修改！！！！
            QTableWidgetItem* departurePlaceItem = new QTableWidgetItem(secret);
            departurePlaceItem->setTextAlignment(Qt::AlignCenter);
            ui->userlist->setItem(row, 2, departurePlaceItem);

            query.next();
        }
    } else {
        qDebug() << "查询失败：" ;
    }
}

void ManagerWindow::on_flightlist_itemSelectionChanged()
{
    QList<QTableWidgetItem *> selectedItems = ui->flightlist->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取选中行的第一列的单元格
        int row = selectedItems.first()->row();

        // 填充对应的 QLineEdit
        if (row >= 0) {
            ui->numEdit->setText(ui->flightlist->item(row, 0) ? ui->flightlist->item(row, 0)->text() : "");
            ui->companyEdit->setText(ui->flightlist->item(row, 1) ? ui->flightlist->item(row, 1)->text() : "");
            ui->fromEdit->setText(ui->flightlist->item(row, 2) ? ui->flightlist->item(row, 2)->text() : "");
            ui->goEdit->setText(ui->flightlist->item(row, 3) ? ui->flightlist->item(row, 3)->text() : "");
            ui->arrEdit->setText(ui->flightlist->item(row, 4) ? ui->flightlist->item(row, 4)->text() : "");
            ui->landEdit->setText(ui->flightlist->item(row, 5) ? ui->flightlist->item(row, 5)->text() : "");
        }
    }
}


void ManagerWindow::on_cancelButton_clicked()
{
    ui->numEdit->setText("");
    ui->companyEdit->setText("");
    ui->fromEdit->setText("");
    ui->goEdit->setText("");
    ui->arrEdit->setText("");
    ui->landEdit->setText("");
}


void ManagerWindow::on_changeList_2_clicked()
{
    // 获取选中行
    QList<QTableWidgetItem *> selectedItems = ui->flightlist->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "选择行", "请选中一行进行修改");
        return;
    }

    int row = selectedItems.first()->row();

    // 获取 QLineEdit 中的数据
    QString flightId = ui->numEdit->text();
    QString flightCompany = ui->companyEdit->text();
    QString startCity = ui->fromEdit->text();
    QString startTime = ui->goEdit->text();
    QString endCity = ui->arrEdit->text();
    QString endTime = ui->landEdit->text();
    ui->numEdit->setText("");
    ui->companyEdit->setText("");
    ui->fromEdit->setText("");
    ui->goEdit->setText("");
    ui->arrEdit->setText("");
    ui->landEdit->setText("");

    // 更新数据库
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("UPDATE flight_info SET flight_company = ?, startCity = ?, startTime = ?, endCity = ?, endTime = ? WHERE flight_id = ?");
    query.addBindValue(flightCompany);
    query.addBindValue(startCity);
    query.addBindValue(startTime);
    query.addBindValue(endCity);
    query.addBindValue(endTime);
    query.addBindValue(flightId);

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库更新失败", query.lastError().text());
        return;
    }

    // ui->flightlist->clearContents();
    // flightquery();
    // 更新 QTableWidget
    ui->flightlist->item(row, 0)->setText(flightId);
    ui->flightlist->item(row, 1)->setText(flightCompany);
    ui->flightlist->item(row, 2)->setText(startCity);
    ui->flightlist->item(row, 3)->setText(startTime);
    ui->flightlist->item(row, 4)->setText(endCity);
    ui->flightlist->item(row, 5)->setText(endTime);

    // 设置每个单元格的对齐方式为居中
    ui->flightlist->item(row, 0)->setTextAlignment(Qt::AlignCenter);
    ui->flightlist->item(row, 1)->setTextAlignment(Qt::AlignCenter);
    ui->flightlist->item(row, 2)->setTextAlignment(Qt::AlignCenter);
    ui->flightlist->item(row, 3)->setTextAlignment(Qt::AlignCenter);
    ui->flightlist->item(row, 4)->setTextAlignment(Qt::AlignCenter);
    ui->flightlist->item(row, 5)->setTextAlignment(Qt::AlignCenter);

    QMessageBox::information(this, "修改成功", "航班信息已成功更新");
}

void ManagerWindow::on_deleteList_2_clicked()
{
    // 获取选中的单元格
    QList<QTableWidgetItem *> selectedItems = ui->flightlist->selectedItems();

    // 确保至少选中了一行
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "选择行", "请选中一行进行删除");
        return;
    }

    // 获取选中行的 flight_id
    int row = selectedItems.first()->row();
    QString flightId = ui->flightlist->item(row, 0)->text();

    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  QString("您确定要删除航班 %1 吗？").arg(flightId),
                                  QMessageBox::Yes | QMessageBox::No);

    // 如果用户点击了 Yes 执行删除
    if (reply == QMessageBox::Yes) {
        // 删除数据库中的记录
        QSqlQuery query;
        query.exec("USE flight");
        query.prepare("DELETE FROM flight_info WHERE flight_id = ?");
        query.addBindValue(flightId);

        if (!query.exec()) {
            QMessageBox::critical(this, "删除失败", query.lastError().text());
            return;
        }

        // 从 QTableWidget 中移除该行
        ui->flightlist->removeRow(row);

        // 提示删除成功
        QMessageBox::information(this, "删除成功", "航班信息已成功删除");
    } else {
        // 如果用户选择了 No，什么都不做
        QMessageBox::information(this, "删除取消", "操作已取消");
    }
}


void ManagerWindow::on_NewList_2_clicked()
{
    ui->flightlist->clearSelection();

    QString value1 = ui->numEdit->text();  // 航班编号
    QString value2 = ui->companyEdit->text();  // 航空公司
    QString value3 = ui->fromEdit->text();  // 出发地
    QString value4 = ui->goEdit->text();  // 起飞时间（字符串格式）
    QString value5 = ui->arrEdit->text();  // 目的地
    QString value6 = ui->landEdit->text();  // 降落时间（字符串格式）

    if (value1.isEmpty() || value2.isEmpty() || value3.isEmpty() || value4.isEmpty() || value5.isEmpty() || value6.isEmpty()) {
        QMessageBox::warning(this, "填写不完整", "请确保所有字段都已填写完整");
        return;
    }

    QString message = QString("您输入的信息如下：\n\n"
                              "航班编号: %1\n"
                              "航空公司: %2\n"
                              "出发地: %3\n"
                              "起飞时间: %4\n"
                              "目的地: %5\n"
                              "降落时间: %6\n\n"
                              "是否确认添加这些信息？")
                          .arg(value1)
                          .arg(value2)
                          .arg(value3)
                          .arg(value4)
                          .arg(value5)
                          .arg(value6);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "确认信息", message,
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("USE flight");

        // 确保数据库已连接
        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            qDebug() << "数据库连接失败：" << db.lastError().text();
            return;
        }

        // 准备插入数据的 SQL 语句
        query.prepare("INSERT INTO flight_info (flight_id, flight_company, startCity, startTime, endCity, endTime) "
                      "VALUES (?, ?, ?, ?, ?, ?)");

        // 绑定数据
        query.addBindValue(value1);
        query.addBindValue(value2);
        query.addBindValue(value3);
        query.addBindValue(value4);  // 起飞时间作为字符串
        query.addBindValue(value5);  // 目的地
        query.addBindValue(value6);  // 降落时间作为字符串

        // 执行查询
        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", query.lastError().text());
            return;
        }

        // 更新 UI 表格
        int row = ui->flightlist->rowCount();
        ui->flightlist->insertRow(row);
        ui->flightlist->setItem(row, 0, new QTableWidgetItem(value1));
        ui->flightlist->setItem(row, 1, new QTableWidgetItem(value2));
        ui->flightlist->setItem(row, 2, new QTableWidgetItem(value3));
        ui->flightlist->setItem(row, 3, new QTableWidgetItem(value4));
        ui->flightlist->setItem(row, 4, new QTableWidgetItem(value5));
        ui->flightlist->setItem(row, 5, new QTableWidgetItem(value6));

        // 清空输入框
        ui->numEdit->clear();
        ui->companyEdit->clear();
        ui->fromEdit->clear();
        ui->goEdit->clear();
        ui->arrEdit->clear();
        ui->landEdit->clear();

        // 提示用户成功添加
        QMessageBox::information(this, "新建成功", "新建航班信息已成功添加");
    }
}



void ManagerWindow::on_deleteList_clicked()
{
    // 获取选中的单元格
    QList<QTableWidgetItem *> selectedItems = ui->userlist->selectedItems();

    // 确保至少选中了一行
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "选择行", "请选中一行进行删除");
        return;
    }

    int row = selectedItems.first()->row();
    QString adId = ui->userlist->item(row, 0)->text();

    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  QString("您确定要删除管理员 %1 吗？").arg(adId),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("USE flight");
        query.prepare("DELETE FROM administrator WHERE administrator_id = ?");
        query.addBindValue(adId);

        if (!query.exec()) {
            QMessageBox::critical(this, "删除失败", query.lastError().text());
            return;
        }

        ui->userlist->removeRow(row);

        QMessageBox::information(this, "删除成功", "该管理员已成功删除");
    } else {
        QMessageBox::information(this, "删除取消", "操作已取消");
    }
}


void ManagerWindow::on_changeList_clicked()          //掩码问题！！！！！！！
{
    QList<QTableWidgetItem *> selectedItems = ui->userlist->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "选择行", "请选中一行进行修改");
        return;
    }

    int row = selectedItems.first()->row();

    // 获取 QLineEdit 中的数据
    QString adId = ui->userlist->item(row, 0)->text();
    QString adname = ui->adIDEdit->text();
    QString adse = ui->adseEdit->text();

    ui->adIDEdit->setText("");
    ui->adseEdit->setText("");


    // 更新数据库
    QSqlQuery query;
    query.exec("USE flight");
    query.exec("SET SQL_SAFE_UPDATES = 0");  // 禁用安全更新
    query.prepare("UPDATE administrator SET administrator_name = ?, administrator_password = ? WHERE administrator_id = ?");
    query.addBindValue(adname);
    query.addBindValue(adse);
    query.addBindValue(adId);


    if (!query.exec()) {
        QMessageBox::critical(this, "数据库更新失败", query.lastError().text());
        return;
    }

    // 更新 QTableWidget
    ui->userlist->item(row, 1)->setText(adname);
    ui->userlist->item(row, 2)->setText(adse);

    QMessageBox::information(this, "修改成功", "管理员信息已成功更新");
}


void ManagerWindow::on_userlist_itemSelectionChanged()
{
    QList<QTableWidgetItem *> selectedItems = ui->userlist->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取选中行的第一列的单元格
        int row = selectedItems.first()->row();

        // 填充对应的 QLineEdit
        if (row >= 0) {
            ui->adIDEdit->setText(ui->userlist->item(row, 1) ? ui->userlist->item(row, 1)->text() : "");
            ui->adseEdit->setText(ui->userlist->item(row, 2) ? ui->userlist->item(row, 2)->text() : "");
        }
    }
}


void ManagerWindow::on_cancelBtn_clicked()
{
    ui->adIDEdit->setText("");
    ui->adseEdit->setText("");
}

