#ifndef SAMOCHODDIALOG_H
#define SAMOCHODDIALOG_H

#include <QDialog>

namespace Ui {
class CarDialog;
}

class CarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CarDialog(QWidget *parent = 0);
    ~CarDialog();

private slots:
    void on_PBok_clicked();

    void on_PBanuluj_clicked();

    void on_CBbrand_currentIndexChanged(int index);
    
private:
    std::vector<int> idk;
    std::vector<int> idmo;
    std::vector<int> idma;
    void init();
    void initModel(int index);
    void setValues();
    void setModel();
    Ui::CarDialog *ui;
};

#endif // SAMOCHODDIALOG_H
