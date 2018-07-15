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

class MyGeneralPurpose: public QObject
{
    Q_OBJECT

public:
     MyGeneralPurpose();
    ~MyGeneralPurpose();

    void init(QObject *obj) ;

public slots:
    void update();
    bool removeCurrentRow();
    void selectRow(int index);
    bool saveCurrentRow();
    bool saveAsNewRow();
    int rowCount() ;
    QJsonObject currentRowToJSON();
private:
    QSqlTableModel *m_tableModel ;
    QObject *obj ;
    int currentRow = -1;
};

#endif // MYGENERALPURPOSE_H
