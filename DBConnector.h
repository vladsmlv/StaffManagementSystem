#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>
#include <QtSql/QtSql>

class DBConnector : public QObject
{
    Q_OBJECT
public:
    explicit DBConnector(QObject *parent = nullptr);
    ~DBConnector();
    static DBConnector* getDBConnector();
    void initDB(QString drivername, QString DBName, QString username, QString hostname, QString password);
    bool openConnection();
    void closeConnection();

private:
    static DBConnector *_instanceDB;
    QSqlDatabase db;

signals:
};

#endif // DBCONNECTOR_H
