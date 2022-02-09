#ifndef STARTTABWIDGET_H
#define STARTTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class StartTabWidget : public QWidget
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
    explicit StartTabWidget(QWidget *parent = nullptr);
    ~StartTabWidget();

signals:

};

#endif // STARTTABWIDGET_H
