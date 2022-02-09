#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    consoleTextEdit = new QTextEdit();
    consoleTextEdit->setReadOnly(true);
    consoleTextEdit->setFontFamily("Courier New");
    mainLayout->addWidget(consoleTextEdit);
    this->setLayout(mainLayout);
}

ConsoleWidget::ConsoleWidget(bool appendTime, QWidget *parent) : ConsoleWidget(parent)
{
    this->appendTime = appendTime;
}

ConsoleWidget::~ConsoleWidget()
{

}

QSize ConsoleWidget::sizeHint() const
{
    return QSize(300, 100);
}

void ConsoleWidget::printLog(QString text, QColor color)
{
    QColor currentColor = consoleTextEdit->textColor();
    consoleTextEdit->setTextColor(color);
    if(appendTime)
    {
        consoleTextEdit->append(QDateTime::currentDateTime().toString(timeFormat) + " " + text);
    }
    else
    {
        consoleTextEdit->append(text);
    }
    consoleTextEdit->setTextColor(currentColor);
}

void ConsoleWidget::printLog(QString message, LogLevel level)
{
    switch(level)
    {
        case LogLevel::Info:
        {
            QPalette p = qApp->palette();
            QColor currentColor = p.color(QPalette::WindowText);
            printLog(message, currentColor);
            break;
        }
        case LogLevel::Ok:
        {
            printLog(message, Qt::green);
            break;
        }
        case LogLevel::Error:
        {
            printLog(message, Qt::red);
            break;
        }
        case LogLevel::Warning:
        {
            printLog(message, Qt::yellow);
            break;
        }
    }
}

void ConsoleWidget::clear()
{
    consoleTextEdit->clear();
}
