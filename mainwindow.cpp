#include "mainwindow.h"
#include "ui_mainwindow.h"

std::vector<int> MainWindow::id;
int MainWindow::currentId = -1;
Login MainWindow::login;
KTable MainWindow::table;
enumTable MainWindow::chosenTable = Tnull;
MainWindow* MainWindow::MWptr;
bool MainWindow::isConnected = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connectDB();
    login.selectAll(table);
    this->setWindowTitle("Warsztat");
    chosenTable = Tnull;
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget->setSortingEnabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPart() // wywyołuje okno dialogowe PartDialog
{
    PartDialog d;          // korzystając ze stosu wybrane okno musi być zawsze na wierzchu
    d.setWindowTitle("Części");
    d.setModal(true);
    d.exec();               // otwiera okno
    login.selectPart(table.part); // łączy z bazą danych o pobranych danych
    run_part();            // w tabeli głównego okna ustawia dane o częściach carów
}

void MainWindow::addExploitation()
{
    ExploitationDialog d;
    d.setWindowTitle("Eksploatacja");
    d.setModal(true);
    d.exec();
    table.exploitation.clear();
    login.selectExploitation(table.exploitation);
    run_exploitation();
}

void MainWindow::addClient()
{
    ClientDialog d;
    d.setWindowTitle("Klient");
    d.setModal(true);
    d.exec();
    login.selectClient(table.client);
    run_client();
}

void MainWindow::addBrand()
{
    BrandDialog d;
    d.setWindowTitle("Marka");
    d.setModal(true);
    d.exec();
    login.selectBrand(table.brand);
    run_brand();
}

void MainWindow::addModel()
{
    ModelDialog d;
    d.setWindowTitle("Model");
    d.setModal(true);
    d.exec();
    login.selectModel(table.model);
    run_model();
}

void MainWindow::addRepair()
{
    RepairDialog d;
    d.setWindowTitle("Naprawa");
    d.setModal(true);
    d.exec();
    login.selectRepair(table.repair);
    run_repair();
}

void MainWindow::addCar()
{
    CarDialog d;
    d.setWindowTitle("Samochód");
    d.setModal(true);
    d.exec();
    login.selectCar(table.car);
    run_car();
}

bool MainWindow::sure()
{
    QMessageBox msgBox(
                QMessageBox::Question,
                "Usuwanie elementu",
                "Czy na pewno chcesz usunąć element z listy?",
                QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, "Tak");  // ustawia etykietę przycisku
    msgBox.setButtonText(QMessageBox::No, "Nie");
    return (QMessageBox::Yes == msgBox.exec());     // wywołuje wiadomość o podanych parametrach
}

void MainWindow::deletePart()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deletePart(id[currentId]);
        unsigned i = 0;
        std::vector<Part> tmp;
        for (; table.part[i].idpart != id[currentId]; ++i) {
            tmp.push_back(table.part[i]);
        }
        for (++i; i < table.part.size(); ++i) {
            tmp.push_back(table.part[i]);
        }
        table.part.clear();
        table.part = std::move(tmp);
        run_part();
    }
}


void MainWindow::deleteExploitation()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteExploitation(id[currentId]);    // usuwa z bazy danych wpis o odpowiednim id
        // usuwa pozycję z KTable table
        unsigned i = 0;
        std::vector<Exploitation> tmp;
        for (; table.exploitation[i].idexploitation != id[currentId]; ++i) {
            tmp.push_back(table.exploitation[i]);
        }
        for (++i; i < table.exploitation.size(); ++i) {
            tmp.push_back(table.exploitation[i]);
        }
        table.exploitation.clear();
        table.exploitation = std::move(tmp);
        run_exploitation();                         // odświeża widok
    }
}

void MainWindow::deleteClient()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteClient(id[currentId]);
        unsigned i = 0;
        std::vector<Client> tmp;
        for (; table.client[i].idclient != id[currentId]; ++i) {
            tmp.push_back(table.client[i]);
        }
        for (++i; i < table.client.size(); ++i) {
            tmp.push_back(table.client[i]);
        }
        table.client.clear();
        table.client = std::move(tmp);
        run_client();
    }
}

void MainWindow::deleteBrand()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteBrand(id[currentId]);
        unsigned i = 0;
        std::vector<Brand> tmp;
        for (; table.brand[i].idbrand != id[currentId]; ++i) {
            tmp.push_back(table.brand[i]);
        }
        for (++i; i < table.brand.size(); ++i) {
            tmp.push_back(table.brand[i]);
        }
        table.brand.clear();
        table.brand = std::move(tmp);
        run_brand();
    }
}

