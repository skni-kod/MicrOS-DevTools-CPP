#ifndef COMPILERTABWIDGET_H
#define COMPILERTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class CompilerTabWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Main label.
     */
    QLabel *mainLabel = nullptr;
    /**
     * @brief Holds information about going to next tab.
     */
    QLabel *nextTabLabel = nullptr;

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    explicit CompilerTabWidget(QWidget *parent = nullptr);
    ~CompilerTabWidget();

signals:

};

#endif // COMPILERTABWIDGET_H
