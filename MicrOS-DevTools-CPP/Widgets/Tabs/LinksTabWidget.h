#ifndef LINKSTABWIDGET_H
#define LINKSTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class LinksTabWidget : public QWidget
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
    explicit LinksTabWidget(QWidget *parent = nullptr);
    ~LinksTabWidget();

signals:

};

#endif // LINKSTABWIDGET_H