void MainWindow::deleteModel()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteModel(id[currentId]);
        unsigned i = 0;
        std::vector<Model> tmp;
        for (; table.model[i].idmodel != id[currentId]; ++i) {
            tmp.push_back(table.model[i]);
        }
        for (++i; i < table.model.size(); ++i) {
            tmp.push_back(table.model[i]);
        }
        table.model.clear();
        table.model = std::move(tmp);
        run_model();
    }
}

void MainWindow::deleteRepair()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteRepair(id[currentId]);
        unsigned i = 0;
        std::vector<Repair> tmp;
        for (; table.repair[i].idrepair != id[currentId]; ++i) {
            tmp.push_back(table.repair[i]);
        }
        for (++i; i < table.repair.size(); ++i) {
            tmp.push_back(table.repair[i]);
        }
        table.repair.clear();
        table.repair = std::move(tmp);
        run_repair();
    }
}

void MainWindow::deleteCar()
{
    if (currentId < 0)
        QMessageBox::information(this, "Nie wybrano pozycji do usunięcia", "Musisz zaznaczyć pozycję, którą chcesz usunąć z listy");
    else if(sure())
    {
        login.deleteCar(id[currentId]);
        unsigned i = 0;
        std::vector<Car> tmp;
        for (; table.car[i].idcar != id[currentId]; ++i) {
            tmp.push_back(table.car[i]);
        }
        for (++i; i < table.car.size(); ++i) {
            tmp.push_back(table.car[i]);
        }
        table.car.clear();
        table.car = std::move(tmp);
        run_car();
    }
}

void MainWindow::run_polacz()
{
//    LoginDialog d;
//    d.setWindowTitle("Logowanie");
//    d.setModal(true);
//    d.exec();
//    if (!(login.connect()))
//    {
//        QMessageBox::information(this, "Błąd połączenia:", "Nie połączono z bazą danych");
//        isConnected = false;
//    }
//    else
//    {
//        login.selectAll(table);
//        isConnected = true;
//    }
    currentId = -1;
}

void MainWindow::run_rozlacz()
{
//    login.disconnect();                 // przerywa połączenie z bazą danych
    isConnected = false;                // informacja o przerwanym połączeniu
    table.clear();                      // wyczyszczenie tablicy
    this->setWindowTitle("Warsztat");   // ustawienie tytyłu głównego okna
    chosenTable = Tnull;                // brak wybranej kategorii
    ui->tableWidget->setRowCount(0);    // widok ma 0 wierszy
    ui->tableWidget->setColumnCount(0); // widok ma 0 kolumn
    ui->tableWidget->clear();           // usuwa wpisy z widoku
}

void MainWindow::run_part()
{
/*    if (!isConnected)
        return;*/                                                 // jeśli brak połączenia kończy funkcję
    this->setWindowTitle("Warsztat - Części");
    chosenTable = Tpart;                                       // ustawia wybraną kategorię
    QStringList labels;
    labels << "Naprawa" << "Nazwa" << "Cena" << "Notatka";   // nagłówki wyświetlanych kolumn
    ui->tableWidget->setColumnCount(4);                         // liczba kolumn
    ui->tableWidget->setRowCount(table.part.size());           // liczba wierszy
    ui->tableWidget->setHorizontalHeaderLabels(labels);         // zaznaczanie wierszy a nie komórek
    id.clear();                                                 // czyszczenie vectora z id pozycji
    id.resize(table.part.size());                              // przygotowanie vectora do pomieszczenia pozycji
    int i = 0;
    for (auto& x: table.part)
    {
        id[i] = x.idpart;                                        // id koilnych elementów
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QVariant(x.idrepair).toString()));  // wstawianie treści
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(x.name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(x.price, 'f', 2)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(x.note));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 80);     // szeyearość klumny
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->setColumnWidth(3, 150);
}

