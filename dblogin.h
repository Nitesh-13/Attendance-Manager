#ifndef DBLOGIN_H
#define DBLOGIN_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

class dblogin : public QObject
{
    Q_OBJECT
public:
    explicit dblogin(QObject *parent = nullptr);
    QSqlDatabase loginSE;
    QSqlDatabase loginTE;
    bool connectSE();
    bool connectTE();
    void disconnectSE();
    void disconnectTE();
};

#endif // DBLOGIN_H
