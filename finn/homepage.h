#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include<InfoWindow.h>
#include<checkWindow.h>
#include "ImageInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HomePage;
}
QT_END_NAMESPACE

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();
    QVector<ImageInfo> imageInfos;

private slots:
    void on_userInfoButton_clicked();

    void on_buyButton_clicked();

    void on_staffCenterButton_clicked();

    void closeAllWindows();


    void on_ticket1_clicked();

    void on_ticket2_clicked();

public slots:
    void refreshContent();

private:
    Ui::HomePage *ui;
};
#endif // HOMEPAGE_H
