#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QApplication>
#include <QColor>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>

class ConsoleWidget : public QWidget
{
    Q_OBJECT

private:

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

    QTextEdit *consoleTextEdit = nullptr;

public:
    ConsoleWidget(QWidget *parent = nullptr);
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
};

#endif // CONSOLEWIDGET_H
