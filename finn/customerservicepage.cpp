#include "customerservicepage.h"
#include "qmessagebox.h"
#include "ui_customerservicepage.h"

CustomerServicePage::CustomerServicePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerServicePage)
{
    ui->setupUi(this);
}

CustomerServicePage::~CustomerServicePage()
{
    delete ui;
}

void CustomerServicePage::on_Q1_clicked()
{
    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setInformativeText("进入个人页面-订单，如已支付的机票可以选择退票，机票的钱将在七个工作日内返回，请耐心等待；如机票处于待支付状态，直接取消订单即可\n");
    msgBox.exec();
}

void CustomerServicePage::on_Q2_clicked()
{
    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setInformativeText("进入个人页面-订单，点击“改签”重新选择机票即可\n注意：\n1.只有已支付的机票才可以改签\n2.改签机票不可以改变乘客信息和票数，如需更改请退票后重新处理\n3.改签必须选择不同的班次，如您只是想选择同一班次的不同舱位，请现场联系工作人员\n4.为回馈新老用户支持，航班系统将免费为您补齐差价，改签退票均不收取额外费用");
    msgBox.exec();
}


void CustomerServicePage::on_Q3_clicked()
{
    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setInformativeText("每日有特价机票可以抢购，购买方式：点击主页下方机票上的蓝色按钮即可跳转购买");
    msgBox.exec();
}


void CustomerServicePage::on_Q4_clicked()
{
    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setInformativeText("积分数=订单实付金额/100；当积分累计10000分时，即可升级为黄金用户，享极速购票特权");
    msgBox.exec();
}


void CustomerServicePage::on_Q4_2_clicked()
{
    QMessageBox msgBox;
    QFont msgFont = msgBox.font();
    msgFont.setPointSize(12); // 设置字体大小为8点
    msgBox.setFont(msgFont);
    msgBox.setInformativeText("请电话联系客服：\n023-23242133\n012-23242344\n我们将24小时竭诚为您服务");
    msgBox.exec();
}

