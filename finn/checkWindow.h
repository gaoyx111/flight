#ifndef CHECKWINDOW_H
#define CHECKWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QVBoxLayout>
#include<QStackedWidget>
#include<QComboBox>
#include<QScrollArea>
#include<flight.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class checkWindow;
}
QT_END_NAMESPACE

class checkWindow : public QMainWindow
{
    Q_OBJECT
    QStringList startcity;
    QStringList endcity;
    QStringList stopcity;
    // QComboBox *fromplace =new QComboBox;
    // QComboBox *toplace = new QComboBox;
public:
    bool layout1Added = false;
    checkWindow(QWidget *parent = nullptr);
    ~checkWindow();
    void setstartcity();
    void setstopcity();
    void setendcity();
    void showflight();
    void maketicket(QString startcity,QString stopcity,QString endcity,QString godate,QScrollArea *scroller);
    void makesmallticket(QString startcity,QString stopcity,QString endcity,QString godate,QScrollArea *scroller);
    void deletticket(QScrollArea *scroller);
    void addFlightInfoToLayout();

signals:
    void checkClose();
private:
    Ui::checkWindow *ui;
    QStackedWidget *stackedWidget;  // 添加 QStackedWidget 指针

    QWidget *TicketPage;
    QWidget *RefundPage;
    QWidget *changePage;
// public:
//     QString m_flightId;
//     QString m_cabinClass;
//     flight m_selectedFlight;
public slots:
    void onBuyButtonClickedSlot(QString m_flightId,QString m_cabinClass,flight m_selectFlight);
    void onShowDetailButtonClickedSlot(flight m_selectFlight);
    void onDepartureDateChanged(const QDate &date);
private slots:


    void on_TicketButton_clicked();

    void on_BackButton_clicked();



    bool oncheckButtonClicked();
    void on_checkButton_clicked();
    void on_sigle_clicked();

    void on_goandback_clicked();

    void on_pushButton_clicked();

private:
    void closeEvent(QCloseEvent *){//重写关闭按钮事件
        emit checkClose();//发出关闭信号，父窗体接收信号后显示窗体
    }
};
#endif // CHECKWINDOW_H



