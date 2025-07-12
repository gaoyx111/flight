#include "homepage.h"
#include "customerservicepage.h"
#include "loginwindow.h"
#include "InfoWindow.h"
#include "qsqlerror.h"
#include "ui_homepage.h"
#include "checkWindow.h"
#include <QRandomGenerator>
extern int fromhomepage;
extern flight flightfrompage;
extern int Buysignal;
HomePage::HomePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);
    imageInfos << ImageInfo(":/sign/bei'jing.jpg", "北京：历史与现代的交汇点")
               << ImageInfo(":/sign/cheng'du.jpg", "成都：熊猫的故乡，美食的天堂")
               << ImageInfo(":/sign/guang'zhou.jpg", "广州：南国明珠，贸易与文化的门户")
               << ImageInfo(":/sign/hang'zhou.jpg", "杭州：西湖美景，人间天堂")
               << ImageInfo(":/sign/xi'an.jpg", "西安：古丝绸之路的起点，历史的见证")
               << ImageInfo(":/sign/shang'hai.jpg", "上海：东方明珠，时尚与金融的中心")
               << ImageInfo(":/sign/shen'zhen.jpg", "深圳：中国的硅谷，创新之城")
               << ImageInfo(":/sign/nan'jing.jpg", "南京：六朝古都，江南佳丽地")
               << ImageInfo(":/sign/niu'yue.jpg", "纽约：梦想与机遇的交汇")
               << ImageInfo(":/sign/sing'ga'po.jpg", "新加坡：花园城市，亚洲的十字路口")
               << ImageInfo(":/sign/xin'jiang.jpg", "新疆：丝绸之路上的神秘土地，自然与文化的融合")
               << ImageInfo(":/sign/xi'zang.jpg", "西藏：世界屋脊，心灵的净土")
               << ImageInfo(":/sign/lun'dun.jpg", "伦敦：泰晤士河畔的历史名城，传统与现代的融合");
    refreshContent();
    connect(ui->homeBtn, &QPushButton::clicked, this, &HomePage::refreshContent);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_userInfoButton_clicked()
{
    this->hide();
    InfoWindow *sub = new InfoWindow();
    connect(sub, &InfoWindow::closeAllWindows, this, &HomePage::closeAllWindows);
    connect(sub, &InfoWindow::returnToHome, this, &HomePage::show);
    sub->setAttribute(Qt::WA_DeleteOnClose); // 设置子窗体属性：关闭即销毁
    sub->show();
}


void HomePage::on_buyButton_clicked()
{
    this->hide();//当前窗体隐藏
    Buysignal=0;
    checkWindow *sub = new checkWindow();//新建子窗体
    connect(sub,&checkWindow::checkClose,this,&QWidget::show);//关联子窗体关闭信号与父窗体显示事件
    sub->setAttribute(Qt::WA_DeleteOnClose);//设置子窗体属性：关闭即销毁
    sub->show();//显示子窗体
}


void HomePage::on_staffCenterButton_clicked()
{
    CustomerServicePage *sub = new CustomerServicePage();//新建子窗体
    sub->show();//显示子窗体
}

void HomePage::closeAllWindows()
{
    this->close(); // 关闭HomePage
    LoginWindow *loginWindow = new LoginWindow(); // 创建LoginWindow
    loginWindow->show(); // 显示LoginWindow
}

void HomePage::refreshContent() {
    // 随机选择三个不同的 ImageInfo 对象
    QVector<ImageInfo> selectedInfos;
    QSet<int> usedIndexes;
    while (selectedInfos.size() < 3 && !usedIndexes.contains(usedIndexes.size())) {
        int index = QRandomGenerator::global()->bounded(0, imageInfos.size());
        if (!usedIndexes.contains(index)) {
            selectedInfos.append(imageInfos[index]);
            usedIndexes.insert(index);
        }
    }

    // 更新图片和描述
    for (int i = 0; i < selectedInfos.size(); ++i) {
        const ImageInfo &info = selectedInfos[i];
        QPixmap pixmap(info.imagePath);
        if (i == 0){
            ui->picture1->setPixmap(pixmap.scaled(ui->picture1->size(), Qt::KeepAspectRatio));
            ui->text1->setText(info.description);
            ui->hot1->setText("🔥" + info.description.split("：").first());
        }
        else if (i == 1) {
            ui->picture2->setPixmap(pixmap.scaled(ui->picture2->size(), Qt::KeepAspectRatio));
            ui->text2->setText(info.description);
            ui->hot2->setText("🔥" + info.description.split("：").first());
        }
        else if (i == 2) {
            ui->picture3->setPixmap(pixmap.scaled(ui->picture3->size(), Qt::KeepAspectRatio));
            ui->text3->setText(info.description);
            ui->hot3->setText("🔥" + info.description.split("：").first());
        }
    }

    //查价格最低的两张机票
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("SELECT flight_id, flight_company, startCity, endCity, economyPrice, startTime, endTime FROM flight_info WHERE economyPrice < 500 AND startTime >= CURRENT_TIMESTAMP ORDER BY RAND() LIMIT 2");
    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            if (row == 0) {
                QString startTime = query.value(5).toString();
                QString endTime = query.value(6).toString();
                QDateTime dateTime1 = QDateTime::fromString(startTime, "yyyy-MM-dd HH:mm:ss");
                QDateTime dateTime2 = QDateTime::fromString(endTime, "yyyy-MM-dd HH:mm:ss");
                QTime timePart1 = dateTime1.time();
                QTime timePart2 = dateTime2.time();
                QString formattedTimePart1 = timePart1.toString("HH:mm");
                QString formattedTimePart2 = timePart2.toString("HH:mm");
                ui->beginTime_2->setText(formattedTimePart1);
                ui->arrivalTime_2->setText(formattedTimePart2);
                ui->airlineNumber_2->setText(/*query.value(1).toString()*/query.value(0).toString());
                ui->fromPlace_2->setText(query.value(2).toString());
                ui->toPlace_2->setText(query.value(3).toString());
                ui->label_2->setText(QString::number(query.value(4).toInt()));
            } else if (row == 1) {
                QString startTime = query.value(5).toString();
                QString endTime = query.value(6).toString();
                QDateTime dateTime1 = QDateTime::fromString(startTime, "yyyy-MM-dd HH:mm:ss");
                QDateTime dateTime2 = QDateTime::fromString(endTime, "yyyy-MM-dd HH:mm:ss");
                QTime timePart1 = dateTime1.time();
                QTime timePart2 = dateTime2.time();
                QString formattedTimePart1 = timePart1.toString("HH:mm");
                QString formattedTimePart2 = timePart2.toString("HH:mm");
                ui->beginTime_4->setText(formattedTimePart1);
                ui->arrivalTime_4->setText(formattedTimePart2);
                ui->airlineNumber_4->setText(/*query.value(1).toString()+*/query.value(0).toString());
                ui->fromPlace_4->setText(query.value(2).toString());
                ui->toPlace_4->setText(query.value(3).toString());
                ui->label_4->setText(QString::number(query.value(4).toInt()));
            }
            row++;
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }

}



