#ifndef CUSTOMERSERVICEPAGE_H
#define CUSTOMERSERVICEPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CustomerServicePage;
}
QT_END_NAMESPACE

class CustomerServicePage : public QMainWindow
{
    Q_OBJECT

public:
    CustomerServicePage(QWidget *parent = nullptr);
    ~CustomerServicePage();

private slots:
    void on_Q1_clicked();

    void on_Q2_clicked();

    void on_Q3_clicked();

    void on_Q4_clicked();

    void on_Q4_2_clicked();

private:
    Ui::CustomerServicePage *ui;
};
#endif // CUSTOMERSERVICEPAGE_H
