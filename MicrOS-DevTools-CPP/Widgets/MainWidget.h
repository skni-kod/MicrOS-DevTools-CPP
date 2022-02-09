#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSaveFile>
#include <QTabWidget>
#include <QTextStream>
#include <QWidget>
#include <QVBoxLayout>

#include "ConsoleWidget.h"
#include "Tabs/LinksTabWidget.h"
#include "Tabs/StartTabWidget.h"
#include "Tabs/ToolsTabWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Pointer to main menu.
     */
    QMenuBar *menuBar = nullptr;
    /**
     * @brief Pointer to program menu.
     */
    QMenu *programMenu = nullptr;
    /**
     * @brief Action for exit.
     */
    QAction *exitAction = nullptr;

    QMenu *tabsMenu = nullptr;
    QAction *startTabAction = nullptr;
    QAction *liknsTabAction = nullptr;
    QAction *toolsTabAction = nullptr;
    QAction *environmentTabAction = nullptr;
    QAction *buildingTabAction = nullptr;
    /**
     * @brief Pointer to console menu.
     */
    QMenu *consoleMenu = nullptr;
    /**
     * @brief Action for saving console log.
     */
    QAction *saveConsoleAction = nullptr;
    /**
     * @brief Action for clean console.
     */
    QAction *cleanConsoleAction = nullptr;
    /**
     * @brief Pointer to help menu.
     */
    QMenu *helpMenu = nullptr;
    /**
     * @brief Action for about.
     */
    QAction *aboutAction = nullptr;
    /**
     * @brief Action for about MicrOS.
     */
    QAction *aboutMicrosAction = nullptr;
    /**
     * @brief Action for about Qt.
     */
    QAction *aboutQtAction = nullptr;

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

    /**
     * @brief Main tab wiget.
     */
    QTabWidget *mainTabWidget = nullptr;

    LinksTabWidget *linksTabWidget = nullptr;
    StartTabWidget *startTabWidget = nullptr;
    ToolsTabWidget *toolsTabWidget = nullptr;

    QGroupBox *consoleGroupBox = nullptr;
    QVBoxLayout *consoleLayout = nullptr;
    ConsoleWidget *consoleWidget = nullptr;


public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    /**
     * @brief Function that shows message box about program.
     */
    void showAboutMessage();
    /**
     * @brief Function that shows message box about MicrOS.
     */
    void showAboutMicrosMessage();
    /**
     * @brief Function that saves log to file.
     */
    void saveLogToFile();
};
#endif // MAINWIDGET_H
