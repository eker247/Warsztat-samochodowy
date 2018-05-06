#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include <QStringList>
#include "tabele.h"

//#include "logindialog.h"
#include "partdialog.h"
#include "exploitationdialog.h"
#include "clientdialog.h"
#include "branddialog.h"
#include "modeldialog.h"
#include "repairdialog.h"
#include "cardialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static std::vector<int> id; // pointer to KTable.Class
    static int currentId;       // chosen entity
    static Login login;         // datebase connect, disconnect, select
    static KTable table;        // all date in datebase
    static MainWindow* MWptr;   // pointer to MainWindow
    static bool isConnected;
    static enumTable chosenTable;
    explicit MainWindow(QWidget *parent = 0);
    void connectDB();
    ~MainWindow();

private slots:
    void on_ACpolacz_triggered();

    void on_ACrozlacz_triggered();

    void on_ACpart_triggered();

    void on_ACexploitation_triggered();

    void on_ACclient_triggered();

    void on_ACbrand_triggered();

    void on_ACmodel_triggered();

    void on_ACrepair_triggered();

    void on_ACcar_triggered();

    void on_PBdodaj_clicked();

    void on_PBaktualizuj_clicked();

    void on_PBusun_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    void run_polacz();
    void run_rozlacz();
    void run_part();
    void run_exploitation();
    void run_client();
    void run_brand();
    void run_model();
    void run_repair();
    void run_car();
    void run_dodaj();
    void run_aktualizuj();
    void run_usun();

    void list_repair();

    void addPart();
    void addExploitation();
    void addClient();
    void addBrand();
    void addModel();
    void addRepair();
    void addCar();

    void deletePart();
    void deleteExploitation();
    void deleteClient();
    void deleteBrand();
    void deleteModel();
    void deleteRepair();
    void deleteCar();
    bool sure();

};

#endif // MAINWINDOW_H
