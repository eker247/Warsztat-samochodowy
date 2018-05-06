#include "modeldialog.h"
#include "ui_modeldialog.h"
#include "mainwindow.h"

namespace {
KTable& table = MainWindow::table;
}

ModelDialog::ModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelDialog)
{
    ui->setupUi(this);
    init();
    if (MainWindow::currentId >= 0)
        setValues();
}

ModelDialog::~ModelDialog()
{
    delete ui;
}


void ModelDialog::init()
{
    ui->CBbrand->insertItem(0, "");

    idm.empty();
    int i = 1;
    for (auto& x: table.brand)
    {
        ui->CBbrand->insertItem(i++, x.name);
        idm.push_back(x.idbrand);
    }
}

void ModelDialog::setValues()
{
    Model& model = table.ModelById(MainWindow::currentId);
    ui->LEmodel->setText(model.name);

    int j = 0;
    for (auto& x: table.brand)
    {
        if (x.idbrand == model.idbrand)
            break;
        ++j;
    }
    ui->CBbrand->setCurrentIndex(j+1);
}

void ModelDialog::on_PBok_clicked()
{
    if (ui->CBbrand->currentIndex() == 0) {
        QMessageBox::information(this, "Nieprawidłowe dane", "Wybierz markę samochodu");
        return;
    }
    if (ui->LEmodel->text() == "") {
        QMessageBox::information(this, "Nieprawidłowe dane", "Wprowadź nazwę modelu");
        return;
    }
    cidm = ui->CBbrand->currentIndex();
    unsigned idmar;
    for (idmar = 0; (idmar < idm.size()); idmar++)
         if (idm[idmar] == cidm)
            break;
    Model m;
    m.idbrand = idmar + 1;
    m.name = ui->LEmodel->text();
    MainWindow::login.addModel(m, MainWindow::currentId);
    this->close();
}

void ModelDialog::on_PBanuluj_clicked()
{
    this->close();
}
