#include "mydatabase.h"


MyDatabase::MyDatabase(QObject *parent) : QObject(parent)
{

}

bool MyDatabase::initSQLITE3()
{
    databaseType = "QSQLITE" ;
    QString databaseName = "database.db";
    QString databasePath = QDir::toNativeSeparators(QApplication::applicationDirPath()).replace("\\","/") +"/";
    QString databaseLocation = databasePath + databaseName ;

    bool check = QSqlDatabase::isDriverAvailable(databaseType) ;
    if( !check ) msgCritical("Error", "QSQLITE is not availabe");

    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName(databaseLocation);

    bool ok = myDatabase.open();
    if ( !ok ) msgCritical("Error", myDatabase.lastError().text());
    return ok ;
}

QStringList MyDatabase::tables()
{
    return myDatabase.tables() ;
}

void MyDatabase::createTable(QObject *obj)
{
    QString tableName;
    QStringList columnsList ;
    tableName = obj->metaObject()->className() ;
    QString tmp ;

    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); ++i)
    {
        // TODO: replace qt type with sqlite type
        tmp = obj->metaObject()->property(i).read(obj).typeName();
        tmp.replace("QString", "TEXT");
        tmp.replace("char", "CHARACTER(1)");
        tmp.replace("int", "INTEGER");
        tmp.replace("float", "FLOAT");
        tmp.replace("double", "DOUBLE");
        tmp.replace("QDate", "DATE");
        tmp.replace("QDateTime", "DATETIME");
        tmp.replace("bool", "BOOLEAN");
        if(QString(obj->metaObject()->property(i).name()).at(0) == '_')
            continue;
        columnsList << QString(obj->metaObject()->property(i).name()) +" "+tmp;

    }

    QString schema = prepare_create(tableName, columnsList) ;
    if(!executeQuery(schema))
        qDebug() << "err: executeQuery(schema) ";
    _schemaMap.insert(tableName, schema);

}

QString MyDatabase::prepare_create(QString tableName, QStringList columnsList)
{
    QString returnValue = "CREATE TABLE IF NOT EXISTS "+ tableName +"(";
    int n = columnsList.length() ;
    for ( int i = 0 ; i < n ; i++ )
    {
        if ( i == n-1 )
        {
            returnValue += columnsList[i] + "); " ;
            break ;
        }
        returnValue += columnsList[i] + ", " ;
    }
    return returnValue ;
}

bool MyDatabase::executeQuery(QString query)
{
    QSqlQuery cmd ;
    bool ok = cmd.exec(query);
    if ( !ok ) msgCritical("_executeQuery", query+"\n"+cmd.lastError().text());
    return ok ;
}

void MyDatabase::msgCritical(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox::critical(0,title,body);

}
