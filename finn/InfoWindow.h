#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "qscrollarea.h"
#include "qstackedwidget.h"
#include "ticket.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class InfoWindow;
}
QT_END_NAMESPACE

class InfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();
    void updatename(QString newname,QString newnick,QString newgender,QString bir,QString id);
    void refreshCouponPage();
    void showboughtticket(QScrollArea *scroller);
    void makepa();
    void deletePassenger(const QString &otherid);
    void deletticket(QScrollArea *scroller);
private slots:

    void on_PersonInfo_clicked();

    void on_order_clicked();

    void on_coupon_clicked();

    void on_TravelerInfo_clicked();

    void on_BackButton_clicked();

    void on_EditButton_9_clicked();

    void on_okbutton_clicked();

    void on_cancelbtn_clicked();

    void on_changebtn_clicked();

    void on_addbtn_clicked();

    void on_exitBtn_clicked();

    void on_allbtn_clicked();

    void on_gobtn_clicked();

    void on_paybtn_clicked();

    void on_finish_clicked();

public slots:
    void onModifyButtonClicked();
    void onDeleteButtonClicked();
    void onCancelButtonClicked(const QString& ticketNumber,QScrollArea*scroller);
    void ondetailButtonClicked(const QString& ticketNumber);
    void onChangeButtonClicked(const QString& ticketNumber);
    void onPayButtonClicked(const QString& ticketNumber);
    void onButtonClicked(const QString& ticketNumber,QScrollArea *scroller);
signals:
    void closeAllWindows();
    void returnToHome();

private:
    Ui::InfoWindow *ui;
    QStackedWidget *stackedWidget;  // 添加 QStackedWidget 指针

    QWidget *personInfoPage;
    QWidget *orderPage;
    QWidget *couponPage;
    QWidget *travelerInfoPage;
    QWidget *infoPage;

};
#endif // INFOWINDOW_H
