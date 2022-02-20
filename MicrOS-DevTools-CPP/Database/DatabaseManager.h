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
#include "DatabaseUpdater.h"
#include "Version.h"
#include "Utils/Logger.h"

/*!
 * \brief The DatabaseManager class
 * \details Manages database and its connection. Handles creation of new database and update existing one.
 */
class DatabaseManager : public QObject
{
    Q_OBJECT

private:
    /*!
     * \brief State of database during initial check.
     */
    enum class DatabaseInitState
    {
        NotChecked,    /*!< State not checked yet. */
        New,           /*!< It's first time when database is created. */
        Exist,         /*!< Database already exist. */
        Deleted,       /*!< Database has been deleted. */
        CheckDeleted   /*!< Check file has been deleted. */
    };

    /*!
     * \brief Folder where database is stored.
     */
    const QString databaseFolder = "data";

    /*!
     * \brief Check file name.
     */
    const QString checkFileName = ".database.txt";

    /*!
     * \brief Instance of logger.
     */
    Logger *logger = nullptr;

    /*!
     * \brief Enum with database init state.
     */
    DatabaseInitState databaseState = DatabaseInitState::NotChecked;

    /*!
     * \brief Flag with holds inforamtion if database was successfully initialized.
     */
    bool databaseInitialized = false;

    /*!
     * \brief Database instance class.
     */
    QSqlDatabase database;

    /*!
     * \brief Dataabse file instance.
     */
    QFile databaseFile;

public:
    /*!
     * \brief Default constructor.
     * \param logger Pointer to logger.
     * \param parent Pointer to parent object.
     */
    explicit DatabaseManager(Logger *logger, QObject *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~DatabaseManager();

public:
    /*!
     * \brief Initializes database.
     * \param databaseName Name of database file.
     * \return True if success, false otherwise.
     */
    bool init(QString databaseName);

private:
    /*!
     * \brief Check if folder where database will be stored exist.
     */
    void checkDatabaseFolder();
    /*!
     * \brief Creates check file for database.
     * \param path Path to file.
     */
    void createCheckfile(const QString &path);
    /*!
     * \brief Check state of database.
     * \param databaseFile Database file instance.
     * \param checkFile Check file instance.
     */
    void getDatabaseInitState(QFile &databaseFile, QFile &checkFile);
    /*!
     * \brief Performs connection to database.
     * \param path Path to database file.
     * \return True if success, false otherwise.
     */
    bool connectToDatabase(const QString &path);
    /*!
     * \brief Creates database by calling /a DatabaseCreator.
     * \return True if success, false otherwise.
     */
    bool buildDatabase();
    /*!
     * \brief Updates database by calling /a DatabaseCreator.
     * \return True if success, false otherwise.
     */
    bool updateDatabase();

};

#endif // DATABASEMANAGER_H