void MainWindow::run_exploitation()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Eksploatacja");
    chosenTable = Texploitation;
    QStringList labels;
    labels << "Nazwisko" << "Imię" << "Marka" << "Model" << "Olej" << "Filtr oleju"
           << "Filtr paliwa" << "Filtr powietrza" << "Filtr kabinowy"
           << "Przebieg" << "Data" << "Notatka";
    ui->tableWidget->setColumnCount(12);
    ui->tableWidget->setRowCount(table.exploitation.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.exploitation.size());
    int i = 0;
    for (auto& x: table.exploitation)
    {
        id[i] = x.idexploitation;
        QString surname = table.ClientById(table.CarById(x.idcar).idclient).surname;
        QString name = table.ClientById(table.CarById(x.idcar).idclient).name;
        QString brand = table.BrandById(table.ModelById(table.CarById(x.idcar).
                                                        idmodel).idbrand).name;
        QString model = table.ModelById(table.CarById(x.idcar).idmodel).name;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(surname));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(brand));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(model));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(x.oil));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(x.oil_filter));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(x.fuel_filter));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(x.air_filter));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(x.cabin_filter));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QVariant(x.mileage).toString()));
        ui->tableWidget->setItem(i, 10, new QTableWidgetItem(x.date));
        ui->tableWidget->setItem(i, 11, new QTableWidgetItem(x.note));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 120);
    ui->tableWidget->setColumnWidth(2, 110);
    ui->tableWidget->setColumnWidth(3, 110);
    ui->tableWidget->setColumnWidth(4, 130);
    ui->tableWidget->setColumnWidth(5, 130);
    ui->tableWidget->setColumnWidth(6, 130);
    ui->tableWidget->setColumnWidth(7, 130);
    ui->tableWidget->setColumnWidth(8, 130);
    ui->tableWidget->setColumnWidth(9, 80);
    ui->tableWidget->setColumnWidth(10, 120);
    ui->tableWidget->setColumnWidth(11, 130);
}

void MainWindow::run_client()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Klient");
    chosenTable = Tclient;
    QStringList labels;
    labels << "Imię" << "Nazwisko" << "Telefon" << "Notatka";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(table.client.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.client.size());
    int i = 0;
    for (auto& x: table.client)
    {
        QString tel = (x.phone > 0) ? QVariant(x.phone).toString() : "";
        id[i] = x.idclient;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(x.name));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(x.surname));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(tel));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(x.note));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
}

void MainWindow::run_brand()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Marka");
    chosenTable = Tbrand;
    QStringList labels;
    labels << "Marka";
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(table.brand.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.brand.size());
    int i = 0;
    for (auto& x: table.brand)
    {
        id[i] = x.idbrand;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(x.name));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 130);
}

void MainWindow::run_model()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Model");
    chosenTable = Tmodel;
    QStringList labels;
    labels << "Marka" << "Model";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(table.model.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.model.size());
    int i = 0;
    for (auto& x: table.model)
    {
        id[i] = x.idmodel;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(table.BrandById(x.idbrand).name));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(x.name));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 130);
    ui->tableWidget->setColumnWidth(1, 130);
}

void MainWindow::run_repair()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Naprawa");
    chosenTable = Trepair;
    QStringList labels;
    labels << "Naprawa" << "Nazwisko" << "Imię" << "Marka" << "Model" << "Opis"
           << "Data przyjęcia" << "Data oddania" << "Koszt robocizny" << "Notatka";
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(table.repair.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.repair.size());
    int i = 0;
    for (auto& x: table.repair)
    {
        id[i] = x.idrepair;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QVariant(x.idrepair).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(
                                     table.ClientById(table.CarById(x.idcar).idclient).surname));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(
                                     table.ClientById(table.CarById(x.idcar).idclient).name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(
                                     table.BrandById(table.ModelById(table.CarById(x.idcar).idmodel).idbrand).name));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(
                                     table.ModelById(table.CarById(x.idcar).idmodel).name));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(x.desc.replace("~n", "; ")));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(x.indate));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(x.outdate));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(x.repair_price, 'f', 2)));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(x.note));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 130);
    ui->tableWidget->setColumnWidth(4, 130);
    ui->tableWidget->setColumnWidth(5, 150);
    ui->tableWidget->setColumnWidth(6, 120);
    ui->tableWidget->setColumnWidth(7, 120);
    ui->tableWidget->setColumnWidth(8, 100);
    ui->tableWidget->setColumnWidth(9, 150);
}

void MainWindow::run_car()
{
//    if (!isConnected)
//        return;
    this->setWindowTitle("Warsztat - Samochód");
    chosenTable = Tcar;
    QStringList labels;
    labels << "ID" << "Nazwisko" << "Imię" << "Marka" << "Model" << "Rok produkcji" << "Generacja" << "Silnik";
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(table.car.size());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    id.clear();
    id.resize(table.car.size());
    int i = 0;
    for (auto& x: table.car)
    {
        id[i] = x.idcar;
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QVariant(x.idcar).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(table.ClientById(x.idclient).surname));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(table.ClientById(x.idclient).name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(
                                     table.BrandById(table.ModelById(x.idmodel).idbrand).name));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(table.ModelById(x.idmodel).name));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QVariant(x.year).toString()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(x.generation));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(x.engine));
        ++i;
    }
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 130);
    ui->tableWidget->setColumnWidth(4, 130);
    ui->tableWidget->setColumnWidth(5, 130);
    ui->tableWidget->setColumnWidth(6, 100);
    ui->tableWidget->setColumnWidth(7, 150);
}

