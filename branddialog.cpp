#include "branddialog.h"
#include "ui_branddialog.h"
#include "mainwindow.h"

namespace {
KTable& table = MainWindow::table;
}

BrandDialog::BrandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrandDialog)
{
    ui->setupUi(this);
    if (MainWindow::currentId >= 0)
        setValues();
}

BrandDialog::~BrandDialog()
{
    delete ui;
}

void BrandDialog::setValues()
{
    Brand& brand = table.BrandById(MainWindow::currentId);
    ui->LEbrand->setText(brand.name);
}

void BrandDialog::on_PBok_clicked()
{
    Brand m;
    m.name = ui->LEbrand->text();
    if (m.name == "") 
    {
        QMessageBox::information(this, "Brak danych", "Nie podano nazwy marki");
        return;
    }
    MainWindow::login.addBrand(m, MainWindow::currentId);
    this->close();
}

void BrandDialog::on_PBanuluj_clicked()
{
    this->close();
}
