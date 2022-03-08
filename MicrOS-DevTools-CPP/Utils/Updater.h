#ifndef UPDATER_H
#define UPDATER_H

#include <QDebug>

#include <QApplication>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QProcess>

#include "Utils/Logger.h"
#include "Utils/ProcessHelper.h"

/*!
 * \brief Class with logic to perform update.
 */
class Updater : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Indicates result of checking update.
     */
    enum class UpdateStatus
    {
        updateAvailable,          /*!< Update is available. */
        updateNotAvailable,       /*!< Update is not available. */
        error,                    /*!< There was error during update check. */
        updateAlreadyInProgress   /*!< Checking for update is already in progress. */
    };

private:
    /*!
     * \brief Describes status of checking update.
     */
    enum class UpdateState
    {
        notRunning, /*!< Check for update is not running. */
        running     /*!< Check for update is already running. */
    };

    /*!
     * \brief Name of the maintenance tool.
     */
    const QString toolName = "Instalator.exe";

    /*!
     * \brief State of checking update tool
     */
    UpdateState state = UpdateState::notRunning;

    /*!
     * \brief Logger instance.
     */
    Logger *logger = nullptr;

    /*!
     * \brief Holds update process.
     */
    QProcess *process = nullptr;

public:
    /*!
     * \brief Constructor.
     * \param logger Pointer to logger.
     * \param parent Pointer to parent object.
     */
    explicit Updater(Logger *logger, QObject *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~Updater();

signals:
    /*!
     * \brief Signal that is send after checking for update.
     * \param status Result of check.
     */
    void updateAvailable(Updater::UpdateStatus status);

public slots:
    /*!
     * \brief Function that check if updates exist.
     */
    void checkForUpdates();
    /*!
     * \brief Calls update tool to perform update.
     */
    void performUpdate();

private:
    /*!
     * \brief Check if maintenance tool exist.
     * \return True if exist, false otherwise.
     */
    bool checkForMaintenanceTool();
    /*!
     * \brief Run process to check for updates.
     * \details Result of process output will be handled in functions \a processFinished and \a processError.
     */
    void runMaintenanceToolCheck();
    /*!
     * \brief Creates path to maintenance tool.
     * \return Path to maintenance tool.
     */
    QString getPathToMaintenanceTool();

private slots:
    /*!
     * \brief Called when check for update process is finished.
     * \param exitCode Process exit code.
     * \param exitStatus Process exit status.
     */
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    /*!
     * \brief Called when check for update process is errors.
     * \param error Process error information.
     */
    void processError(QProcess::ProcessError error);

};

#endif // UPDATER_H