void MainWindow::list_repair()                         // podsumowanie naprawy
{
    chosenTable = Tnull;
    Repair& repair = table.RepairById(id[ui->tableWidget->currentRow()]);
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    QStringList label;
    label << "Nazwa" << "Opis" << "Cena";
    ui->tableWidget->setHorizontalHeaderLabels(label);
    float price = repair.repair_price;
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Robocizna"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(repair.desc));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(repair.repair_price, 'f', 2)));
    unsigned i = 1;
    for (auto& x: table.part)
    {
        if (x.idrepair != repair.idrepair)
            continue;
        ui->tableWidget->setRowCount(i+1);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(x.name));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(x.note));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(x.price, 'f', 2)));
        price += QVariant(x.price).toFloat();
        ++i;
    }
    ui->tableWidget->setRowCount(i+1);
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem("Kwota łączna"));
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(price, 'f', 2)));
}

void MainWindow::run_dodaj()
{
//    if (!isConnected)
//        return;
    currentId = -1;
    switch (chosenTable)
    {
    case Tnull      : break;
    case Tpart     : addPart(); break;
    case Texploitation : addExploitation(); break;
    case Tclient    : addClient(); break;
    case Tbrand     : addBrand(); break;
    case Tmodel     : addModel(); break;
    case Trepair   : addRepair(); break;
    case Tcar  : addCar(); break;
    }
}

void MainWindow::run_aktualizuj()
{
//    if (!isConnected || (chosenTable == Tnull))
//        return;
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        currentId = -1;
        QMessageBox::information(this, "Nie zaznaczono elementu", "Aby aktualizować dane musisz wcześniej zaznaczyć obiekt");
        return;
    }
    // qDebug() << "currentId = " << currentId;
    currentId = id[row];
    // qDebug() << "currentId = " << currentId;
//    for (auto& x: table.exploitation) {
//         qDebug() << x.idexploitation;
//    }
    // qDebug() << table.ExploitationById(currentId).serialize();

    switch (chosenTable)
    {
    case Tnull      : break;
    case Tpart     : addPart(); break;
    case Texploitation : addExploitation(); break;
    case Tclient    : addClient(); break;
    case Tbrand     : addBrand(); break;
    case Tmodel     : addModel(); break;
    case Trepair   : addRepair(); break;
    case Tcar  : addCar(); break;
    }
    currentId = -1;
}

void MainWindow::run_usun()
{
//    if (!isConnected || (chosenTable == Tnull))
//        return;
    currentId = ui->tableWidget->currentRow();
    if ((currentId < 0) || !(ui->tableWidget->item(currentId, 0)->isSelected()))
    {
        QMessageBox::information(this, "Nie zaznaczono elementu", "Aby usunąć dane musisz wcześniej zaznaczyć obiekt");
        return;
    }
    switch (chosenTable)
    {
    case Tnull      : break;
    case Tpart     : deletePart(); break;
    case Texploitation : deleteExploitation(); break;
    case Tclient    : deleteClient(); break;
    case Tbrand     : deleteBrand(); break;
    case Tmodel     : deleteModel(); break;
    case Trepair   : deleteRepair(); break;
    case Tcar  : deleteCar(); break;
    }
    currentId = -1;
}

void MainWindow::on_ACpolacz_triggered()
{
//    run_polacz();
}

void MainWindow::on_ACrozlacz_triggered()
{
//    run_rozlacz();
}

void MainWindow::on_ACpart_triggered()
{
    run_part();
}

void MainWindow::on_ACexploitation_triggered()
{
    run_exploitation();
}

void MainWindow::on_ACclient_triggered()
{
    run_client();
}

void MainWindow::on_ACbrand_triggered()
{
    run_brand();
}

void MainWindow::on_ACmodel_triggered()
{
    run_model();
}

void MainWindow::on_ACrepair_triggered()
{
    run_repair();
}

void MainWindow::on_ACcar_triggered()
{
    run_car();
}

void MainWindow::on_PBdodaj_clicked()
{
    run_dodaj();
}

void MainWindow::on_PBaktualizuj_clicked()
{
    run_aktualizuj();
}

void MainWindow::on_PBusun_clicked()
{
    run_usun();
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (chosenTable == Trepair)
        list_repair();
}
