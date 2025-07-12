#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include "qpainter.h"
#include "qstackedwidget.h"
#include "qstyleditemdelegate.h"
#include "qtablewidget.h"
#include <QMainWindow>

namespace Ui {
class ManagerWindow;
}

// class CustomItemDelegate : public QStyledItemDelegate
// {
//     Q_OBJECT

// public:
//     explicit CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

//     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
//         QStyleOptionViewItem opt = option;
//         if (opt.state & QStyle::State_Selected) {
//             painter->setPen(QColor("blue"));
//         } else {
//             painter->setPen(QColor("black"));
//         }

//         // 调用父类的 paint 方法，绘制单元格
//         QStyledItemDelegate::paint(painter, opt, index);
//     }
// };

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();

    void flightquery();
    void userquery();

private slots:
    void on_userPageButton_clicked();

    void on_FlightPageButton_clicked();

    void on_exitButton_clicked();

    void on_flightlist_itemSelectionChanged();

    void on_cancelButton_clicked();

    void on_changeList_2_clicked();

    void on_deleteList_2_clicked();

    void on_NewList_2_clicked();

    void on_deleteList_clicked();

    void on_changeList_clicked();

    void on_userlist_itemSelectionChanged();

    void on_cancelBtn_clicked();

private:
    Ui::ManagerWindow *ui;
    QStackedWidget *stackedWidget;  // 添加 QStackedWidget 指针

    QWidget *flightPage;
    QWidget *userPage;

    QTableWidget *flightTable;
    QTableWidget *userTable;

//    CustomItemDelegate* delegate;
};

#endif // MANAGERWINDOW_H
