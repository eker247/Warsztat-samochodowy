#include "cardialog.h"
#include "ui_cardialog.h"
#include "mainwindow.h"

namespace {
KTable& table = MainWindow::table;
}

CarDialog::CarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarDialog)
{
    ui->setupUi(this);
    init();
    if (MainWindow::currentId >= 0)
        setValues();
}

CarDialog::~CarDialog()
{
    delete ui;
}

void CarDialog::init()
{
    int i = 1;

    ui->CBclient->insertItem(0, "");
    idk.clear();
    for (auto& x: table.client)
    {
        idk.push_back(x.idclient);
        QString client = x.surname + " " + x.name;
        ui->CBclient->insertItem(i++, client);
    }

    i = 1;
    ui->CBbrand->insertItem(0, "");
    idma.clear();
    for (auto& x: table.brand)
    {
        idma.push_back(x.idbrand);
        ui->CBbrand->insertItem(i++, x.name);
    }
}

void CarDialog::initModel(int index)
{
    int idbrand;
    if (index)
        idbrand = idma[index-1];
    else
        idbrand = -1;

    idmo.clear();
    ui->CBmodel->clear();
    int i = 1;
    ui->CBmodel->insertItem(0, "");
    for (auto& x: table.model)
    {
        if (x.idbrand == idbrand)
        {
            idmo.push_back(x.idmodel);
            ui->CBmodel->insertItem(++i, x.name);
        }
    }
}

void CarDialog::setValues()
{
    Car& car = table.CarById(MainWindow::currentId);
    unsigned i = 0;
    int idcar = car.idcar;
    int idclient = car.idclient;
    for ( ; (i < idk.size()); ++i)
    {
        if (idclient == idk[i])
            break;
    }
    ui->CBclient->setCurrentIndex(i+1);

    i = 0;
    int idmodel = car.idmodel;
    int idbrand = table.ModelById(car.idmodel).idbrand;
    for ( ; (i < idma.size()); ++i)
    {
        if (idbrand == idma[i])
            break;
    }
    ui->CBbrand->setCurrentIndex(i+1);

    i = 0;
    for ( ; (i < idmo.size()); ++i)
    {
        if (idmodel == idmo[i])
            break;
    }
    ui->CBmodel->setCurrentIndex(i+1);
    ui->LEyear->setText(QVariant(car.year).toString());
    ui->LEgeneration->setText(car.generation);
    ui->LEengine->setText(car.engine);
}

void CarDialog::on_PBok_clicked()
{
    if (!ui->CBclient->currentIndex()) {
        QMessageBox::information(this, "Błędne dane", "Pole client nie może być puste");
        return;
    }
    if (!ui->CBmodel->currentIndex()) {
        QMessageBox::information(this, "Błędne dane", "Pole model nie może być puste");
        return;
    }
    Car s;
    s.idclient = idk[ui->CBclient->currentIndex()-1];
    s.idmodel = idmo[ui->CBmodel->currentIndex()-1];
    s.generation = ui->LEgeneration->text();
    s.engine = ui->LEengine->text();
    s.year = QVariant(ui->LEyear->text()).toInt();
    MainWindow::login.addCar(s, MainWindow::currentId);

    this->close();
}

void CarDialog::on_PBanuluj_clicked()
{
    this->close();
}

void CarDialog::on_CBbrand_currentIndexChanged(int index)
{
    // qDebug() << "Ruszyło initModel(" << index << ")";
    initModel(index);
}
