#include "Employee.h"

Employee::Employee(QObject *parent)
    : QObject{parent}
{
    query = new QSqlQuery();
    positions = new QMap<QString, int>();
    departments = new QMap<QString, int>();

    accessLevels = new QMap<QString, QString>();
    accessLevels->insert("администратор", "admin");
    accessLevels->insert("сотрудник", "employee");
    accessLevels->insert("особый", "special");
}

QStringList Employee::getPositionsList()
{
    query->exec("SELECT title, id FROM positions;");
    while (query->next())
    {
        positions->insert(query->value(0).toString(), query->value(1).toInt());
    }

    return QStringList(positions->keys());
}

QStringList Employee::getDepartmentsList()
{
    query->exec("SELECT title, id FROM departments;");
    while (query->next())
    {
        departments->insert(query->value(0).toString(), query->value(1).toInt());
    }

    return QStringList(departments->keys());
}

void Employee::submit()
{
    emit sendToDBModel(this);
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

QString Employee::getPosition() const
{
    return positions->key(m_nPosition);
}

void Employee::setPosition(const QString &position)
{
    m_nPosition = positions->value(position);
}

QString Employee::getDepartment() const
{
    return departments->key(m_nDepartment);
}

void Employee::setDepartment(const QString &department)
{
    m_nDepartment = departments->value(department);
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

int Employee::getDepartmentId() const
{
    return m_nDepartment;
}

QString Employee::getAccessLevelAlias() const
{
    return m_nAccessLevel;
}
