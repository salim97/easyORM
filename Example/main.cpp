#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QMetaClassInfo>
#include <QQmlContext>
#include <QSqlTableModel>

#include "clients.h"
#include "mydatabase.h"
#include "mygeneralpurpose.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
qmlRegisterInterface<QSqlTableModel>("QSqlTableModel");
    MyDatabase myDatabase;
    if(!myDatabase.initSQLITE3()) // you must call this method to make connection with database....
        return 1 ;



    qDebug() << "tables: " << myDatabase.tables() ;

    Clients clients; // example of class that we will convert it to table


    myDatabase.createTable(&clients);
    qDebug() << "clients" << myDatabase.tables() ;

//    qDebug() << clients.first_name() ;
//    clients.removeCurrentRow();
//    qDebug() << clients.first_name() ;
//    clients.first_name("a") ; clients.saveAsNewRow() ;
//    clients.first_name("b") ; clients.saveAsNewRow() ;
//    clients.first_name("c") ; clients.saveAsNewRow() ;

//    for( int i = 0 ; i < clients.rowCount() ; i++ )
//    {
//        clients.selectRow(i);
//        qDebug() << clients.first_name() ;
//    }



    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("clients", &clients);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
