#ifndef DETAIL_H
#define DETAIL_H

#include "qdialog.h"
#include <QWidget>

namespace Ui {
class detail;
}

class detail : public QDialog {
    Q_OBJECT

public:
    explicit detail(QWidget *parent = nullptr);
    ~detail();
    void showdetail();
protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closed();
public slots:
    void onSureButtonClicked();
private:
    Ui::detail *ui;
};

#endif // DETAIL_H
