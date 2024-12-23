#ifndef STAFFDBMODEL_H
#define STAFFDBMODEL_H

#include <QDateTime>
#include <QDebug>
#include <QSqlRelationalTableModel>
#include "Employee.h"

class StaffDBModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit StaffDBModel(QObject *parent = nullptr);

    enum Column {
        ID,
        LAST_NAME,
        FIRST_NAME,
        PATRONYMIC,
        POSITION,
        DEPARTMENT,
        OFFICIAL_DUTIES,
        DOCUMENT_NUMBER,
        LOGIN,
        ACCESS_LEVEL,
        CURRENT_PASSWORD,
        CREATION_DATE,
        INITIAL_PASSWORD
    };

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

public slots:
    void get(const int);
    void set(const int, const Employee*);
    void create(const Employee*);
    void update(const int, const Employee*);
    bool remove(const int);

signals:
    void sendToEmployeeEntity(const Employee*);

private:
    Employee *employee;
};

#endif // STAFFDBMODEL_H
