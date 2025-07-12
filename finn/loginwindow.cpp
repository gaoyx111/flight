#include "loginwindow.h"
#include "ui_loginwindow.h"

#include"managerlogin.h"
#include<managerwindow.h>
#include <QMessageBox>
#include <QtSql>
#include<qlabel.h>
#include<QString>
#include<DBOperator.h>
extern DBOperator op;

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->PassWordLine->setEchoMode(QLineEdit::Password);

    this->newWindow = new ManagerLogin;//实例化管理界面类
    this->newWindowManager = new ManagerWindow;
//    this->newSignUpWindow = new registerWindow;
    this->newHomePage = new HomePage;
    // ui->ManagerLink->setTextInteractionFlags(Qt::TextBrowserInteraction);

    /*connect(ui->ManagerLink,&QLabel::linkActivated,this,&LoginWindow::onLinkActivated);*///连接管理员登录label
    // connect(ui->RegisterLink,&QLabel::linkActivated,this,&LoginWindow::onLinkActivated);//连接新用户注册label
    connect(ui->LoginButton, &QPushButton::clicked, this, &LoginWindow::on_LoginButton_clicked);//连接登录按钮
}

void LoginWindow::onLinkActivated(const QString &link) {
    qDebug() << "Link clicked: " << link;

    if (link == "manager") {
        // 执行管理员界面跳转操作
        this->hide();  // 隐藏当前窗口
        if (this->newWindow) {
            this->newWindow->show();  // 显示新窗口
        }//link在ui界面设置了，所以代码里没有
    } else {
        qDebug() << "其他链接：" << link;
    }
    if (link == "register") {
        // 执行注册界面跳转操作
        this->hide();  // 隐藏当前窗口
        if (this->newSignUpWindow) {
            this->newSignUpWindow->show();  // 显示新窗口
        }
    } else {
        qDebug() << "其他链接：" << link;
    }
}
LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    QString id = ui->UserNameLine->text();
    QString password = ui->PassWordLine->text();

    ui->lbl_name->setText("");
    ui->lbl_pwd->setText("");

    // DBOperator op;

    if (id.trimmed()=="") {
        ui->lbl_name->setText("账号不能为空！");
        ui->lbl_name->setStyleSheet("color:red");
        ui->UserNameLine->setFocus();
    }
    else if (password.trimmed()=="") {
        ui->lbl_pwd->setText("密码不能为空！");
        ui->lbl_pwd->setStyleSheet("color:red");
        ui->PassWordLine->setFocus();
    }
    if(op.DBpaFind(id.trimmed(),password.trimmed()))
    {
        this->hide();
        if (this->newHomePage) {
            this->newHomePage->show();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("账号或密码出错，请重新输入");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("登录失败");
        msgBox.exec();
    }
}



void LoginWindow::on_RegisterButton_clicked()
{
    this->hide();  // 隐藏当前窗口
    if (this->newSignUpWindow) {
        this->newSignUpWindow->show();  // 显示新窗口
    }
    else{
        this->newSignUpWindow=new registerWindow;
        this->newSignUpWindow->show();
    }
}


void LoginWindow::on_adLoginButton_clicked()
{
    this->hide();  // 隐藏当前窗口
    if (this->newWindow) {
        this->newWindow->show();  // 显示新窗口
    }//link在ui界面设置了，所以代码里没有
}


void LoginWindow::on_CancelButton_clicked()
{
    ui->UserNameLine->text()="";
    ui->PassWordLine->text()="";
}

void LoginWindow::setUserName(const QString &username) {
    ui->UserNameLine->setText(username);
}

void LoginWindow::setPassword(const QString &password) {
    ui->PassWordLine->setText(password);
}
