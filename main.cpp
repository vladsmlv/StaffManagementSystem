#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtSql/QtSql>
#include "DBConnector.h"
#include "StaffDBModel.h"
#include "Employee.h"
#include "DBAdminManager.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<Employee>("com.staffmanagementsystem.Employee", 1, 0, "Employee");

    DBConnector* dbConnector = new DBConnector(&app);
    dbConnector->initDB("QPSQL", "Staff", "sa", "localhost", "sysadmin1029");
    dbConnector->openConnection();

    DBAdminManager *adminManager = new DBAdminManager();
    StaffDBModel *staffModel = new StaffDBModel();
    Employee *employee = new Employee();

    QObject::connect(employee, &Employee::getSignalToDBModel, staffModel, &StaffDBModel::get);
    QObject::connect(employee, &Employee::createSignalToDBModel, staffModel, &StaffDBModel::create);
    QObject::connect(employee, &Employee::updateSignalToDBModel, staffModel, &StaffDBModel::update);
    QObject::connect(employee, &Employee::deleteSignalToDBModel, staffModel, &StaffDBModel::remove);
    QObject::connect(employee, &Employee::createAdmin, adminManager, &DBAdminManager::createAdmin);
    QObject::connect(employee, &Employee::removeAdmin, adminManager, &DBAdminManager::excludeAdmin);
    QObject::connect(employee, &Employee::deleteAdmin, adminManager, &DBAdminManager::deleteAdmin);
    QObject::connect(staffModel, &StaffDBModel::sendToEmployeeEntity, employee, &Employee::updateEntity);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("staffModel", staffModel);
    engine.rootContext()->setContextProperty("employeeObj", employee);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
