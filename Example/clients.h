#ifndef CLIENTS_H
#define CLIENTS_H


#include <QDate>


#include "easyORM.h"

class Clients :  public easyORM
{

public:
    // you need this macro to get thing work proply
    //use this macro, or replace it with your own constrecteur but you must put init(this); on it
    INIT_CURD(Clients) // add CURD methods( Create, Update, Read, Delete)


    AUTO_PROPERTY(QString, first_name)
    AUTO_PROPERTY(QString, last_name)
    AUTO_PROPERTY(QDate, birth_date)
    AUTO_PROPERTY(char, gender)
    AUTO_PROPERTY(int, key)

public:
    //your public methods...
    //you can add init() function, to use it as your own constrecteur
    //you can add adjustRow() function, to get row adjust
        //for example : price * Quantity = totalPrice ;
        // instead of using trigger in each database (MYSQL, SQLITE3, ... )
private:
    //your private variables...


};

#endif // CLIENTS_H
