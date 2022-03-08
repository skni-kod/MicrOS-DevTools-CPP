#include "ProcessHelper.h"

ProcessHelper::ProcessHelper(QObject *parent) : QObject(parent)
{

}

QString ProcessHelper::QProcessExitSatusToString(const QProcess::ExitStatus &status)
{
    switch(status)
    {
        case QProcess::ExitStatus::NormalExit:
            return tr("Proces zakończył się poprawnie");
        case QProcess::ExitStatus::CrashExit:
            return tr("Proces uległ awarii");
        default:
            return tr("Nieznany status zakończenia procesu");
    }
}

QString ProcessHelper::QProcessErrorToString(const QProcess::ProcessError &error)
{
    switch(error)
    {
        case QProcess::ProcessError::FailedToStart:
            return tr("Procesowi nie udfało się wystartować - brakuje wywołanego programu lub możesz mieć niewystarczające uprawnienia do wywołania programu");
        case QProcess::ProcessError::Crashed:
            return tr("Proces uległ awarii po pomyślnym uruchomieniu");
        case QProcess::ProcessError::Timedout:
            return tr("Ostatnie wywołanie waitFor...() przekroczyło limit czasu - stan procesu jest niezmieniony");
        case QProcess::ProcessError::WriteError:
            return tr("Wystąpił błąd podczas próby pisania do procesu");
        case QProcess::ProcessError::ReadError:
            return tr("Wystąpił błąd podczas próby odczytu z procesu");
        case QProcess::ProcessError::UnknownError:
        default:
            return tr("Nieznany błąd");
    }
}
