#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "DatabaseCreator.h"
#include "DatabaseHelper.h"
#include "Version.h"
#include "Utils/Logger.h"

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

    Logger *logger = nullptr;

    DatabaseInitState databaseState = DatabaseInitState::NotChecked;
    bool databaseInitialized = false;
    QSqlDatabase database;

public:
    explicit DatabaseManager(Logger *logger, QObject *parent = nullptr);
    ~DatabaseManager();

public:
    bool init(QString databaseName);

private:
    void checkDatabaseFolder();
    void createCheckfile(const QString &path);
    void getDatabaseInitState(QFile &databaseFile, QFile &checkFile);
    bool connectToDatabase(const QString &path);
    bool buildDatabase();

};

#endif // DATABASEMANAGER_H
