#ifndef MODELDIALOG_H
#define MODELDIALOG_H

#include <QDialog>

namespace Ui {
class ModelDialog;
}

class ModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelDialog(QWidget *parent = 0);
    ~ModelDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

private:
    std::vector<int> idm;
    int cidm;
    void init();
    void setValues();
    Ui::ModelDialog *ui;
};

#endif // MODELDIALOG_H
