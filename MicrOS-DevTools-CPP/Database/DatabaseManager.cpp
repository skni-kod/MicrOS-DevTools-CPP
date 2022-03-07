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

bool DatabaseManager::init()
{
    // Check if databaseFolder exist, if not create one
    checkDatabaseFolder();

    // Database file and check file
    databaseFile.setFileName(databaseFolder + "/" + databaseFileName);
    QFile checkFile(databaseFolder + "/" + checkFileName);

    // Check if database file exist
    getDatabaseInitState(databaseFile, checkFile);

    // Connect to database
    if(connectToDatabase(databaseFileName) == false)
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
            createCheckfile(databaseFolder + "/" + checkFileName);
            logger->logMessage(tr("Baza danych zbudowana"), Logger::LogLevel::Info);
        }
        else
        {
            logger->logMessage(tr("Baza danych odbudowna"), Logger::LogLevel::Info);
        }
    }

    if(databaseState == DatabaseInitState::CheckDeleted)
    {
        createCheckfile(databaseFolder + "/" + checkFileName);
        logger->logMessage(tr("Plik .database.txt odtworzony"), Logger::LogLevel::Info);
    }

    if(databaseState == DatabaseInitState::Exist || databaseState == DatabaseInitState::CheckDeleted)
    {
        // Check if database needs to be updated
        if(updateDatabase() == false)
        {
            return false;
        }
    }

    if(checkAndUpdateApplicationVersionField() == false)
    {
        logger->logMessage(tr("Błąd przy sprawdzaniu numeru wersji aplikacji"), Logger::LogLevel::Error);
        return false;
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
        if(databaseDir.mkdir(databaseFolder) == false)
        {
            logger->logMessage(tr("Nie można utworzyć folderu dla bazy danych"), Logger::LogLevel::Error);
        }
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
    database.setDatabaseName(databaseFolder + "/" + path);

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
    return updater.checkForUpdateAndUpdate(database, databaseFile);
}

bool DatabaseManager::checkAndUpdateApplicationVersionField()
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(DatabaseHelper::QSqlQueryExec(query, "SELECT version FROM SystemVersion WHERE component = 'Application version'", logger) == false)
    {
        return false;
    }
    query.next();
    QString applicationVersionStr = query.value(0).toString();
    if(applicationVersionStr == APPLICATION_VERSION)
    {
        return true;
    }

    // Update SystemVersion
    if(DatabaseHelper::QSqlQueryPrepare(query, "UPDATE SystemVersion SET version = :version WHERE component = :component", logger) == false)
    {
        return false;
    }
    query.bindValue(":component", APPLICATION_VERSION_SETTING);
    query.bindValue(":version", APPLICATION_VERSION);
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }
    logger->logMessage(tr("Zaktualizowano numer wersji aplikacji w bazie danych"), Logger::LogLevel::Info);
    return true;
}
