#ifndef MYGENERALPURPOSE_H
#define MYGENERALPURPOSE_H

#include <QJsonObject>
#include <QObject>

#include <QDebug>
#include <QMetaClassInfo>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include "mypropertyhelper.h"

class easyORM: public QObject
{
    Q_OBJECT
public:
     easyORM();
    ~easyORM();

    void init(QObject *obj) ;

public slots:

    bool removeCurrentRow();
    bool removeAllRows();
    QJsonObject setCurrentRow(int index);

    void select();
    bool update();
    bool insert();
    bool where(QString condition);
    int rowCount() ;
    QJsonObject currentRowToJSON();

private:
    QSqlTableModel *m_tableModel ;
    QObject *obj ;
    int currentRow = -1;
};

#endif // MYGENERALPURPOSE_H
