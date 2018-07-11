#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>
#include <QMetaClassInfo>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QApplication>

class MyDatabase : public QObject
{
    Q_OBJECT

public:
    explicit MyDatabase(QObject *parent = nullptr);
    bool initSQLITE3();
    void createTable(QObject *obj);
    QMap<QString, QString> _schemaMap;
    bool executeQuery(QString query);
    void msgCritical(QString title, QString body);
    QStringList tables();
signals:

private:
    QString prepare_create(QString tableName, QStringList columnsList);
    QSqlDatabase myDatabase ;
    QString databaseType ;
};

#endif // MYDATABASE_H
