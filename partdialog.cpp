#include "partdialog.h"
#include "ui_partdialog.h"
#include "mainwindow.h"

namespace {
KTable& table = MainWindow::table;
}

PartDialog::PartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PartDialog)
{
    ui->setupUi(this);
    init();
}

void PartDialog::init()
{
    ui->LEprice->setValidator(new QDoubleValidator(0.1, 100000.1, 2, this));
    if (MainWindow::currentId > -1)
    {
        Part& part = table.PartById(MainWindow::currentId);
        ui->LEidrepair->setText(QVariant(part.idrepair).toString());
        ui->LEname->setText(part.name);
        ui->LEprice->setText(QString::number(part.price, 'f', 2));
        ui->LEnote->setText(part.note);
    }
}

PartDialog::~PartDialog()
{
    delete ui;
}

void PartDialog::on_PBok_clicked()
{
    QString cen = ui->LEprice->text().replace(",", ".");
    cen = QString::number(QVariant(cen).toDouble(), 'f', 2);
    Part part;
    part.idrepair = QVariant(ui->LEidrepair->text()).toInt();
    part.name = ui->LEname->text();
    part.price = QVariant(cen).toFloat();
    part.note = ui->LEnote->text();

    MainWindow::login.addPart(part, MainWindow::currentId);
    this->close();
}

void PartDialog::on_PBanuluj_clicked()
{
    this->close();
}
