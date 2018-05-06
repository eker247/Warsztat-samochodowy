#ifndef KLIENTDIALOG_H
#define KLIENTDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

private:
    void setValues();
    Ui::ClientDialog *ui;
};

#endif // KLIENTDIALOG_H
