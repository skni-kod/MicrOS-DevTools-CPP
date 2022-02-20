#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QString>
#include <QObject>

/*!
 * \brief Class that represents logger
 * \details Allow to log message with different level and send them via signal to places where they should be delivered.
 * Has posibility to include time with message.
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Indicates legel of message.
     */
    enum class LogLevel
    {
        Info,     /*!< Standard type of message. */
        Ok,       /*!< Type of message that communicates success. */
        Error,    /*!< Type of message that indicates error. */
        Warning   /*!< Type of message that indicates warning, but not as ciritcal as error. */
    };

private:
    /*!
     * \brief Append time to log flag.
     * \details When true current time will be added to each line in logs.
     *
     */
    bool appendTime = false;
    /*!
     * \brief Format of time in logs.
     *
     */
    QString timeFormat = "hh:mm:ss.zzz";

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    Logger(QObject *parent = nullptr);
    /*!
     * \brief Constructor.
     * \param appendTime Flag which indicates if time should be added to log line.
     * \param parent Pointer to parent object.
     */
    Logger(bool appendTime, QObject *parent = nullptr);

signals:
    /*!
    * \brief Send line of text to log.
    * \param message Message to print to log console.
    * \param level Level of logged message.
    */
   void messageLogged(QString message, LogLevel level);

public slots:
    /*!
     * \brief Print line of text to log.
     * \param message Message to print to log console.
     * \param level Level of logged message.
     */
    void logMessage(QString message, LogLevel level);
    /*!
     * \brief Setter for \a appendTime
     * \details Controls property that indicates if time should be added to logged message.
     * \param value Value to set.
     */
    void setAppendTime(bool value) noexcept {appendTime = value;}
    /*!
     * \brief Setter for \a timeFormat
     * \details Controls property that indicates format of time that is added to logged message.
     * \param format Format for time.
     */
    void setTimeFormat(QString format) {timeFormat = format;}

public:
    /*!
     * \brief Getter for \a appendTime
     * \return Value of \a appendTime.
     */
    bool getAppendTime() noexcept {return appendTime;}
    /*!
     * \brief Getter for \a timeFormat
     * \return Value of \a timeFormat.
     */
    QString getTimeFormat() {return timeFormat;}
};

#endif // LOGGER_H
