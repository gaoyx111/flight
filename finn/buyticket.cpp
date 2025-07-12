#include "buyticket.h"
#include "ui_buyticket.h"

void buyTicket::setticket(QString starttime,QString endtime)
{
    ui->beginTime_2->setText(starttime);
    ui->arrivalTime_2->setText(endtime);
}

buyTicket::buyTicket(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::buyTicket)
{
    ui->setupUi(this);
}

buyTicket::~buyTicket()
{
    delete ui;
}
