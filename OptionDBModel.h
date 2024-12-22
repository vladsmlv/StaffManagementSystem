#ifndef OPTIONDBMODEL_H
#define OPTIONDBMODEL_H

#include <QObject>
#include <QSqlQueryModel>

class OptionDBModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit OptionDBModel(QObject *parent = nullptr);

signals:
};

#endif // OPTIONDBMODEL_H
