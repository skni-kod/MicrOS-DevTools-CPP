#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}

void DatabaseManager::init(QString databaseName)
{
    // Check if databaseFolder exist, if not create one
    checkDatabaseFolder();

    // Database file and check file
    QFile databaseFile(databaseFolder + QDir::separator() + databaseName);
    QFile checkFile(databaseFolder + QDir::separator() + checkFileName);

    // Check if database file exist
    getDatabaseInitState(databaseFile, checkFile);

    // In these states database fill be created as new
    // No need to check if database needs to be updated
    if(databaseState == DatabaseInitState::New || databaseState == DatabaseInitState::Deleted)
    {
        buildDatabase(databaseName);
        if(databaseState == DatabaseInitState::New)
        {
            createCheckfile(databaseFolder + QDir::separator() + checkFileName);
            emit logMessage(tr("Baza danych zbudowana"), ConsoleWidget::LogLevel::Info);
        }
        else
        {
            emit logMessage(tr("Baza danych odbudowna"), ConsoleWidget::LogLevel::Info);
        }
    }

    if(databaseState == DatabaseInitState::CheckDeteled)
    {
        createCheckfile(databaseFolder + QDir::separator() + checkFileName);
        emit logMessage(tr("Plik .database.txt odtworzony"), ConsoleWidget::LogLevel::Info);
    }


    if(databaseState == DatabaseInitState::Exist || databaseState == DatabaseInitState::CheckDeteled)
    {
        // Check if database needs to be updated


    }

    emit logMessage(tr("Inicjalizacja bazy danych zakończona"), ConsoleWidget::LogLevel::Ok);
    databaseInitialized = true;
}

void DatabaseManager::checkDatabaseFolder()
{
    QDir databaseDir;
    if(!databaseDir.cd(databaseFolder))
    {
        databaseDir.mkdir(databaseFolder);
    }
}

void DatabaseManager::getDatabaseInitState(QFile &databaseFile, QFile &checkFile)
{
    if(!databaseFile.exists() && !checkFile.exists())
    {
            // If not exist, create database
            databaseState = DatabaseInitState::New;
            emit logMessage(tr("Tworzenie bazy danych"), ConsoleWidget::LogLevel::Info);
    }
    else
    {
        emit logMessage(tr("Łączenie z bazą danych"), ConsoleWidget::LogLevel::Info);
        if(databaseFile.exists() && checkFile.exists())
        {
            // If database and check file exist
            databaseState = DatabaseInitState::Exist;
        }
        else if(!databaseFile.exists() && checkFile.exists())
        {
            // If database not exist but check file do
            databaseState = DatabaseInitState::Deleted;
            emit logMessage(tr("Nie usuwaj bazy danych"), ConsoleWidget::LogLevel::Warning);
        }
        else if(databaseFile.exists() && !checkFile.exists())
        {
            // If database do exist but check file not
            databaseState = DatabaseInitState::CheckDeteled;
            emit logMessage(tr("Nie usuwaj pliku .database.txt"), ConsoleWidget::LogLevel::Warning);
        }
    }
}

void DatabaseManager::buildDatabase(const QString &path)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseFolder + QDir::separator() + path);
    database.open();

    DatabaseCreator creator;
    creator.createDatabase(database);

    database.close();
}

void DatabaseManager::createCheckfile(const QString &path)
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
