#include "managerlogin.h"
#include "loginwindow.h"
#include "ui_managerlogin.h"
#include<DBOperator.h>
#include<QMessageBox>

extern DBOperator op;
ManagerLogin::ManagerLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerLogin)
{
    ui->setupUi(this);
    this->newWindowManager = new ManagerWindow;
    ui->M_PassWordLine->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton,&QPushButton::clicked,this,&ManagerLogin::close);
}

ManagerLogin::~ManagerLogin()
{
    delete ui;
}

void ManagerLogin::on_pushButton_clicked()
{
    this->close();
    LoginWindow* lw=new LoginWindow();
    lw->show();
}


void ManagerLogin::on_LoginButton_clicked()
{
    QMessageBox msgBox;

    DBOperator op;
    QString id = ui->ManagerNameLine->text();
    QString password = ui->M_PassWordLine->text();

    ui->lbl_ID->setText("");
    ui->lbl_pass->setText("");


    if (id.trimmed()=="") {
        ui->lbl_ID->setText("账号不能为空！");
        ui->lbl_ID->setStyleSheet("color:red");
        ui->ManagerNameLine->setFocus();
    }
    else if (password.trimmed()=="") {
        ui->lbl_pass->setText("密码不能为空！");
        ui->lbl_pass->setStyleSheet("color:red");
        ui->M_PassWordLine->setFocus();
    }
    if(op.DBadFind(id.trimmed(),password.trimmed()))
    {
        this->hide();  // 隐藏当前窗口
        if (this->newWindowManager) {
            this->newWindowManager->show();  // 显示新窗口
        }
    }
    else
    {
        msgBox.setText("账号或密码出错，请重新输入");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("登录失败");
        msgBox.exec();
    }
}


void ManagerLogin::on_CancelButton_clicked()
{
    ui->lbl_ID->setText("");
    ui->lbl_pass->setText("");
}

