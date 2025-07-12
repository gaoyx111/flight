#include"registerwindow.h"
#include "loginwindow.h"
#include "qrandom.h"
#include "qsqlerror.h"
#include "ui_registerwindow.h"
#include<DBOperator.h>
#include<QString>
#include<QMessageBox>
extern DBOperator op;
QString randomString;

registerWindow::registerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerWindow)
{
    ui->setupUi(this);

    randomString = generateRandom();

//    connect(ui->LoginButton,&QPushButton::clicked,this,&registerWindow::close);

}

registerWindow::~registerWindow()
{
    delete ui;
}

QString registerWindow::generateRandom() {
    QRandomGenerator *generator = QRandomGenerator::global();
    int a = generator->bounded(10);
    int b = generator->bounded(10);
    int c = generator->bounded(10);
    int d = generator->bounded(10);
    QString s = QString("%1%2%3%4").arg(a).arg(b).arg(c).arg(d);
//    qDebug() << "Generated verification code: " << s;

    ui->verLabel->setText(s);
    ui->verLabel->setVisible(true);  // 确保verLabel可见
    return s;
}

void registerWindow::on_LoginButton_clicked() {
    ui->idnote->setText("");
    ui->namenote->setText("");
    ui->passnote->setText("");
    ui->senote->setText("");
    ui->vernote->setText("");

    QString name = ui->UserNameLine->text();
    QString password = ui->PassWordLine->text();
    QString password2 = ui->PassWordLine_2->text();
    QString phonenum = ui->phoneLine->text();
    QString ver = ui->verLine->text();
    qDebug() << "注册ing";

    // 输入验证
    if (name.trimmed() == "") {
        ui->namenote->setText("用户名不能为空！");
        ui->namenote->setStyleSheet("color:red");
        ui->UserNameLine->setFocus();
        return;
    } else if (password.trimmed() == "") {
        ui->passnote->setText("密码不能为空！");
        ui->passnote->setStyleSheet("color:red");
        ui->PassWordLine->setFocus();
        return;
    } else if (password2 != password) {
        ui->senote->setText("两次输入的密码不同，请重新输入");
        ui->senote->setStyleSheet("color:red");
        ui->PassWordLine_2->setFocus();
        return;
    } else if(phonenum.trimmed() == "") {
        ui->idnote->setText("您的ID不能为空！");
        ui->idnote->setStyleSheet("color:red");
        ui->phoneLine->setFocus();
        return;
    } else if(phonenum.trimmed().size()!=11){
        ui->idnote->setText("请输入有效的手机号");
        ui->idnote->setStyleSheet("color:red");
        ui->phoneLine->setFocus();
        return;
    } else if (ver != randomString) {
        ui->vernote->setText("验证码输入错误，请重新输入");
        ui->vernote->setStyleSheet("color:red");
        randomString = generateRandom();
        ui->verLine->setFocus();
        return;
    }

    // 检查用户是否已存在
    QSqlQuery checkQuery;
    checkQuery.exec("USE flight");
    checkQuery.prepare("SELECT * FROM passenger WHERE passenger_id = :phone");
    checkQuery.bindValue(":phone", phonenum.trimmed());

    if (checkQuery.exec()) {
        if (checkQuery.next()) {
            // 用户已存在
            QMessageBox msgBox;
            msgBox.setText("该用户已存在！");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("注册失败");
            msgBox.exec();
            ui->UserNameLine->setFocus();
        } else {
            // 用户不存在，插入新的用户数据到数据库
            QSqlQuery insertQuery;
            insertQuery.exec("USE flight");
            insertQuery.prepare("INSERT INTO passenger (passenger_name, passenger_password, passenger_id, passenger_nickname) VALUES (:username, :password, :phone, :nickname)");
            insertQuery.bindValue(":username", name.trimmed());
            insertQuery.bindValue(":password", password.trimmed());
            insertQuery.bindValue(":phone", phonenum.trimmed());
            insertQuery.bindValue(":nickname", "用户"+generateRandom());

            if (insertQuery.exec()) {
                // 注册成功后关闭当前窗口
                this->close();
                LoginWindow *lw = new LoginWindow();
                lw->setUserName(phonenum);
                lw->setPassword(password);
                lw->show();
            } else {
                // 插入失败时弹出提示框
                QMessageBox msgBox;
                msgBox.setText("注册失败，请稍后重试！");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("注册失败");
                msgBox.exec();
            }
        }
    } else {
        // 查询失败时的处理
        qDebug() << "查询失败: " << checkQuery.lastError();
        QMessageBox msgBox;
        msgBox.setText("数据库查询失败，请稍后再试！");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("错误");
        msgBox.exec();
    }
}


void registerWindow::on_BackButton_clicked()
{
    this->hide();
    LoginWindow* lw=new LoginWindow();
    lw->show();
}
