#ifndef PLACEORDER_H
#define PLACEORDER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlaceOrder;
}
QT_END_NAMESPACE

class PlaceOrder : public QMainWindow
{
    Q_OBJECT

public:
    PlaceOrder(QWidget *parent = nullptr,QString randomNumberString="1");
    ~PlaceOrder();
    void passengerquery(QString randomNumberString);
    QString orderInfo;
    int panum=0;
    int checkprice;
    QString class_type;
    QString ep;
    QString bp;
    QString fp;

private slots:
    void on_choosePassenger_clicked();

    void on_choosePassenger_2_clicked();

    void on_subitOrder_clicked();

public slots:
    void close() {
        this->close();
    }

private:
    Ui::PlaceOrder *ui;
};
#endif // PLACEORDER_H
