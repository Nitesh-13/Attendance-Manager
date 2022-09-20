#include "dblogin.h"

dblogin::dblogin(QObject *parent)
    : QObject{parent}
{
}

// mysql credentials for SE database
bool dblogin::connectSE()
{
    loginSE = QSqlDatabase::addDatabase("QMYSQL");
    loginSE.setHostName("localhost"); // remote mysql host here
    loginSE.setUserName("");          // mysql username here
    loginSE.setPassword("");          // mysql password here
    loginSE.setDatabaseName("");      // database name here
    if (loginSE.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// mysql credentials for TE database
bool dblogin::connectTE()
{
    loginTE = QSqlDatabase::addDatabase("QMYSQL");
    loginTE.setHostName("localhost"); // remote mysql host here
    loginTE.setUserName("");          // mysql username here
    loginTE.setPassword("");          // mysql password here
    loginTE.setDatabaseName("");      // database name here
    if (loginTE.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void dblogin::disconnectSE()
{
    loginSE.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void dblogin::disconnectTE()
{
    loginTE.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
