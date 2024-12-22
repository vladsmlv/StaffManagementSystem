#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QDebug>

class Employee : public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName NOTIFY lastNameChanged FINAL)
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName NOTIFY firstNameChanged FINAL)
    Q_PROPERTY(QString patronymic READ getPatronymic WRITE setPatronymic NOTIFY patronymicChanged FINAL)
    Q_PROPERTY(QString position READ getPosition WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(QString department READ getDepartment WRITE setDepartment NOTIFY departmentChanged FINAL)
    Q_PROPERTY(QString officialDuties READ getOfficialDuties WRITE setOfficialDuties NOTIFY officialDutiesChanged FINAL)
    Q_PROPERTY(QString docNumber READ getDocNumber WRITE setDocNumber NOTIFY docNumberChanged FINAL)
    Q_PROPERTY(QString login READ getLogin WRITE setLogin NOTIFY loginChanged FINAL)
    Q_PROPERTY(QString accessLevel READ getAccessLevel WRITE setAccessLevel NOTIFY accessLevelChanged FINAL)
    Q_PROPERTY(QString initialPassword READ getInitialPassword WRITE setInitialPassword NOTIFY initialPasswordChanged FINAL)
    Q_PROPERTY(QString currentPassword READ getCurrentPassword WRITE setCurrentPassword NOTIFY currentPasswordChanged FINAL)

    QString m_nLastName;
    QString m_nFirstName;
    QString m_nPatronymic;
    int m_nPosition;
    int m_nDepartment;
    QString m_nOfficialDuties;
    QString m_nDocNumber;
    QString m_nLogin;
    QString m_nAccessLevel;
    QString m_nInitialPassword;
    QString m_nCurrentPassword;

    QMap<QString, int> *positions, *departments;
    QMap<QString, QString> *accessLevels;
    QSqlQuery *query;

public:
    explicit Employee(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getPositionsList();
    Q_INVOKABLE QStringList getDepartmentsList();
    Q_INVOKABLE void submit();

    QString getLastName() const;
    void setLastName(const QString&);
    QString getFirstName() const;
    void setFirstName(const QString&);
    QString getPatronymic() const;
    void setPatronymic(const QString&);
    QString getPosition() const;
    void setPosition(const QString&);
    QString getDepartment() const;
    void setDepartment(const QString&);
    QString getOfficialDuties() const;
    void setOfficialDuties(const QString&);
    QString getDocNumber() const;
    void setDocNumber(const QString&);
    QString getLogin() const;
    void setLogin(const QString&);
    QString getAccessLevel() const;
    void setAccessLevel(const QString&);
    QString getInitialPassword() const;
    void setInitialPassword(const QString&);
    QString getCurrentPassword() const;
    void setCurrentPassword(const QString&);

    // Q_INVOKABLE QString getLastName() const;
    // Q_INVOKABLE void setLastName(const QString&);
    // Q_INVOKABLE QString getFirstName() const;
    // Q_INVOKABLE void setFirstName(const QString&);
    // Q_INVOKABLE QString getPatronymic() const;
    // Q_INVOKABLE void setPatronymic(const QString&);
    // Q_INVOKABLE QString getPosition() const;
    // Q_INVOKABLE void setPosition(const QString&);
    // Q_INVOKABLE QString getDepartment() const;
    // Q_INVOKABLE void setDepartment(const QString&);
    // Q_INVOKABLE QString getOfficialDuties() const;
    // Q_INVOKABLE void setOfficialDuties(const QString&);
    // Q_INVOKABLE QString getDocNumber() const;
    // Q_INVOKABLE void setDocNumber(const QString&);
    // Q_INVOKABLE QString getLogin() const;
    // Q_INVOKABLE void setLogin(const QString&);
    // Q_INVOKABLE QString getAccessLevel() const;
    // Q_INVOKABLE void setAccessLevel(const QString&);
    // Q_INVOKABLE QString getInitialPassword() const;
    // Q_INVOKABLE void setInitialPassword(const QString&);
    // Q_INVOKABLE QString getCurrentPassword() const;
    // Q_INVOKABLE void setCurrentPassword(const QString&);

    int getPositionId() const;
    int getDepartmentId() const;
    QString getAccessLevelAlias() const;

signals:
    void lastNameChanged();
    void firstNameChanged();
    void patronymicChanged();
    void positionChanged();
    void departmentChanged();
    void officialDutiesChanged();
    void docNumberChanged();
    void loginChanged();
    void accessLevelChanged();
    void initialPasswordChanged();
    void currentPasswordChanged();

    void sendToDBModel(const Employee*);
};

#endif // EMPLOYEE_H
