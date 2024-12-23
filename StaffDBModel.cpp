#include "StaffDBModel.h"

StaffDBModel::StaffDBModel(QObject *parent)
    : QSqlRelationalTableModel{parent}
{
    employee = new Employee();

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
    set(row, employee);
    bool result = submitAll();
    if(!result)
        qDebug() << "Error:" << lastError();
    select();
}

void StaffDBModel::update(const int row, const Employee *employee)
{
    set(row, employee);
    bool result = submitAll();
    if(!result)
        qDebug() << "Error:" << lastError();
    select();
}

void StaffDBModel::get(const int row)
{
    employee->setLastName(data(index(row, LAST_NAME)).toString());
    employee->setFirstName(data(index(row, FIRST_NAME)).toString());
    employee->setPatronymic(data(index(row, PATRONYMIC)).toString());
    employee->setPositionWithTitle(data(index(row, POSITION)).toString());
    employee->setDepartmentWithTitle(data(index(row, DEPARTMENT)).toString());
    employee->setOfficialDuties(data(index(row, OFFICIAL_DUTIES)).toString());
    employee->setDocNumber(data(index(row, DOCUMENT_NUMBER)).toString());
    employee->setLogin(data(index(row, LOGIN)).toString());
    employee->setAccessLevelAlias(data(index(row, ACCESS_LEVEL)).toString());
    employee->setCurrentPassword(data(index(row, CURRENT_PASSWORD)).toString());
    employee->setInitialPassword(data(index(row, INITIAL_PASSWORD)).toString());

    emit sendToEmployeeEntity(employee);
}

void StaffDBModel::set(const int row, const Employee *employee)
{
    setData(index(row, LAST_NAME), employee->getLastName());
    setData(index(row, FIRST_NAME), employee->getFirstName());
    setData(index(row, PATRONYMIC), employee->getPatronymic());
    setData(index(row, POSITION), employee->getPositionId());
    setData(index(row, DEPARTMENT), employee->getDepartmentId());
    setData(index(row, OFFICIAL_DUTIES), employee->getOfficialDuties());
    setData(index(row, DOCUMENT_NUMBER), employee->getDocNumber());
    setData(index(row, LOGIN), employee->getLogin());
    setData(index(row, ACCESS_LEVEL), employee->getAccessLevelAlias());
    setData(index(row, CURRENT_PASSWORD), employee->getCurrentPassword());
    setData(index(row, CREATION_DATE), QDateTime::currentDateTime());
    setData(index(row, INITIAL_PASSWORD), employee->getInitialPassword());
}

bool StaffDBModel::remove(const int row)
{
    if (row < 0 || row >= rowCount())
    {
        qDebug() << "Error: row index out of range";
        return false;
    }

    removeRow(row);
    bool result = submitAll();
    if (!result)
    {
        qDebug() << lastError();
        revertAll();
    }
    return result;
}
