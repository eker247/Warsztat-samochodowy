#include "clientdialog.h"
#include "ui_clientdialog.h"

namespace {
KTable& table = MainWindow::table;
}

ClientDialog::ClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
{
    ui->setupUi(this);
    if (MainWindow::currentId >= 0)
        setValues();
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::setValues()
{
    Client& client = table.ClientById(MainWindow::currentId);
    ui->LEname->setText(client.name);
    ui->LEsurname->setText(client.surname);
    ui->LEphone->setText(QVariant(client.phone).toString());
    ui->LEnote->setText(client.note);
}

void ClientDialog::on_PBok_clicked()
{
    Client k;
    k.name = ui->LEname->text();
    k.surname = ui->LEsurname->text();
    k.phone = QVariant(ui->LEphone->text()).toInt();
    k.note = ui->LEnote->text();
    if (k.name == "" && k.surname == "" && k.phone == 0 && k.note == "")
    {
        QMessageBox::information(this, "Błędne dane", "Nie wprowadzono żadnych danych");
        return;
    }
    MainWindow::login.addClient(k, MainWindow::currentId);
    this->close();
}

void ClientDialog::on_PBanuluj_clicked()
{
    this->close();
}
