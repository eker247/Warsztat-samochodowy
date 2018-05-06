#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_PBok_clicked();

    void on_PBcancel_clicked();

private:
    void init();
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
