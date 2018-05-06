#include <QTextStream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <vector>
#include <map>
#include <string>
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
    int idclient;
    QString name;
    QString surname;
    int phone;
    QString note;
    Client(int Id = 0, QString im = "name", QString na = "surname",
           int te = 0, QString no = "note") :
        idclient(Id), name(im), surname(na), phone(te), note(no) { }
//     change table into string with all values and "\t" between
    QString serialize()
    {
        QString serial =
            QVariant(idclient).toString() + "\t" +
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
    int idbrand;
    QString name;
    Brand(int IdBrand = 0, QString NameOfBrand = "")
        : idbrand(IdBrand), name(NameOfBrand) { }
    QString serialize() { return name; }

};

class Model : public Table
{
public:
    int idmodel;
    int idbrand;
    QString name;
    Model() { }
    Model(int idmodel, int idbrand, QString Name)
        : idmodel(idmodel), idbrand(idbrand), name(Name) { }
    QString serialize()
    {
        QString serial =
                QVariant(idmodel).toString() + "\t" +
                QVariant(idbrand).toString() + "\t" +
                name;
        return serial;
    }
};

class Car : public Table
{
public:
    int idcar;
    int idclient;
    int idmodel;
    int year;
    QString generation;
    QString engine;
    Car() { }
    Car(int IdCar, int IdClient, int IdModel, int Year,
        QString Generation, QString Engine)
        : idcar(IdCar), idclient(IdClient), idmodel(IdModel), year(Year),
          generation(Generation), engine(Engine) { }
    QString serialize()
    {
        QString serial =
                QVariant(idcar).toString() + "\t" +
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
    int idexploitation;
    int idcar;
    QString oil;
    QString oil_filter;
    QString fuel_filter;
    QString air_filter;
    QString cabin_filter;
    int mileage;
    QString date;
    QString note;
    Exploitation(int Idexploitation = 0, int Idcar = 0, QString Oil = "",
                 QString Oil_filter = "", QString Fuel_filter = "",
                 QString Air_filter = "", QString Cabin_filter = "",
                 int Mileage = 0, QString Date = "", QString Note = "")
        : idexploitation(Idexploitation), idcar(Idcar), oil(Oil),
          oil_filter(Oil_filter), fuel_filter(Fuel_filter),
          air_filter(Air_filter), cabin_filter(Cabin_filter), mileage(Mileage),
          date(Date), note(Note) { }
    QString serialize()
    {
        QString serial =
                QVariant(idexploitation).toString() + "\t" +
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
    int idrepair;
    int idcar;
    QString desc;
    QString indate;
    QString outdate;
    QString note;
    float repair_price;
    Repair() { }
    Repair(int Idrepair, int Idcar, QString Desc,
           QString Indate, QString Outdate,
           QString Note, float Repair_price)
        : idrepair(Idrepair), idcar(Idcar), desc(Desc),
          indate(Indate), outdate(Outdate), note(Note),
          repair_price(Repair_price) { }
    QString serialize()
    {
        QString serial =
                QVariant(idrepair).toString() + "\t" +
                QVariant(idcar).toString() + "\t" +
                desc + "\t" +
                indate + "\t" +
                outdate + "\t" +
                note + "\t" +
                QString::number(repair_price, 'f', 2);
        return serial;
    }
};

class Part : public Table
{
public:
    int idpart;
    int idrepair;
    QString name;
    float price;
    QString note;
    Part(int Idpart = 0, int Idrepair = 0, QString Name = "",
         float Price = 0, QString Note = "")
        : idpart(Idpart), idrepair(Idrepair), name(Name),
          price(Price), note(Note) { }
    QString serialize()
    {
        QString serial =
                QVariant(idpart).toString() + "\t" +
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
    std::vector<Part> part;
    std::vector<Exploitation> exploitation;
    std::vector<Client> client;
    std::vector<Brand> brand;
    std::vector<Model> model;
    std::vector<Repair> repair;
    std::vector<Car> car;
    KTable() { }
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

    Brand& BrandById(int IdBrand)
    {
        for (auto& x: brand) {
            if (x.idbrand == IdBrand)
                return x;
        }
    }

    Car& CarById(int id)
    {
        for (auto& x: car) {
            if (x.idcar == id) {
                return x;
            }
        }
    }

    Client& ClientById(int id)
    {
        for (auto& x: client) {
            if (x.idclient == id) {
                return x;
            }
        }
    }

    Exploitation& ExploitationById(int id)
    {
        for (auto& x: exploitation) {
            if (x.idexploitation == id) {
                return x;
            }
        }
    }

    Model& ModelById(int id)
    {
        for (auto& x: model) {
            if (x.idmodel == id) {
                return x;
            }
        }
    }

    Part& PartById(int id)
    {
        for (auto& x: part) {
            if (x.idpart == id) {
                return x;
            }
        }
    }

    Repair& RepairById(int id)
    {
        for (auto& x: repair) {
            if (x.idrepair == id) {
                return x;
            }
        }
    }
};

class Login
{
public:
    Login() { }

    // get date from MySQL table and insert into vector<T>
    void selectPart(std::vector<Part>& part)
    {
        QFile file("Data/parts.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        part.clear();
        while (!fin.atEnd()) {
            line = fin.readLine();
            row = line.split("`");
            part.push_back(Part(QVariant(row[0]).toInt(),
                                QVariant(row[1]).toInt(), row[2],
                                QVariant(row[3]).toFloat(), row[4]));
        }
        file.close();
    }

    void selectExploitation(std::vector<Exploitation>& exploitation)
    {
        QFile file("Data/exploitation.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        exploitation.clear();
        for (; (!fin.atEnd()); ) {
            line = fin.readLine();
            row = line.split("`");
            exploitation.push_back(Exploitation(
                                       QVariant(row[0]).toInt(),
                                       QVariant(row[1]).toInt(),
                                       row[2], row[3], row[4],
                                       row[5], row[6], QVariant(row[7]).toInt(),
                                       row[8], row[9]));
        }
    }

    void selectClient(std::vector<Client>& client)
    {
        QFile file("Data/client.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        client.clear();
        while (!fin.atEnd()) {
            line = fin.readLine();
            row = line.split("`");
            client.push_back(Client(QVariant(row[0]).toInt(),
                                    row[1], row[2],
                                    QVariant(row[3]).toInt(), row[4]));
        }
    }

    void selectBrand(std::vector<Brand>& brand)
    {
        QFile file("Data/brand.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        brand.clear();
        for (unsigned i; (!fin.atEnd()); ++i) {
            line = fin.readLine();
            row = line.split("`");
            brand.push_back(Brand(QVariant(row[0]).toInt(), row[1]));
        }
    }

    void selectModel(std::vector<Model>& model)
    {
        QFile file("Data/model.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        model.clear();
        while (!fin.atEnd()) {
            line = fin.readLine();
            row = line.split("`");
            model.push_back(Model(QVariant(row[0]).toInt(),
                                  QVariant(row[1]).toInt(),
                                  row[2]));
        }
    }

    void selectRepair(std::vector<Repair>& repair)
    {
        QFile file("Data/service.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        repair.clear();
        while (!fin.atEnd()) {
            line = fin.readLine();
            row = line.split("`");
            repair.push_back(Repair(QVariant(row[0]).toInt(),
                                    QVariant(row[1]).toInt(),
                                    row[2], row[3], row[4],
                                    row[5], QVariant(row[6]).toFloat()));
        }
    }

    void selectCar(std::vector<Car>& car)
    {
        QFile file("Data/car.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream fin(&file);
        QString line;
        QStringList row;
        car.clear();
        while (!fin.atEnd()) {
            line = fin.readLine();
            row = line.split("`");
            car.push_back(Car(QVariant(row[0]).toInt(),
                              QVariant(row[1]).toInt(),
                              QVariant(row[2]).toInt(),
                              QVariant(row[3]).toInt(),
                              row[4], row[5]));
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
    bool addAny(Table& t, int i, QString& path, QString& data)
    {
        // opening of a file
        QFile file(path);    // open file
        file.open(QIODevice::ReadOnly);    // let read and write
        QTextStream fio(&file);     // use file as stream

        // read file
        // get whole file to QString all
        QString all;
        if (i > 0)
        {
            all = fio.readAll();
            file.close();
            // find regex
            // "\n" finishes each line so to find next I have to write "\n4 "
            // 4 is an interesing number in this case
            QString regString = "\n" + QVariant(i).toString();
            QRegExp regex(regString);
            int position = all.indexOf(regex) + 1;

            // from begin to found position
            // save file
            // set carret to begin
            file.open(QIODevice::WriteOnly);
            fio << all.left(position);

            // changing item
            fio << i << '`'
                 << data;

            // from position to EOF
            all = all.midRef(position).toString();

            regex = QRegExp("\n");
            position = all.indexOf(regex);
            fio << all.midRef(position);
        }
        else
        {
            while (!fio.atEnd()) {
                all = fio.readLine();
            }
            file.close();
            QRegExp regex("`");
            int position = all.indexOf(regex);
            i = all.left(position).toInt() + 1;

            // from begin to found position
            // save file
            // set carret to begin
            file.open(QIODevice::Append);

            // changing item
            fio << i << '`' << data << '\n';
        }
//        // qDebug() << query;
//        return mysql_query(&mysql, query.toUtf8());
    return 0;
    }

    bool addPart(Part& part, int i = 0)
    {
        QString data = QVariant(part.idrepair).toString() + '`'
                    + part.name + '`'
                    + QString::number(part.price, 'f', 2) + '`'
                    + part.note;
        QString path = "Data/parts.csv";
        return addAny(part, i, path, data);
    }

    bool addExploitation(Exploitation& e, int i = 0)
    {
        QString data = QVariant(e.idcar).toString() +
                "`" + e.oil + "`" + e.oil_filter +
                "`" + e.fuel_filter + "`" + e.air_filter +
                "`" + e.cabin_filter + "`" + QVariant(e.mileage).toString() +
                "`" + e.date + "`" + e.note;
        QString path = "Data/exploitation.csv";
        return addAny(e, i, path, data);
    }

    bool addClient(Client& e, int i = 0)
    {
        QString data = e.name + "`" + e.surname + "`"
                + QVariant(e.phone).toString()
                + "`" + e.note;
        QString path = "Data/client.csv";
        return addAny(e, i, path, data);
    }

    bool addBrand(Brand& e, int i = 0)
    {
        QString data = e.name;
        QString path = "Data/brand.csv";
        return addAny(e, i, path, data);
    }

    bool addModel(Model& e, int i = 0)
    {
        QString data = QVariant(e.idbrand).toString() + "`" + e.name;
        QString path = "Data/model.csv";
        return addAny(e, i, path, data);
    }

    bool addRepair(Repair& e, int i = 0)
    {
        QString data = QVariant(e.idcar).toString()
                + "`" + e.desc
                + "`" + e.indate
                + "`" + e.outdate
                + "`" + e.note
                + "`" + QString::number(e.repair_price, 'f', 2);
        QString path = "Data/service.csv";
        // qDebug() << e.serialize();
        return addAny(e, i, path, data);
    }

    bool addCar(Car& e, int i = 0)
    {
        QString data = QVariant(e.idclient).toString() +
                "`" + QVariant(e.idmodel).toString() +
                "`" + QVariant(e.year).toString() +
                "`" + e.generation +
                "`" + e.engine;
        QString path = "Data/car.csv";
        return addAny(e, i, path, data);
    }

    bool deleteAny(int i, QString& path)
    {
        // opening of a file
        QFile file(path);    // open file
        file.open(QIODevice::ReadOnly);    // let read and write
        QTextStream fio(&file);     // use file as stream

        // read file
        // get whole file to QString all
        QString all;

        all = fio.readAll();
        file.close();
        // find regex
        // "\n" finishes each line so to find next I have to find "\n" + 1
        // 4 is an interesing number in this case
        QString regString = "\n" + QVariant(i).toString();
        QRegExp regex(regString);
        int position = all.indexOf(regex) + 1;

        // from begin to found position
        // save file
        // set carret to begin
        file.open(QIODevice::WriteOnly);
        fio << all.left(position);

        // from position to EOF
        all = all.midRef(position).toString();
        regex = QRegExp("\n");
        position = all.indexOf(regex) + 1;
        fio << all.midRef(position).toString();

        return 0;
    }

    bool deletePart(int i)
    {
        QString path = "Data/parts.csv";
        return deleteAny(i, path);
    }

    bool deleteExploitation(int i)
    {
        QString path = "Data/exploitation.csv";
        return deleteAny(i, path);
    }

    bool deleteClient(int i)
    {
        QString path = "Data/client.csv";
        return deleteAny(i, path);
    }

    bool deleteBrand(int i)
    {
        QString path = "Data/brand.csv";
        return deleteAny(i, path);
    }

    bool deleteModel(int i)
    {
        QString path = "Data/model.csv";
        return deleteAny(i, path);
    }

    bool deleteRepair(int i)
    {
        QString path = "Data/service.csv";
        return deleteAny(i, path);
    }

    bool deleteCar(int i)
    {
        QString path = "Data/car.csv";
        return deleteAny(i, path);
    }
};
#endif // TABELE_H

