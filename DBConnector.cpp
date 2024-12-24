#include "DBConnector.h"

DBConnector *DBConnector::_instanceDB;

DBConnector::DBConnector(QObject *parent)
    : QObject{parent}
{}

DBConnector::~DBConnector()
{
    closeConnection();
}

DBConnector *DBConnector::getDBConnector()
{
    if (!_instanceDB)
        _instanceDB = new DBConnector();
    return _instanceDB;
}

bool DBConnector::openConnection()
{
    if (!db.open())
    {
        qDebug().noquote() << "Connection failed:" << db.lastError();
        return false;
    }
    qDebug() << "Connection opened.";
    return true;
}

void DBConnector::closeConnection()
{
    if (db.isOpen())
        db.close();
    qDebug() << "Connection closed.";
}

void DBConnector::initDB(QString drivername, QString DBName, QString username, QString hostname, QString password)
{
    db = QSqlDatabase::addDatabase(drivername);
    db.setDatabaseName(DBName);

    db.setUserName(username);
    db.setHostName(hostname);
    db.setPassword(password);
}
