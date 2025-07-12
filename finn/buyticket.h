#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class buyTicket;
}
QT_END_NAMESPACE

class buyTicket : public QMainWindow
{
    Q_OBJECT

public:
    buyTicket(QWidget *parent = nullptr);
    ~buyTicket();
    void setticket(QString starttime,QString endtime);
private:
    Ui::buyTicket *ui;
};
#endif // BUYTICKET_H
