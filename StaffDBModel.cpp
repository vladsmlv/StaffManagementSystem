#include "StaffDBModel.h"

StaffDBModel::StaffDBModel(QObject *parent)
    : QSqlRelationalTableModel{parent}
{
    setTable("staff");
    setRelation(4, QSqlRelation("positions", "id", "title"));
    setRelation(5, QSqlRelation("departments", "id", "title"));
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setSort(0, Qt::AscendingOrder);
    select();
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Фамилия");
    setHeaderData(2, Qt::Horizontal, "Имя");
    setHeaderData(3, Qt::Horizontal, "Отчество");
    setHeaderData(4, Qt::Horizontal, "Должность");
    setHeaderData(5, Qt::Horizontal, "Подразделение");
    setHeaderData(6, Qt::Horizontal, "Функции");
    setHeaderData(7, Qt::Horizontal, "Номер документа");
    setHeaderData(8, Qt::Horizontal, "Логин");
    setHeaderData(9, Qt::Horizontal, "Уровень доступа");
    setHeaderData(10, Qt::Horizontal, "Первичный пароль");
    setHeaderData(11, Qt::Horizontal, "Дата создания профиля");
}

QVariant StaffDBModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
