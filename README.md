# easyORM

easyORM is easy library to create an equivalent of C++ class in SQL table ( sqlite3, mysql, ... ) and it allow you to use ORM design pattern, It is completely compatible for use with QML and C++

# Current Status

- Relation between SQL table and C++ Class
    + [X] Create
    + [X] Read 
    + [X] Write
    + [X] Search
- Custom
    + [X] emit signal before inserting data to sql table
    + [X] emit signal after reading data from sql table
    + [X] return JSOn Object when selecting row from table
    
# TODO
- QML & C++
    + [ ] add CRTP to easyORM.h
    + [ ] add NOT NULL to cloumn
    + [ ] add auto fill to tableview of qml
    + [ ] Relation between two table
    + [ ] return JSOn object after executing custom query
    
# SETUP
-------
1) first copy easyORM folder to your project direcotry
2) then go to your .pro file and add this two lines

```

INCLUDEPATH += $$PWD/easyORM

include(easyORM/easyORM.pri)

```

# How to use it
----------------
1- first we need to create an equivalent  of table in C++
1) create simple C++ class and inhirent from easyORM class
2) add INIT_CURD and pass same name of your class
3) for each column in table you need to create a property, for example

```

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

```
2- now you can init class and use predefine CURD methods from easyORM,go to main.cpp

```
    MyDatabase myDatabase;
    if(!myDatabase.initSQLITE3()) // you must call this method to make connection with database....
        return 1 ;
        
    
    
    Clients clients; 
    
    myDatabase.createTable(&clients); // create table 
    
    qDebug() << "tables: " << myDatabase.tables() ; // print all tables names
    
    // example of inserting random data ...
    clients.first_name("a") ; 
    clients.insert() ;
    clients.first_name("b") ; 
    clients.insert() ;
    clients.first_name("c") ; 
    clients.insert() ;
    
    //print all data
    for( int i = 0 ; i < clients.rowCount() ; i++ )
    {
        clients.setCurrentRow(i);
        qDebug() << "C++: " <<clients.first_name() ;
    }



```

3- you can use your class from QML, same as C++ side

```
    Component.onCompleted: {
        for( var i = 0 ; i < clients.rowCount() ; i++ )
        {
            // clients.setCurrentRow(i) will return JSON object to esy manipulate it from QML side
            // example 01 : no auto complete
            console.log(clients.setCurrentRow(i).first_name)
            
            // example 02: with auto complete
            clients.setCurrentRow(i)
            console.log(clients.first_name)
            console.log(clients.last_name)
        }
    }
```
# advantage of easyORM
----------------------
1. interacte with sql table from C++ or QML using same way .
2. auto complet when programming .
3. gerenate schema from C++ class and adapte schema for SQLITE3 or MYSQL .
4. you can add your own method to class to manupilate data before inserting and after reading data from table .
5. macro to generate getter and setter and property to access from qml .


# Note
-------
- easyORM type convertion support only standard types like( int, QString, float, double, QDate, QDatetime, ... ) 
it doesn't support specifique type .....
- method are named same as SQL querys ( select , where, insert, update, ... ) 
- you should create class one and share pointeur to all your programme, or you can initiale your class and each time you will use it you need to call select(), to sync data between your objects.

# Classes
---------
easyORM.h contain CURD function for all child classes ( Create, Update, Read, Delete ) 
mydatabase.h contain generic function for database, (connecte, getAllTable, disconnecte, makeBackup... )
mypropertyhelper.h contain macro to make life easy when programing


