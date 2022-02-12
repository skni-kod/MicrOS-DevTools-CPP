#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "Version.h"
#include "ConsoleWidget.h"
#include "DatabaseCreator.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

private:
    enum class DatabaseInitState
    {
        NotChecked,
        New,
        Exist,
        Deleted,
        CheckDeteled
    };
    const QString databaseFolder = "data";
    const QString checkFileName = ".database.txt";

    DatabaseInitState databaseState = DatabaseInitState::NotChecked;
    bool databaseInitialized = false;
    QSqlDatabase database;

public:
    DatabaseManager(QObject *parent = nullptr);

signals:
    void logMessage(QString message, ConsoleWidget::LogLevel logLevel);

public:
    void init(QString databaseName);

private:
    void checkDatabaseFolder();
    void getDatabaseInitState(QFile &databaseFile, QFile &checkFile);
    void buildDatabase(const QString &path);
    void createCheckfile(const QString &path);
};

#endif // DATABASEMANAGER_H
