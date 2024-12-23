#include "Employee.h"

Employee::Employee(QObject *parent)
    : QObject{parent}
{
    query = new QSqlQuery();
    positions = new QMap<int, int>();
    positionTitles = new QStringList();
    departments = new QMap<int, int>();
    departmentTitles = new QStringList();

    accessLevels = new QMap<QString, QString>();
    accessLevels->insert("администратор", "admin");
    accessLevels->insert("сотрудник", "employee");
    accessLevels->insert("особый", "special");
}

void Employee::createComboboxList(QStringList *titlesList, QMap<int, int> *idList, QString table)
{
    titlesList->clear();
    idList->clear();
    query->exec(QString("SELECT title, id FROM %1;").arg(table));
    while (query->next())
    {
        titlesList->append(query->value(0).toString());
        idList->insert((titlesList->length() - 1), query->value(1).toInt());
    }
}

QStringList Employee::getPositionsList()
{
    createComboboxList(positionTitles, positions, "positions");
    return *positionTitles;
}

QStringList Employee::getDepartmentsList()
{
    createComboboxList(departmentTitles, departments, "departments");
    return *departmentTitles;
}

void Employee::create()
{
    emit createSignalToDBModel(this);
}

void Employee::update(const int row)
{
    emit updateSignalToDBModel(row, this);
}

void Employee::getData(const int index)
{
    qDebug() << index;
}

QString Employee::getLastName() const
{
    return m_nLastName;
}

void Employee::setLastName(const QString &lastName)
{
    m_nLastName = lastName;
}

QString Employee::getFirstName() const
{
    return m_nFirstName;
}

void Employee::setFirstName(const QString &firstName)
{
    m_nFirstName = firstName;
}

QString Employee::getPatronymic() const
{
    return m_nPatronymic;
}

void Employee::setPatronymic(const QString &patronymic)
{
    m_nPatronymic = patronymic;
}

int Employee::getPosition() const
{
    return positions->key(m_nPosition);
}

void Employee::setPosition(const int position_ind)
{
    m_nPosition = positions->value(position_ind);
}

void Employee::setPositionWithTitle(QString title)
{
    getPositionsList();
    for(int i = 0; i < positionTitles->length(); i++)
    {
        if(positionTitles->at(i) == title)
        {
            m_nPosition = positions->value(i);
            break;
        }
    }
}

int Employee::getDepartment() const
{
    return departments->key(m_nDepartment);
}

void Employee::setDepartment(const int department_ind)
{
    m_nDepartment = departments->value(department_ind);
}

void Employee::setDepartmentWithTitle(QString title)
{
    getDepartmentsList();
    for(int i = 0; i < departmentTitles->length(); i++)
    {
        if(departmentTitles->at(i) == title)
        {
            m_nDepartment = departments->value(i);
            break;
        }
    }
}

QString Employee::getOfficialDuties() const
{
    return m_nOfficialDuties;
}

void Employee::setOfficialDuties(const QString &officialDuties)
{
    m_nOfficialDuties = officialDuties;
}

QString Employee::getDocNumber() const
{
    return m_nDocNumber;
}

void Employee::setDocNumber(const QString &docNumber)
{
    m_nDocNumber = docNumber;
}

QString Employee::getLogin() const
{
    return m_nLogin;
}

void Employee::setLogin(const QString &login)
{
    m_nLogin = login;
}

QString Employee::getAccessLevel() const
{
    return accessLevels->key(m_nAccessLevel);
}

void Employee::setAccessLevel(const QString &accessLevel)
{
    m_nAccessLevel = accessLevels->value(accessLevel);
}

QString Employee::getInitialPassword() const
{
    return m_nInitialPassword;
}

void Employee::setInitialPassword(const QString &initialPassword)
{
    m_nInitialPassword = initialPassword;
}

QString Employee::getCurrentPassword() const
{
    return m_nCurrentPassword;
}

void Employee::setCurrentPassword(const QString &currentPassword)
{
    m_nCurrentPassword = currentPassword;
}

int Employee::getPositionId() const
{
    return m_nPosition;
}

void Employee::setPositionId(int positionId)
{
    m_nPosition = positionId;
}

int Employee::getDepartmentId() const
{
    return m_nDepartment;
}

void Employee::setDepartmentId(int departmentId)
{
    m_nDepartment = departmentId;
}

QString Employee::getAccessLevelAlias() const
{
    return m_nAccessLevel;
}

void Employee::setAccessLevelAlias(QString accessLevelAlias)
{
    m_nAccessLevel = accessLevelAlias;
}

void Employee::updateEntity(const Employee *employee)
{
    m_nLastName = employee->m_nLastName;
    m_nFirstName = employee->m_nFirstName;
    m_nPatronymic = employee->m_nPatronymic;
    m_nPosition = employee->m_nPosition;
    m_nDepartment = employee->m_nDepartment;
    m_nOfficialDuties = employee->m_nOfficialDuties;
    m_nDocNumber = employee->m_nDocNumber;
    m_nLogin = employee->m_nLogin;
    m_nAccessLevel = employee->m_nAccessLevel;
    m_nInitialPassword = employee->m_nInitialPassword;
    m_nCurrentPassword = employee->m_nCurrentPassword;
}
