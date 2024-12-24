#ifndef DBADMINMANAGER_H
#define DBADMINMANAGER_H

#include <QObject>
#include <QtSql/QtSql>

class DBAdminManager : public QObject
{
    Q_OBJECT
private:
    QSqlQuery* query;
public:
    explicit DBAdminManager(QObject *parent = nullptr);

signals:

public slots:
    void createAdmin(QString, QString);
    void excludeAdmin(QString);
    void deleteAdmin(QString);
};

#endif // DBADMINMANAGER_H
