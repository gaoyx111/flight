#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include "qboxlayout.h"
#include "qdialog.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qradiobutton.h"
#include "placeorder.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
extern QString num;

class PaymentSuccessDialog : public QDialog {
    Q_OBJECT
public:
    PaymentSuccessDialog(const QVector<QString> &seatNumbers, QWidget *parent)
        : QDialog(parent) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QLabel *successLabel = new QLabel("支付成功！", this);
        successLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(successLabel);

        QLabel *seatLabel = new QLabel("您的座位号：", this);
        mainLayout->addWidget(seatLabel);

        QString seatNumbersStr = seatNumbers.join(", ");
        QLabel *seatNumbersLabel = new QLabel(seatNumbersStr, this);
        mainLayout->addWidget(seatNumbersLabel);

        QPushButton *okButton = new QPushButton("确定", this);
        mainLayout->addWidget(okButton);

        connect(okButton, &QPushButton::clicked, this, &PaymentSuccessDialog::accept);

        setWindowTitle("支付成功");
        resize(300, 200);

        // 更新数据库中的票状态
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen()) {
            QSqlQuery query;
            query.exec("USE flight");
            query.exec("SET SQL_SAFE_UPDATES = 0;");
            query.prepare("UPDATE ticket SET status = 1 WHERE ticketnum = :tn");
            query.bindValue(":tn", num);
            if (!query.exec()) {
                qDebug() << "更新票状态失败: " << query.lastError().text();
            } else {
                qDebug() << "票状态更新成功";
            }
        } else {
            qDebug() << "数据库未打开";
        }
    }
};

class PaymentDialog : public QDialog {
    Q_OBJECT
public:
    PaymentDialog(const QString &orderInfo, const int &panum, const double &checkprice, QWidget *parent = nullptr)
        : QDialog(parent), panum(panum), checkprice(checkprice) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QLabel *orderInfoLabel = new QLabel("订单信息：", this);
        mainLayout->addWidget(orderInfoLabel);
        QLabel *orderDetailsLabel = new QLabel(orderInfo, this);
        orderDetailsLabel->setWordWrap(true);
        mainLayout->addWidget(orderDetailsLabel);

        QLabel *passengerLabel = new QLabel(QString("乘机人数: %1").arg(panum), this);
        mainLayout->addWidget(passengerLabel);

        QLabel *priceLabel = new QLabel(QString("票价: ¥%1").arg(checkprice), this);
        mainLayout->addWidget(priceLabel);

        QHBoxLayout *paymentLayout = new QHBoxLayout();
        QRadioButton *creditCardButton = new QRadioButton("信用卡支付", this);
        QRadioButton *alipayButton = new QRadioButton("支付宝支付", this);
        QRadioButton *wechatPayButton = new QRadioButton("微信支付", this);

        paymentLayout->addWidget(creditCardButton);
        paymentLayout->addWidget(alipayButton);
        paymentLayout->addWidget(wechatPayButton);

        mainLayout->addLayout(paymentLayout);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QPushButton *confirmButton = new QPushButton("确认支付", this);
        QPushButton *cancelButton = new QPushButton("取消支付", this);

        buttonLayout->addWidget(confirmButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);

        creditCardButton->setChecked(true);

        connect(confirmButton, &QPushButton::clicked, this, &PaymentDialog::confirmPayment);
        connect(cancelButton, &QPushButton::clicked, this, &PaymentDialog::cancelPayment);

        resize(400, 250);
    }

signals:
    void paymentSuccess();

public slots:
    void confirmPayment() {
        QVector<QString> seatNumbers;

        QString selectedClass = class_type;
        int startRow = 0;
        char seatLetter = 'A';

        if (selectedClass == "经济舱") {
            startRow = 32;
        } else if (selectedClass == "商务舱") {
            startRow = 10;
        } else if (selectedClass == "头等舱") {
            startRow = 1;
        }

        int remainingSeats = panum;
        int seatsPerRow = 4;

        while (remainingSeats > 0) {
            for (int i = 0; i < seatsPerRow && remainingSeats > 0; ++i) {
                QString seat = QString("%1%2").arg(startRow).arg(seatLetter);
                seatNumbers.append(seat);
                seatLetter++;

                remainingSeats--;

                if (seatLetter > 'D') {
                    seatLetter = 'A';
                    startRow++;
                }
            }
        }
        PaymentSuccessDialog *successDialog = new PaymentSuccessDialog(seatNumbers, this);
        connect(successDialog, &PaymentSuccessDialog::accepted, this, &PaymentDialog::onPaymentSuccess);
        successDialog->exec();
    }

    void cancelPayment() {
        close();
        if (parentWidget()) {
            parentWidget()->close();
        }
    }

    void onPaymentSuccess() {
        close();
        if (parentWidget()) {
            parentWidget()->close();
        }
    }

private:
    int panum;
    double checkprice;
public:
    QString class_type;
};



#endif // PAYMENTDIALOG_H
