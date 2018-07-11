#ifndef CLIENTS_H
#define CLIENTS_H


#include <QDate>


#include "mygeneralpurpose.h"

class Clients :  public MyGeneralPurpose
{
    Q_OBJECT

public:
    //use this macro, or replace it with your own constrecteur but you must put init(this); on it
    INIT_CURD(Clients) // add CURD methods( Create, Update, Read, Delete)

    AUTO_PROPERTY(QString, first_name)
    AUTO_PROPERTY(QString, last_name)
    AUTO_PROPERTY(QDate, birth_date)
    AUTO_PROPERTY(char, gender)
    AUTO_PROPERTY(int, key)

public:
    //your public methods...

private:
    //your private variables...


};

#endif // CLIENTS_H
