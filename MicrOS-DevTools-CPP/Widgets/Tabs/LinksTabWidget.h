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
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    LinksTabWidget(QWidget *parent = nullptr);
    ~LinksTabWidget();

signals:

};

#endif // LINKSTABWIDGET_H
