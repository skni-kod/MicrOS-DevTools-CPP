#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QSqlDatabase>
#include <QVariant>

#include "DatabaseHelper.h"
#include "Version.h"
#include "Utils/Logger.h"

/*!
 * \brief Class that updates database.
 */
class DatabaseUpdater : public QObject
{
    Q_OBJECT

    /*!
     * \brief Holds current database version.
     */
    int databaseVersion = 0;
    /*!
     * \brief logger Logger instance.
     */
    Logger *logger = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param logger Pointer to logger.
     * \param parent Pointer to parent object.
     */
    explicit DatabaseUpdater(Logger *logger, QObject *parent = nullptr);

signals:

public:
    /*!
     * \brief Check if update should be performed and update if yes.
     * \param database Database instance.
     * \param databaseFile Database file instance.
     * \return
     */
    bool checkForUpdate(QSqlDatabase &database, QFile &databaseFile);

private:
    /*!
     * \brief Check if update is needed.
     * \param database Database instance.
     * \return True if update is needed, false otherwise or when error occurs.
     */
    bool isUpdateNeeded(QSqlDatabase &database);
    /*!
     * \brief Perform backup of database file.
     * \details Database will be copied to file with timestamp in name. If copying fails, copy won't be created.
     * \param database Database instance.
     * \param databaseFile Database file instance.
     * \return True if success, false otherwise.
     */
    bool backupDatabaseFile(QSqlDatabase &database, QFile &databaseFile);
    /*!
     * \brief Performs database update.
     * \param database Database instance.
     * \return
     */
    bool updateDatabase(QSqlDatabase &database);
    /*!
     * \brief Updates database version field in database.
     * \param database Database instance.
     * \return True if success, false otherwise.
     */
    bool updateDatabaseVersionField(QSqlDatabase &database);
    /*!
     * \brief Performs dataabse update to version 2.
     * \details Currently only template, does nothing.
     * \param database Database instance.
     * \return True if success, false otherwise.
     */
    bool updateToVersion2(QSqlDatabase &database);
};

#endif // DATABASEUPDATER_H
