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
    setHeaderData(10, Qt::Horizontal, "Пароль");
    setHeaderData(11, Qt::Horizontal, "Дата создания записи");
    setHeaderData(12, Qt::Horizontal, "Первоначальный пароль");
}

QVariant StaffDBModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}

void StaffDBModel::create(const Employee* employee)
{
    int row = rowCount();
    insertRow(row);

    setData(index(row, LAST_NAME), employee->getLastName());
    setData(index(row, FIRST_NAME), employee->getFirstName());
    setData(index(row, PATRONYMIC), employee->getPatronymic());
    setData(index(row, POSITION_ID), employee->getPositionId());
    setData(index(row, DEPARTMENT_ID), employee->getDepartmentId());
    setData(index(row, OFFICIAL_DUTIES), employee->getOfficialDuties());
    setData(index(row, DOCUMENT_NUMBER), employee->getDocNumber());
    setData(index(row, LOGIN), employee->getLogin());
    setData(index(row, ACCESS_LEVEL), employee->getAccessLevelAlias());
    setData(index(row, CURRENT_PASSWORD), employee->getCurrentPassword());
    setData(index(row, CREATION_DATE), QDateTime::currentDateTime());
    setData(index(row, INITIAL_PASSWORD), employee->getInitialPassword());
    bool result = submitAll();
    if(!result)
        qDebug() << "Error:" << lastError();
    select();
    // return result;
}
