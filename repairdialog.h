#ifndef NAPRAWADIALOG_H
#define NAPRAWADIALOG_H

#include <QDialog>

namespace Ui {
class RepairDialog;
}

class RepairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepairDialog(QWidget *parent = 0);
    ~RepairDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

private:
    std::vector<int> idc;
    int cidc;
    void init();
    void setValues();
    Ui::RepairDialog *ui;
};

#endif // NAPRAWADIALOG_H
