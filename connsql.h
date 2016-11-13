#ifndef CONNSQL_H
#define CONNSQL_H

#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QString>

class ConnSQL
{
private:
    QSqlDatabase db;
public:
    ConnSQL(QString, QString, QString, QString);
};

#endif // CONNSQL_H
