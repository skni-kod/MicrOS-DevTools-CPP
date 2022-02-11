#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}

void DatabaseManager::init(QString path)
{
    // Check if database file exist
    QFile databaseFile(path);
    QFileInfo databaseFileInfo(databaseFile);
    QFile checkFile(databaseFileInfo.absolutePath() + QDir::separator() + checkFileName);

    if(databaseFile.exists() && checkFile.exists())
    {
        // If database and check file exist
        emit logMessage(tr("Inicjalizacja bazy danych zakończona"), ConsoleWidget::LogLevel::Info);
    }
    else if(!databaseFile.exists() && !checkFile.exists())
    {
        // If not exist, create database
        emit logMessage(tr("Tworzenie bazy danych"), ConsoleWidget::LogLevel::Info);
        rebuildDatabase(path);
        createCheckfile(databaseFileInfo.absolutePath() + QDir::separator() + checkFileName);
        emit logMessage(tr("Baza danych zbudowana"), ConsoleWidget::LogLevel::Info);
    }
    else if(!databaseFile.exists() && checkFile.exists())
    {
        // If database not exist but check file do
        emit logMessage(tr("Nie usuwaj bazy danych"), ConsoleWidget::LogLevel::Warning);
        rebuildDatabase(path);
        emit logMessage(tr("Baza danych odbudowna"), ConsoleWidget::LogLevel::Info);
    }
    else if(databaseFile.exists() && !checkFile.exists())
    {
        // If database do exist but check file not
        emit logMessage(tr("Nie usuwaj pliku .database.txt"), ConsoleWidget::LogLevel::Warning);
        createCheckfile(databaseFileInfo.absolutePath() + QDir::separator() + checkFileName);
        emit logMessage(tr("Plik .database.txt odtworzony"), ConsoleWidget::LogLevel::Info);
    }
}

void DatabaseManager::rebuildDatabase(QString path)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
    QSqlQuery query(database);
    query.exec("CREATE TABLE SystemVersion (id INTEGER NOT NULL PRIMARY KEY, component TEXT NOT NULL, version TEXT NOT NULL)");
    database.close();
}

void DatabaseManager::createCheckfile(QString path)
{
    QFile checkFile(path);
    checkFile.open(QIODevice::WriteOnly | QIODevice::Text);

#ifdef Q_OS_WIN
    int attr = GetFileAttributes(path.toStdWString().c_str());
        if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0)
        {
            SetFileAttributes(path.toStdWString().c_str(), attr | FILE_ATTRIBUTE_HIDDEN);
        }
#endif

    checkFile.close();
}
