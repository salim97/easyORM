#include "easyORM.h"

#include <QJsonDocument>
#include <QJsonObject>

easyORM::easyORM()
{
    m_tableModel = new QSqlTableModel ;
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

easyORM::~easyORM()
{
    m_tableModel->clear();
    delete m_tableModel ;
    m_tableModel = nullptr;
}


void easyORM::init(QObject *obj)
{
    this->obj = obj ;
    m_tableModel->setTable(obj->metaObject()->className());
    m_tableModel->select();
    setCurrentRow(0);
}

void easyORM::select()
{
    m_tableModel->setFilter("");
    m_tableModel->select();
    currentRow = 0 ;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(currentRow).value(i)) ;

}

bool easyORM::removeCurrentRow()
{
    m_tableModel->removeRow(currentRow) ;
    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }

    setCurrentRow(0);
    return true ;
}

bool easyORM::removeAllRows()
{
    //TODO: raplce remove all with query
    for(int i = 0 ; i < m_tableModel->rowCount() ; i++)
        m_tableModel->removeRow(i) ;

    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }

    setCurrentRow(0);
    return true ;
}

QJsonObject easyORM::setCurrentRow(int index)
{
    currentRow = index ;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(currentRow).value(i)) ;
   return currentRowToJSON() ;
}



bool easyORM::update()
{

    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
    {
        m_tableModel->setData(m_tableModel->index(currentRow, i), obj->metaObject()->property(i).read(obj));
    }
    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }
    return true ;
}

bool easyORM::insert()
{
    currentRow = m_tableModel->rowCount() ;
    m_tableModel->insertRow(currentRow);

    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
    {
        m_tableModel->setData(m_tableModel->index(currentRow, i), obj->metaObject()->property(i).read(obj));
    }

    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }
    return true ;

}

bool easyORM::where(QString condition)
{
    m_tableModel->setFilter(condition);
    m_tableModel->select();
    setCurrentRow(0);
}

int easyORM::rowCount()
{
    return m_tableModel->rowCount();
}

QJsonObject easyORM::currentRowToJSON()
{
    QJsonObject json;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
    {
        json.insert(QString(obj->metaObject()->property(i).name()),
                    QJsonValue::fromVariant(obj->metaObject()->property(i).read(obj)));
    }
    QJsonDocument doc(json);
    return json ;
}
