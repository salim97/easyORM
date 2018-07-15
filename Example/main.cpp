#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QMetaClassInfo>
#include <QQmlContext>
#include <QJsonObject>

#include "clients.h"
#include "mydatabase.h"
#include "easyORM.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //qmlRegisterInterface<QJsonObject>("QJsonObject"); // TODO: remove this line

    MyDatabase myDatabase;
    if(!myDatabase.initSQLITE3()) // you must call this method to make connection with database....
        return 1 ;



    qDebug() << "tables: " << myDatabase.tables() ;

    Clients clients; // example of class that we will convert it to table
//    clients.select(); // select all data from sql table; // call this if you have two instance or more, editing the same table
                                                           // to sync data in client class

    myDatabase.createTable(&clients);
    qDebug() << "clients" << myDatabase.tables() ;

//    qDebug() << clients.first_name() ;
//    clients.removeCurrentRow();
//    qDebug() << clients.first_name() ;
//    clients.first_name("a") ; clients.insert() ;
//    clients.first_name("b") ; clients.insert() ;
//    clients.first_name("c") ; clients.insert() ;

    for( int i = 0 ; i < clients.rowCount() ; i++ )
    {
        clients.setCurrentRow(i);
        qDebug() << "C++: " <<clients.first_name() ;
    }



    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("clients", &clients);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
