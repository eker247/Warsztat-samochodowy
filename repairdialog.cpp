#include "repairdialog.h"
#include "ui_repairdialog.h"
#include "mainwindow.h"

namespace {
KTable& table = MainWindow::table;
}

RepairDialog::RepairDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepairDialog)
{
    ui->setupUi(this);
    init();
    if (MainWindow::currentId >= 0)
        setValues();
}

RepairDialog::~RepairDialog()
{
    delete ui;
}


void RepairDialog::init()
{
    idc.empty();
    int i = 1;
    for (auto& x: table.car)
    {
        idc.push_back(x.idcar);
        QString car =
                table.ClientById(x.idclient).surname + " " +
                table.ClientById(x.idclient).name + " - " +
                table.BrandById(table.ModelById(x.idmodel).idbrand).name + " " +
                table.ModelById(x.idmodel).name;
        ui->CBcar->insertItem(i++, car);
    }
    ui->LEprice->setValidator(new QDoubleValidator(0.0, 100000.1, 2, this));
    ui->DEid->setDisplayFormat("yyyy-MM-dd");
    ui->DEout->setDisplayFormat("yyyy-MM-dd");
    ui->DEid->setDate(QDate::currentDate());
    ui->DEout->setDate(QDate::currentDate());   // fromString("    -  -  ", "yyyy-MM-dd"
}

void RepairDialog::setValues()
{
    Repair& repair = table.RepairById(MainWindow::currentId);
    for (unsigned i = 0; i < idc.size(); ++i) {
        if (idc[i] == repair.idcar) {
            ui->CBcar->setCurrentIndex(++i);
            break;
        }
    }
    ui->TEdesc->setText(repair.desc.replace("~n", "\n"));
    ui->LEprice->setText(QString::number(repair.repair_price, 'f', 2));
    ui->LEnote->setText(repair.note);
    ui->DEid->setDate(QDate::fromString(repair.indate, "yyyy-MM-dd"));
    ui->DEout->setDate(QDate::fromString(repair.outdate, "yyyy-MM-dd"));
}

void RepairDialog::on_PBok_clicked()
{
    Repair n;
    n.idcar = idc[ui->CBcar->currentIndex()-1];
    if (n.idcar < 1) {
        QMessageBox::information(this, "Puste pole", "Wybierz naprawiany samochód.");
        return;
    }
    n.desc = ui->TEdesc->toPlainText().replace("\n", "~n");// text();
    n.indate = ui->DEid->text();
    n.outdate = ui->DEout->text();
    n.repair_price = QVariant(ui->LEprice->text().replace("," , ".")).toFloat();
    n.note = ui->LEnote->text();
    MainWindow::login.addRepair(n, MainWindow::currentId);
    this->close();
}

void RepairDialog::on_PBanuluj_clicked()
{
    this->close();
}
