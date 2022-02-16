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
    consoleTextEdit->append(text);
    consoleTextEdit->setTextColor(currentColor);
}

void ConsoleWidget::printMessage(QString message, Logger::LogLevel level)
{
    switch(level)
    {
        case Logger::LogLevel::Info:
        {
            QPalette p = qApp->palette();
            QColor currentColor = p.color(QPalette::WindowText);
            printLog(message, currentColor);
            break;
        }
        case Logger::LogLevel::Ok:
        {
            printLog(message, Qt::green);
            break;
        }
        case Logger::LogLevel::Error:
        {
            printLog(message, Qt::red);
            break;
        }
        case Logger::LogLevel::Warning:
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
