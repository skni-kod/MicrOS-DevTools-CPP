#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    consoleTextEdit = new QTextEdit();
    consoleTextEdit->setReadOnly(true);
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

void ConsoleWidget::printInfo(QString text)
{
    QPalette p = qApp->palette();
    QColor currentColor = p.color(QPalette::WindowText);
    printLog(text, currentColor);
}

void ConsoleWidget::printOk(QString text)
{
    printLog(text, Qt::green);
}

void ConsoleWidget::printError(QString text)
{
    printLog(text, Qt::red);
}

void ConsoleWidget::printWarning(QString text)
{
    printLog(text, Qt::yellow);
}

void ConsoleWidget::clear()
{
    consoleTextEdit->clear();
}
