#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtSql/QtSql>
#include "DBConnector.h"
#include "StaffDBModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    DBConnector* dbConnector = new DBConnector(&app);
    dbConnector->initDB("QPSQL", "Staff", "sa", "localhost", "sysadmin1029");
    if (dbConnector->openConnection())
        qDebug() << "Connection opened.";

    StaffDBModel *staffModel = new StaffDBModel(&app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("staffModel", staffModel);

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
