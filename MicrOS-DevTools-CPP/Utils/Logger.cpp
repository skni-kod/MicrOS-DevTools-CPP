#include "Logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

Logger::Logger(bool appendTime, QObject *parent) : Logger(parent)
{
    this->appendTime = appendTime;
}

void Logger::logMessage(QString text, LogLevel level)
{
    if(appendTime)
    {
        emit messageLogged(QDateTime::currentDateTime().toString(timeFormat) + " " + text, level);
    }
    else
    {
        emit messageLogged(text, level);
    }
}