void HomePage::on_ticket1_clicked()
{
    QString flight_Id = ui->airlineNumber_2->text();
    qDebug()<<flight_Id;
    this->hide(); // 当前窗体隐藏
    fromhomepage = 1;
    Buysignal=0;
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("SELECT flight_id, flight_company, stopCity, startport, stopport, endport, economyClass, businessClass, firstClass, businessPrice, firstPrice, startCity, endCity, economyPrice, startTime, endTime FROM flight_info WHERE flight_id = :flightId");
    query.bindValue(":flightId", flight_Id); // 绑定 flight_Id 变量到查询
    if (query.exec()) {
        if (query.next()) {
            flight *f = new flight(query.value("flight_id").toString(), query.value("startCity").toString(), query.value("stopCity").toString(), query.value("endCity").toString(), query.value("startTime").toString(), query.value("endTime").toString(), query.value("flight_company").toString(), query.value("startport").toString(), query.value("stopport").toString(), query.value("endport").toString(), query.value("economyClass").toInt(), query.value("businessClass").toInt(), query.value("firstClass").toInt(), query.value("economyPrice").toInt(), query.value("businessPrice").toInt(), query.value("firstPrice").toInt());
            flightfrompage = *f;
            qDebug()<<"存在"<<f->startcity<<f->endcity;
        }
    } else {
        qDebug() << "查询失败：" << query.lastError().text();
    }
    checkWindow *sub = new checkWindow(); // 新建子窗体
    connect(sub, &checkWindow::checkClose, this, &QWidget::show); // 关联子窗体关闭信号与父窗体显示事件
    sub->setAttribute(Qt::WA_DeleteOnClose); // 设置子窗体属性：关闭即销毁

    sub->show(); // 显示子窗体

}


void HomePage::on_ticket2_clicked()
{
    QString flight_Id = ui->airlineNumber_4->text();
    qDebug()<<flight_Id;
    this->hide(); // 当前窗体隐藏
    fromhomepage = 1;
    Buysignal=0;
    QSqlQuery query;
    query.exec("USE flight");
    query.prepare("SELECT flight_id, flight_company, stopCity, startport, stopport, endport, economyClass, businessClass, firstClass, businessPrice, firstPrice, startCity, endCity, economyPrice, startTime, endTime FROM flight_info WHERE flight_id = :flightId");
    query.bindValue(":flightId", flight_Id); // 绑定 flight_Id 变量到查询
    if (query.exec()) {
        if (query.next()) {
            flight *f = new flight(query.value("flight_id").toString(), query.value("startCity").toString(), query.value("stopCity").toString(), query.value("endCity").toString(), query.value("startTime").toString(), query.value("endTime").toString(), query.value("flight_company").toString(), query.value("startport").toString(), query.value("stopport").toString(), query.value("endport").toString(), query.value("economyClass").toInt(), query.value("businessClass").toInt(), query.value("firstClass").toInt(), query.value("economyPrice").toInt(), query.value("businessPrice").toInt(), query.value("firstPrice").toInt());
            flightfrompage = *f;
            qDebug()<<"存在"<<f->startcity<<f->endcity;
        }
    } else {
        qDebug() << "查询失败：" << query.lastError().text();
    }
    checkWindow *sub = new checkWindow(); // 新建子窗体
    connect(sub, &checkWindow::checkClose, this, &QWidget::show); // 关联子窗体关闭信号与父窗体显示事件
    sub->setAttribute(Qt::WA_DeleteOnClose); // 设置子窗体属性：关闭即销毁

    sub->show(); // 显示子窗体
}

