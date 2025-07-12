#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include<managerlogin.h>//管理员头文件
#include<managerwindow.h>
#include<registerwindow.h>
#include<homepage.h>
#include"DBOperator.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    // DBOperator op;
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    ManagerLogin *newWindow = NULL;//用于保存manager实例化地址
    ManagerWindow *newWindowManager = NULL;
    registerWindow *newSignUpWindow = NULL;
    HomePage *newHomePage = NULL;

public:
    void setUserName(const QString &username);
    void setPassword(const QString &password);

private slots:
    void onLinkActivated(const QString &link);
    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_adLoginButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
