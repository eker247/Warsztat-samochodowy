#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    init();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::init()
{
    ui->LEip->setText("127.0.0.1");
    ui->LEuser->setText("root");
    ui->LEpassword->setEchoMode(QLineEdit::Password);
    ui->LEpassword->setText("1234");
    ui->LEdb->setText("warsztat");

}

void LoginDialog::on_PBok_clicked()
{
//    MainWindow::login.ip = ui->LEip->text();
//    MainWindow::login.username = ui->LEuser->text();
//    MainWindow::login.password = ui->LEpassword->text();
//    MainWindow::login.datebase = ui->LEdb->text();
//    if (MainWindow::login.ip == "")
//    {
//        QMessageBox::information(this, "Błędne dane", "Podaj adres ip serwera");
//        return;
//    }
//    if (MainWindow::login.username == "")
//    {
//        QMessageBox::information(this, "Błędne dane", "Wprowadź nazwę użytkownika");
//        return;
//    }
//    if (MainWindow::login.password == "")
//    {
//        QMessageBox::information(this, "Błędne dane", "Podaj hasło");
//        return;
//    }
//    if (MainWindow::login.datebase == "")
//    {
//        QMessageBox::information(this, "Błędne dane", "Wprowadź nazwę bazy danych");
//        return;
//    }
//    this->close();
}

void LoginDialog::on_PBcancel_clicked()
{
    this->close();
}
