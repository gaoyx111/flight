#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>


namespace Ui {
class registerWindow;
}

class registerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit registerWindow(QWidget *parent = nullptr);
    ~registerWindow();

    QString generateRandom();

private slots:
    void on_LoginButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::registerWindow *ui;
signals:
    void registerClose();
private:
    void closeEvent(QCloseEvent *){//重写关闭按钮事件
        emit registerClose();//发出关闭信号，父窗体接收信号后显示窗体
    }
};

#endif // REGISTERWINDOW_H
