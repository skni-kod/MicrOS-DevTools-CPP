#include "Updater.h"

Updater::Updater(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
    process = new QProcess();

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Updater::processFinished);
    connect(process, &QProcess::errorOccurred, this, &Updater::processError);
}

Updater::~Updater()
{

}

void Updater::checkForUpdates()
{
    if(state == UpdateState::running)
    {
        emit updateAvailable(UpdateStatus::updateAlreadyInProgress);
        return;
    }
    state = UpdateState::running;
    logger->logMessage(tr("Wyszukiwanie aktualizacji"), Logger::LogLevel::Info);
    if(checkForMaintenanceTool() == false)
    {
        logger->logMessage(tr("Nie znaleziono narzędzia do aktualizacji"), Logger::LogLevel::Error);
        emit updateAvailable(UpdateStatus::error);
        state = UpdateState::notRunning;
        return;
    }

    runMaintenanceToolCheck();
}

bool Updater::checkForMaintenanceTool()
{
    QString path = getPathToMaintenanceTool();
    QFile maintenanceToolFile(path);
    if(maintenanceToolFile.exists())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Updater::runMaintenanceToolCheck()
{
    QString path = getPathToMaintenanceTool();
    QStringList params {"check-updates"};
    process->start(path, params);
}

QString Updater::getPathToMaintenanceTool()
{
    QDir catalog = QDir(QCoreApplication::applicationDirPath());
    catalog.cdUp();
    return catalog.absoluteFilePath(toolName);
}

void Updater::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitCode == 0)
    {
        QByteArray stdOutput = process->readAllStandardOutput();
        QString output = QString(stdOutput);
        if(output.contains("<updates>"))
        {
            emit updateAvailable(UpdateStatus::updateAvailable);
        }
        else if(output.contains("There are currently no updates available"))
        {
            emit updateAvailable(UpdateStatus::updateNotAvailable);
        }
        else
        {
            emit updateAvailable(UpdateStatus::error);
        }
    }
    else
    {
        logger->logMessage(ProcessHelper::QProcessExitSatusToString(exitStatus), Logger::LogLevel::Error);
        emit updateAvailable(UpdateStatus::error);
    }
    state = UpdateState::notRunning;
}

void Updater::processError(QProcess::ProcessError error)
{
    logger->logMessage(tr("Błąd podczas wyszukiwania aktualizacji"), Logger::LogLevel::Error);
    logger->logMessage(ProcessHelper::QProcessErrorToString(error), Logger::LogLevel::Error);
    emit updateAvailable(UpdateStatus::error);
    state = UpdateState::notRunning;
}

void Updater::performUpdate()
{
    QString path = getPathToMaintenanceTool();
    QStringList params {"--start-updater"};
    process->startDetached(path, params);
}
