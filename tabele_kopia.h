#include <QString>
#include <vector>
#include <map>
#include <string>
#include <mysql/mysql.h>
#include <QVariant>
#include <QTableWidgetItem>

#ifndef TABELE_H
#define TABELE_H

enum enumTable { Tnull, Tpart, Texploitation, Tclient, Tbrand, Tmodel, Trepair, Tcar };

class Table
{
public:
    virtual QString serialize() = 0;
};

class Client : public Table
{
public:
//    int idclient;
    QString name;
    QString surname;
    int phone;
    QString note;
    Client(const char* im = "name", const char* na = "surname",
           int te = 0, const char* no = "note") :
        name(im), surname(na), phone(te), note(no) { }
//     change table into string with all values and "\t" between
    QString serialize()
    {
        QString serial =
//            QVariant(idclient).toString() + "\t" +
            name + "\t" +
            surname + "\t" +
            QVariant(phone).toString() + "\t" +
            note;
        return serial;
    }
};

class Brand : public Table
{
public:
//    int idbrand;
    QString name;
    Brand(const char* naz = "") : name(naz) { }
    QString serialize() { return name; }

};

class Model : public Table
{
public:
//    int idmodel;
    int idbrand;
    QString name;
    QString serialize()
    {
        QString serial =
//                QVariant(idmodel).toString() + "\t" +
                QVariant(idbrand).toString() + "\t" +
                name;
        return serial;
    }
};

class Car : public Table
{
public:
//    int idcar;
    int idclient;
    int idmodel;
    int year;
    QString generation;
    QString engine;
    QString serialize()
    {
        QString serial =
//                QVariant(idcar).toString() + "\t" +
                QVariant(idclient).toString() + "\t" +
                QVariant(idmodel).toString() + "\t" +
                QVariant(year).toString() + "\t" +
                generation + "\t" + engine;
        return serial;
    }
};

class Exploitation : public Table
{
public:
//    int idexploitation;
    int idcar;
    QString oil;
    QString oil_filter;
    QString fuel_filter;
    QString air_filter;
    QString cabin_filter;
    int mileage;
    QString date;
    QString note;
    QString serialize()
    {
        QString serial =
//                QVariant(idexploitation).toString() + "\t" +
                QVariant(idcar).toString() + "\t" +
                oil + "\t" +
                oil_filter + "\t" +
                fuel_filter + "\t" +
                air_filter + "\t" +
                cabin_filter + "\t" +
                QVariant(mileage).toString() + "\t" +
                date + "\t" +
                note;
        return serial;
    }
};

class Repair : public Table
{
public:
//    int idrepair;
    int idcar;
    QString desc;
    QString indate;
    QString outdate;
    float repair_price;
    QString note;
    QString serialize()
    {
        QString serial =
//                QVariant(idrepair).toString() + "\t" +
                QVariant(idcar).toString() + "\t" +
                desc + "\t" +
                indate + "\t" +
                outdate + "\t" +
                note + "\t" +
                QVariant(repair_price).toFloat();
        return serial;
    }
};

class Part : public Table
{
public:
//    int idpart;
    int idrepair;
    QString name;
    float price;
    QString note;
    QString serialize()
    {
        QString serial =
//                QVariant(idpart).toString() + "\t" +
                QVariant(idrepair).toString() + "\t" +
                name + "\t" +
                QVariant(price).toFloat() + "\t" +
                note;
        return serial;
    }
};

class KTable
{
public:
    std::map<int, Part> part;
    std::map<int, Exploitation> exploitation;
    std::map<int, Client> client;
    std::map<int, Brand> brand;
    std::map<int, Model> model;
    std::map<int, Repair> repair;
    std::map<int, Car> car;
    KTable()
    {
//        part.push_back(Part());
//        exploitation.push_back(Exploitation());
//        client.push_back(Client());
//        brand.push_back(Brand());
//        model.push_back(Model());
//        repair.push_back(Repair());
//        car.push_back(Car());
    }
    void clear()
    {
        part.clear();
        exploitation.clear();
        client.clear();
        brand.clear();
        model.clear();
        repair.clear();
        car.clear();
    }
};

class Login
{
public:
    MYSQL mysql;
    QString ip;
    QString username;
    QString password;
    QString datebase;
    Login(const char* i = "127.0.0.1", const char* u = "r", const char* p = "1234", const char* d = "warsztat")
        : ip(i), username(u), password(p), datebase(d) { }

