#ifndef MARKADIALOG_H
#define MARKADIALOG_H

#include <QDialog>

namespace Ui {
class BrandDialog;
}

class BrandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrandDialog(QWidget *parent = 0);
    ~BrandDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

private:
    void setValues();
    Ui::BrandDialog *ui;
};

#endif // MARKADIALOG_H
