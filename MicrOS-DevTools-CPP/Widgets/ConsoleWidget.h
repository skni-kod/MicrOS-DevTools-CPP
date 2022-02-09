#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>

class ConsoleWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Append time to log flag.
     * @details When true current time will be added to each line in logs.
     */
    bool appendTime = false;
    /**
     * @brief Format of time in logs.
     */
    QString timeFormat = "hh:mm:ss.zzz";
    /**
     * @brief Main layout of widget.
     */
    QVBoxLayout *mainLayout = nullptr;
    /**
     * @brief Main console.
     */
    QTextEdit *consoleTextEdit = nullptr;

public:
    explicit ConsoleWidget(QWidget *parent = nullptr);
    ConsoleWidget(bool appendTime, QWidget *parent = nullptr);
    ~ConsoleWidget();
    QSize sizeHint() const override;

signals:

public slots:
    void printLog(QString text, QColor color);
    void printInfo(QString text);
    void printOk(QString text);
    void printError(QString text);
    void printWarning(QString text);
    void clear();
    void setAppendTime(bool value) noexcept {appendTime = value;}
    void setTimeFormat(QString format) {timeFormat = format;}

public:
    bool getAppendTime() noexcept {return appendTime;}
    QString getTimeFormat() {return timeFormat;}
    QString getLog() {return consoleTextEdit->toPlainText();}
};

#endif // CONSOLEWIDGET_H
