#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QtXml>
#include <qdom.h>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("lenovo");
    db.setDatabaseName("sellData.db");
    db.setUserName("lb");
    db.setPassword("123");
    if(!db.open()) return false;


/*
    db.exec("create table factory(id varchar primary key, name varchar)");
    db.exec("insert into factory values('0','please select brand')");
    db.exec("insert into factory values('01','Yi WolksVagen')");
    db.exec("insert into factory values('02','Citrien')");
    db.exec("insert into factory values('03','Shanghai Wolksvagen')");

    db.exec("create table brand(id varchar primary key, name varchar, factory varchar,price int,sum int ,sell int , last int" );
    db.exec(QString("insert into brand values('01','奥迪A6','Yi WolksVagen',36,50,10,40)"));
    db.exec(QString("insert into brand values('02','捷达','Yi WolksVagen',34,20,5,15)"));
    db.exec(QString("insert into brand values('03','宝来','Yi WolksVagen',41,80,20,60)"));
    db.exec(QString("insert into brand values('04','奔驰','Yi WolksVagen',83,40,15,25)"));
    db.exec(QString("insert into brand values('05','毕加索','Citrien',39,50,15,35)"));
    db.exec(QString("insert into brand values('06','富康','Citrien',28,60,10,50)"));
    db.exec(QString("insert into brand values('07','标致307','Citrien',27,70,20,50)"));
    db.exec(QString("insert into brand values('08','桑塔纳','Shanghai Wolksvagen',25,75,25,50)"));
    db.exec(QString("insert into brand values('09','帕萨特','Shanghai Wolksvagen',27,65,20,45)"));

    db.exec("create table password(password varchar primary key)");
    db.exec("insert password value('123456')");
*/
    QSqlQuery query;
    query.exec("create table factory(id varchar primary key, name varchar)");
    query.exec("insert into factory values('0','please select brand')");
    query.exec("insert into factory values('01','Yi WolksVagen')");
    query.exec("insert into factory values('02','Citrien')");
    query.exec("insert into factory values('03','Shanghai Wolksvagen')");

    bool r=query.exec("create table brand(id varchar primary key, name varchar, factory varchar,price int,sum int ,sell int , last int)" );
    query.exec(QString("insert into brand values('01','奥迪A6','Yi WolksVagen',36,50,10,40)"));
    query.exec(QString("insert into brand values('02','捷达','Yi WolksVagen',34,20,5,15)"));
    query.exec(QString("insert into brand values('03','宝来','Yi WolksVagen',41,80,20,60)"));
    query.exec(QString("insert into brand values('04','奔驰','Yi WolksVagen',83,40,15,25)"));
    query.exec(QString("insert into brand values('05','毕加索','Citrien',39,50,15,35)"));
    query.exec(QString("insert into brand values('06','富康','Citrien',28,60,10,50)"));
    query.exec(QString("insert into brand values('07','标致307','Citrien',27,70,20,50)"));
    query.exec(QString("insert into brand values('08','桑塔纳','Shanghai Wolksvagen',25,75,25,50)"));
    query.exec(QString("insert into brand values('09','帕萨特','Shanghai Wolksvagen',27,65,20,45)"));

    query.exec("create table password(password varchar primary key)");
    query.exec("insert into password values('123456')");

    return true;
}


#endif // CONNECTION_H
