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
        POSITION_ID,
        DEPARTMENT_ID,
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
    void create(const Employee*);

signals:
};

#endif // STAFFDBMODEL_H
