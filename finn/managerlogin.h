#ifndef MANAGERLOGIN_H
#define MANAGERLOGIN_H

#include <QWidget>
#include<managerwindow.h>
namespace Ui {
class ManagerLogin;
}

class ManagerLogin : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLogin(QWidget *parent = nullptr);
    ~ManagerLogin();

    ManagerWindow *newWindowManager = NULL;
private:
    Ui::ManagerLogin *ui;
signals:
    void managerloginClose();
private slots:
    void on_pushButton_clicked();

    void on_LoginButton_clicked();

    void on_CancelButton_clicked();

private:
    void closeEvent(QCloseEvent *){//重写关闭按钮事件
        emit managerloginClose();//发出关闭信号，父窗体接收信号后显示窗体
    }
};

#endif // MANAGERLOGIN_H
