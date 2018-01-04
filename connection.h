#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QtXml>
#include <qdom.h>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("lenovo");
    db.setDatabaseName("sellData.data");
    db.setUserName("lb");
    db.setPassword("123");
    if(!db.open()) return false;



    db.exec("create tafble factory(id varchar primary key, name varchar)");
    db.exec("insert into factory values('0','please select brand')");
    db.exec("insert into factory values('01','Yi WolksVagen')");
    db.exec("insert into factory values('02','Citrien')");
    db.exec("insert into factory values('03','Shanghai Wolksvagen')");

    db.exec("create table brand(id varchar primary key, name varchar, factory varchar,price int,sum int ,sell int , last int" );
    db.exec(QString("insert into brand values('01','奥迪A6','一汽大众',36,50,10,40)"));
    db.exec(QString("insert into brand values('02','捷达','一汽大众',34,20,5,15)"));
    db.exec(QString("insert into brand values('03','宝来','一汽大众',41,80,20,60)"));
    db.exec(QString("insert into brand values('04','奔驰','一汽大众',83,40,15,25)"));
    db.exec(QString("insert into brand values('05','毕加索','二汽神龙',39,50,15,35)"));
    db.exec(QString("insert into brand values('06','富康','二汽神龙',28,60,10,50)"));
    db.exec(QString("insert into brand values('07','标致307','二汽神龙',27,70,20,50)"));
    db.exec(QString("insert into brand values('08','桑塔纳','上海大众',25,75,25,50)"));
    db.exec(QString("insert into brand values('09','帕萨特','上海大众',27,65,20,45)"));

    db.exec("create table password(password varchar primary key)");
    db.exec("insert password value('123456')");

    return true;
}


#endif // CONNECTION_H
