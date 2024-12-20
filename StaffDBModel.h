#ifndef STAFFDBMODEL_H
#define STAFFDBMODEL_H

#include <QSqlRelationalTableModel>

class StaffDBModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit StaffDBModel(QObject *parent = nullptr);
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

signals:
};

#endif // STAFFDBMODEL_H
