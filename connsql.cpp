#include "connsql.h"
#include <QMessageBox>


ConnSQL::ConnSQL(QString host, QString dbName, QString user, QString passwd)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(passwd);

    if(db.open()) {
        qDebug()<<"Success to connect to mysql!";
//        QMessageBox::information(this, "Connected",
//                                 "Success to connect to mysql!");
    } else {
        qDebug()<<"Failed to connect to mysql!";
    }
}