    bool connect()
    {
        mysql_init(&mysql); // incjalizacja
        mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"utf8");
        // if not connected return 0
        return mysql_real_connect(&mysql, ip.toStdString().c_str(), username.toStdString().c_str(),
                                  password.toStdString().c_str(), datebase.toStdString().c_str(), 0, NULL, 0);
    }

    void disconnect()
    {
        ip = "";
        username = "";
        password = "";
        datebase = "";
        mysql_close(&mysql); // zamknij połączenie
    }

    bool query(QString str)
    {
        // qDebug() << "query: " << str;
        return mysql_query(&mysql, str.toStdString().c_str());
    }

    // get date from MySQL table and insert into vector<T>
    void selectPart(std::map<int, Part>& part)
    {
        mysql_query(&mysql, "SELECT * FROM part;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        part.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            part[i].idrepair = QVariant(row[1]).toInt();
            part[i].name = row[2];
            part[i].price = QVariant(row[3]).toFloat();
            part[i].note = row[4];
        }

    }

    void selectExploitation(std::map<int, Exploitation>& exploitation)
    {
        mysql_query(&mysql, "SELECT * FROM exploitation;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        exploitation.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            exploitation[i].idcar = QVariant(row[1]).toInt();
            exploitation[i].oil = row[2];
            exploitation[i].oil_filter = row[3];
            exploitation[i].fuel_filter = row[4];
            exploitation[i].air_filter = row[5];
            exploitation[i].cabin_filter = row[6];
            exploitation[i].mileage = QVariant(row[7]).toInt();
            exploitation[i].date = row[8];
            exploitation[i].note = row[9];
        }
    }

    void selectClient(std::map<int, Client>& client)
    {
        mysql_query(&mysql, "SELECT * FROM client;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        client.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            client[i].name = row[1] ? row[1] : "";
            client[i].surname = row[2] ? row[2] : "";
            client[i].phone = row[3] ? QVariant(row[3]).toInt() : -1;
            client[i].note = row[4] ? row[4] : "";
        }
    }

    void selectBrand(std::map<int, Brand>& brand)
    {
        mysql_query(&mysql, "SELECT * FROM brand;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        brand.empty();
//        brand.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            brand[i].name = row[1] ? row[1] : "";
        }
    }

    void selectModel(std::map<int, Model>& model)
    {
        mysql_query(&mysql, "SELECT * FROM model;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        model.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            model[i].idbrand = row[1] ? QVariant(row[1]).toInt() : -1;
            model[i].name = row[2] ? row[2] : "";
        }
    }

    void selectRepair(std::map<int, Repair>& repair)
    {
        mysql_query(&mysql, "SELECT * FROM repair;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        repair.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            repair[i].idcar = row[1] ? QVariant(row[1]).toInt() : -1;
            repair[i].desc = row[2] ? row[2] : "";
            repair[i].indate = row[3] ? row[3] : "";
            repair[i].outdate = row[4] ? row[4] : "";
            repair[i].note = row[5] ? row[5] : "";
            repair[i].repair_price = row[6] ? QVariant(row[6]).toFloat() : 0;
        }
    }

    void selectCar(std::map<int, Car>& car)
    {
        mysql_query(&mysql, "SELECT * FROM car;");
        MYSQL_RES* result = mysql_store_result(&mysql);
//        int size = mysql_num_rows(result);
        car.empty();
        MYSQL_ROW row;
        for (int i; (row = mysql_fetch_row(result)); )
        {
            i = QVariant(row[0]).toInt();
            car[i].idclient = row[1] ? QVariant(row[1]).toInt() : -1;
            car[i].idmodel = row[2] ? QVariant(row[2]).toInt() : -1;
            car[i].year = row[3] ? QVariant(row[3]).toInt() : -1;
            car[i].generation = row[4] ? row[4] : "";
            car[i].engine = row[5] ? row[5] : "";
        }
    }

    void selectAll(KTable& table)
    {
        selectPart(table.part);
        selectExploitation(table.exploitation);
        selectClient(table.client);
        selectBrand(table.brand);
        selectModel(table.model);
        selectRepair(table.repair);
        selectCar(table.car);
    }

    bool addPart(Part& part, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE part SET idrepair = \"" + QVariant(part.idrepair).toString() +
                    "\", name = \"" + part.name + "\", price = \"" + QString::number(part.price, 'f', 2) +
                    "\", note = \"" + part.note + "\" WHERE idpart = \"" +
                    QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO part (idrepair, name, price, note) VALUES (\"" + QVariant(part.idrepair).toString() +
                    "\", \"" + part.name + "\", \"" + QString::number(part.price, 'f', 2) +
                    "\", \"" + part.note + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addExploitation(Exploitation& e, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE exploitation SET idcar = \"" + QVariant(e.idcar).toString() +
                    "\", oil = \"" + e.oil + "\", oil_filter = \"" + e.oil_filter +
                    "\", fuel_filter = \"" + e.fuel_filter + "\", air_filter = \"" + e.air_filter +
                    "\", cabin_filter = \"" + e.cabin_filter + "\", mileage = \"" + QVariant(e.mileage).toString() +
                    "\", date = \"" + e.date + "\", note = \"" + e.note + "\" WHERE idexploitation = \"" +
                    QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO exploitation (idcar, oil, oil_filter, fuel_filter, air_filter, cabin_filter, mileage, date, note) VALUES (\"" +
                    QVariant(e.idcar).toString() + "\", \"" + e.oil + "\", \"" +
                    e.oil_filter + "\", \"" + e.fuel_filter + "\", \"" + e.air_filter + "\", \"" +
                    e.cabin_filter + "\", \"" + QVariant(e.mileage).toString() + "\", \"" + e.date + "\", \"" +
                    e.note + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addClient(Client& e, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE client SET name = \"" + e.name +
                    "\", surname = \"" + e.surname + "\", phone = \"" + QVariant(e.phone).toString() +
                    "\", note = \"" + e.note + "\" WHERE idclient = \"" +
                    QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO client (name, surname, phone, note) VALUES (\"" +
                    e.name + "\", \"" + e.surname + "\", \"" + QVariant(e.phone).toString() + "\", \"" +
                    e.note + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addBrand(Brand& e, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE brand SET name = \"" + e.name +
                    "\" WHERE idbrand = \"" + QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO brand (name) VALUES (\"" +
                    e.name + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addModel(Model& e, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE model SET idbrand = \"" + QVariant(e.idbrand).toString() +
                    "\", name = \"" + e.name + "\" WHERE idmodel = \"" +
                    QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO model (idbrand, name) VALUES (\"" +
                    QVariant(e.idbrand).toString() + "\", \"" + e.name + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addRepair(Repair& e, int i = 0)
    {
        QString query;
        if (i)
        {
            query = "UPDATE repair SET idcar = \"" + QVariant(e.idcar).toString() +
                    "\", desc = \"" + e.desc + "\", indate = \"" + e.indate +
                    "\", outdate = \"" + e.outdate + "\", repair_price = \"" + QString::number(e.repair_price, 'f', 2) +
                    "\", note = \"" + e.note + "\" WHERE idrepair = \"" +
                    QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO repair (idcar, desc, indate, outdate, repair_price, note) VALUES (\"" +
                    QVariant(e.idcar).toString() + "\", \"" + e.desc + "\", \"" +
                    e.indate + "\", \"" + e.outdate + "\", \"" + QString::number(e.repair_price, 'f', 2) + "\", \"" +
                    e.note + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool addCar(Car& e, int i = 0)
    {
        QString query;
        if (i > 0)
        {
            query = "UPDATE car SET idclient = \"" + QVariant(e.idclient).toString() +
                    "\", idmodel = \"" + QVariant(e.idmodel).toString() +
                    "\", year = \"" + QVariant(e.year).toString() +
                    "\", generation = \"" + e.generation +
                    "\", engine = \"" + e.engine +
                    "\" WHERE idcar = \"" + QVariant(i).toString() + "\";";
        }
        else
        {
            query = "INSERT INTO car (idclient, idmodel, year, generation, engine) VALUES (\"" +
                    QVariant(e.idclient).toString() + "\", \"" +
                    QVariant(e.idmodel).toString() + "\", \"" +
                    QVariant(e.year).toString() + "\", \"" +
                    e.generation + "\", \"" +
                    e.engine + "\");";
        }
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deletePart(int i)
    {
        QString query = "DELETE FROM part WHERE idpart = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteExploitation(int i)
    {
        QString query = "DELETE FROM exploitation WHERE idexploitation = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteClient(int i)
    {
        QString query = "DELETE FROM client WHERE idclient = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteBrand(int i)
    {
        QString query = "DELETE FROM brand WHERE idbrand = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteModel(int i)
    {
        QString query = "DELETE FROM model WHERE idmodel = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteRepair(int i)
    {
        QString query = "DELETE FROM repair WHERE idrepair = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }

    bool deleteCar(int i)
    {
        QString query = "DELETE FROM car WHERE idcar = \"" + QVariant(i).toString() + "\";";
        // qDebug() << query;
        return mysql_query(&mysql, query.toUtf8());
    }
};
#endif // TABELE_H

