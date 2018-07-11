#include "mygeneralpurpose.h"

MyGeneralPurpose::MyGeneralPurpose()
{
    m_tableModel = new QSqlTableModel ;
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

MyGeneralPurpose::~MyGeneralPurpose()
{
    m_tableModel->clear();
    delete m_tableModel ;
    m_tableModel = nullptr;
}


void MyGeneralPurpose::init(QObject *obj)
{
    this->obj = obj ;
    m_tableModel->setTable(obj->metaObject()->className());
    m_tableModel->select();
    selectRow(0);
}

void MyGeneralPurpose::update()
{
    m_tableModel->select();
    currentRow = 0 ;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(currentRow).value(i)) ;

}

bool MyGeneralPurpose::removeCurrentRow()
{
    m_tableModel->removeRow(currentRow) ;
    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }

    selectRow(0);
    return true ;
}

void MyGeneralPurpose::selectRow(int index)
{
    currentRow = index ;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(currentRow).value(i)) ;
}

bool MyGeneralPurpose::saveCurrentRow()
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

bool MyGeneralPurpose::saveAsNewRow()
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

int MyGeneralPurpose::rowCount()
{
    return m_tableModel->rowCount();
}
