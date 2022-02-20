#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
}

DatabaseManager::~DatabaseManager()
{
    if(databaseInitialized == true)
    {
        database.close();
    }
}

bool DatabaseManager::init(QString databaseName)
{
    // Check if databaseFolder exist, if not create one
    checkDatabaseFolder();

    // Database file and check file
    databaseFile.setFileName(databaseFolder + QDir::separator() + databaseName);
    QFile checkFile(databaseFolder + QDir::separator() + checkFileName);

    // Check if database file exist
    getDatabaseInitState(databaseFile, checkFile);

    // Connect to database
    if(connectToDatabase(databaseName) == false)
    {
        logger->logMessage(tr("Błąd podczas łączenia do bazy danych"), Logger::LogLevel::Error);
        return false;
    }
    // In these states database file be created as new
    // No need to check if database needs to be updated
    if(databaseState == DatabaseInitState::New || databaseState == DatabaseInitState::Deleted)
    {
        if(buildDatabase() == false)
        {
            logger->logMessage(tr("Błąd podczas budownia bazy danych"), Logger::LogLevel::Error);
            return false;
        }

        if(databaseState == DatabaseInitState::New)
        {
            createCheckfile(databaseFolder + QDir::separator() + checkFileName);
            logger->logMessage(tr("Baza danych zbudowana"), Logger::LogLevel::Info);
        }
        else
        {
            logger->logMessage(tr("Baza danych odbudowna"), Logger::LogLevel::Info);
        }
    }

    if(databaseState == DatabaseInitState::CheckDeleted)
    {
        createCheckfile(databaseFolder + QDir::separator() + checkFileName);
        logger->logMessage(tr("Plik .database.txt odtworzony"), Logger::LogLevel::Info);
    }


    if(databaseState == DatabaseInitState::Exist || databaseState == DatabaseInitState::CheckDeleted)
    {
        // Check if database needs to be updated

    }

    logger->logMessage(tr("Inicjalizacja bazy danych zakończona"), Logger::LogLevel::Ok);
    databaseInitialized = true;
    return true;
}

void DatabaseManager::checkDatabaseFolder()
{
    QDir databaseDir;
    if(!databaseDir.cd(databaseFolder))
    {
        databaseDir.mkdir(databaseFolder);
    }
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

void DatabaseManager::getDatabaseInitState(QFile &databaseFile, QFile &checkFile)
{
    if(!databaseFile.exists() && !checkFile.exists())
    {
            // If not exist, create database
            databaseState = DatabaseInitState::New;
            logger->logMessage(tr("Tworzenie bazy danych"), Logger::LogLevel::Info);
    }
    else
    {
        logger->logMessage(tr("Łączenie z bazą danych"), Logger::LogLevel::Info);
        if(databaseFile.exists() && checkFile.exists())
        {
            // If database and check file exist
            databaseState = DatabaseInitState::Exist;
        }
        else if(!databaseFile.exists() && checkFile.exists())
        {
            // If database not exist but check file do
            databaseState = DatabaseInitState::Deleted;
            logger->logMessage(tr("Nie usuwaj bazy danych"), Logger::LogLevel::Warning);
        }
        else if(databaseFile.exists() && !checkFile.exists())
        {
            // If database do exist but check file not
            databaseState = DatabaseInitState::CheckDeleted;
            logger->logMessage(tr("Nie usuwaj pliku .database.txt"), Logger::LogLevel::Warning);
        }
    }
}

bool DatabaseManager::connectToDatabase(const QString &path)
{
    if(QSqlDatabase::isDriverAvailable("QSQLITE") == false)
    {
        logger->logMessage(tr("Sterownik QSQLite nie jest dostępny - nie można połączyć się z bazą danych"), Logger::LogLevel::Error);
        return false;
    }
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseFolder + QDir::separator() + path);

    if(database.open())
    {
        return true;
    }
    else
    {
        QSqlError error = database.lastError();
        DatabaseHelper::QSqlErrorToString(error, logger);
        return false;
    }
}

bool DatabaseManager::buildDatabase()
{

    DatabaseCreator creator(logger);
    return creator.createDatabase(database);
}

bool DatabaseManager::updateDatabase()
{
    DatabaseUpdater updater(logger);
    return updater.checkForUpdate(database, databaseFile);
}
