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
    Q_PROPERTY(int position READ getPosition WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(int department READ getDepartment WRITE setDepartment NOTIFY departmentChanged FINAL)
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

    QMap<int, int> *positions, *departments;
    QStringList *positionTitles, *departmentTitles;
    QMap<QString, QString> *accessLevels;
    QSqlQuery *query;

    bool addAdministrator = false;
    bool removeAdministrator = false;

    void createComboboxList(QStringList*, QMap<int, int>*, QString);

public:
    explicit Employee(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getPositionsList();
    Q_INVOKABLE QStringList getDepartmentsList();
    Q_INVOKABLE void create();
    Q_INVOKABLE void update(const int);
    Q_INVOKABLE void remove(const int);

    QString getLastName() const;
    void setLastName(const QString&);
    QString getFirstName() const;
    void setFirstName(const QString&);
    QString getPatronymic() const;
    void setPatronymic(const QString&);
    int getPosition() const;
    void setPosition(const int);
    void setPositionWithTitle(QString);
    int getDepartment() const;
    void setDepartment(const int);
    void setDepartmentWithTitle(QString);
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

    int getPositionId() const;
    void setPositionId(int);
    int getDepartmentId() const;
    void setDepartmentId(int);
    QString getAccessLevelAlias() const;
    void setAccessLevelAlias(QString);

public slots:
    void updateEntity(const Employee*);

signals:
    void lastNameChanged();
    void firstNameChanged();
    void patronymicChanged();
    void positionChanged();
    void positionIndexChanged();
    void departmentChanged();
    void officialDutiesChanged();
    void docNumberChanged();
    void loginChanged();
    void accessLevelChanged();
    void initialPasswordChanged();
    void currentPasswordChanged();

    void getSignalToDBModel(const int);
    void createSignalToDBModel(const Employee*);
    void updateSignalToDBModel(const int, const Employee*);
    void deleteSignalToDBModel(const int);
    void createAdmin(QString, QString);
    void removeAdmin(QString);
    void deleteAdmin(QString);
};

#endif // EMPLOYEE_H
