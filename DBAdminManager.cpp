#include "DBAdminManager.h"

DBAdminManager::DBAdminManager(QObject *parent)
    : QObject{parent}
{
    query = new QSqlQuery();
}

void DBAdminManager::createAdmin(QString login, QString password)
{
    QString queryStr;
    queryStr = QString("SELECT * FROM pg_user WHERE usename = '%1';").arg(login);
    if(!query->exec(queryStr))
        qDebug().noquote() << "Select query failed:" << query->lastError();
    if(!query->next())
    {
        queryStr = QString("CREATE USER %1 WITH PASSWORD '%2';").arg(login, password);
        if(!query->exec(queryStr))
            qDebug().noquote() << "Create query failed:" << query->lastError();
    }

    queryStr = QString("ALTER USER %1 WITH SUPERUSER;").arg(login);
    if(!query->exec(queryStr))
        qDebug().noquote() << "Update query failed:" << query->lastError();
}

void DBAdminManager::excludeAdmin(QString login)
{
    QString queryStr = QString("ALTER USER %1 WITH NOSUPERUSER;").arg(login);
    if(!query->exec(queryStr))
        qDebug().noquote() << "Update query failed:" << query->lastError();
}

void DBAdminManager::deleteAdmin(QString login)
{
    qDebug() << "Delete admin:" << login;
    QString queryStr = QString("DROP USER %1;").arg(login);
    if(!query->exec(queryStr))
        qDebug().noquote() << "Delete query failed:" << query->lastError();
}
