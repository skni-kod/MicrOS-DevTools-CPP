#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The ConsoleWidget class.
 * \details Defines widget that can act as console.
 * Prints messages with 4 different colored levels.
 * Has posibility to include time with message.
 */
class ConsoleWidget : public QWidget
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
    /*!
     *  \brief Main layout of widget.
     */
    QVBoxLayout *mainLayout = nullptr;
    /*!
     *  \brief Main text edit which plays console role.
     */
    QTextEdit *consoleTextEdit = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    explicit ConsoleWidget(QWidget *parent = nullptr);
    /*!
     * \brief Constructor.
     * \param appendTime Flag which indicates if time should be added to log line.
     * \param parent Pointer to parent widget.
     */
    ConsoleWidget(bool appendTime, QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~ConsoleWidget();
    /*!
     * \brief Provides recommended size for the widget.
     * \return Recommended size for the widget.
     */
    QSize sizeHint() const override;

signals:

public slots:
    /*!
     * \brief Print line of text to log.
     * \param message Message to print to log console.
     * \param level Level of logged message.
     */
    void printMessage(QString message, LogLevel level);
    /*!
     * \brief Clears log console.
     */
    void clear();
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
    /*!
     * \brief Getter for content of log console
     * \return Whole log stored by console.
     */
    QString getLog() {return consoleTextEdit->toPlainText();}

private:
    /*!
     * \brief Prints message to log console.
     * \param text Message to log.
     * \param color Color of message.
     */
    void printLog(QString text, QColor color);
};

#endif // CONSOLEWIDGET_H
