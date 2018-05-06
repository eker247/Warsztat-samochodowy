#ifndef CZESCDIALOG_H
#define CZESCDIALOG_H

#include <QDialog>

namespace Ui {
class PartDialog;
}

class PartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PartDialog(QWidget *parent = 0);
    ~PartDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

private:
    int i;
    Ui::PartDialog *ui;
    void init();
};

#endif // CZESCDIALOG_H
