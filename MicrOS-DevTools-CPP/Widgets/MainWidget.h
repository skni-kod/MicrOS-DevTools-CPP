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
#include <QStandardPaths>
#include <QTabWidget>
#include <QTextStream>
#include <QWidget>
#include <QVBoxLayout>

#include "ConsoleWidget.h"
#include "Database/DatabaseManager.h"
#include "Tabs/BuildingTabWidget.h"
#include "Tabs/CompilerTabWidget.h"
#include "Tabs/EnvironmentTabWidget.h"
#include "Tabs/LinksTabWidget.h"
#include "Tabs/StartTabWidget.h"
#include "Tabs/ToolsTabWidget.h"
#include "Utils/Logger.h"

/*!
 * \brief The MainWidget class
 * \details Main widget of application. Stores menu bar, all tabs and console.
 */
class MainWidget : public QWidget
{
    Q_OBJECT

private:
    /// Menu bar

    /*!
     * \brief Pointer to main menu.
     */
    QMenuBar *menuBar = nullptr;
    /*!
     * \brief Pointer to program menu.
     */
    QMenu *programMenu = nullptr;
    /*!
     * \brief Action for exit.
     */
    QAction *exitAction = nullptr;
    /*!
     * \brief  Pointer to tabs menu.
     */
    QMenu *tabsMenu = nullptr;
    /*!
     * \brief Action for selecting start tab.
     */
    QAction *startTabAction = nullptr;
    /*!
     * \brief Action for selecting links tab.
     */
    QAction *liknsTabAction = nullptr;
    /*!
     * \brief Action for selecting tools tab.
     */
    QAction *toolsTabAction = nullptr;
    /*!
     * \brief Action for selecting environment tab.
     */
    QAction *environmentTabAction = nullptr;
    /*!
     * \brief Action for selecting compiler tab.
     */
    QAction *compilerTabAction = nullptr;
    /*!
     * \brief Action for selecting building tab.
     */
    QAction *buildingTabAction = nullptr;
    /*!
     * \brief Pointer to console menu.
     */
    QMenu *consoleMenu = nullptr;
    /*!
     * \brief Action for saving console log.
     */
    QAction *saveConsoleAction = nullptr;
    /*!
     * \brief Action for toggle console visibility.
     */
    QAction *showConsoleAction = nullptr;
    /*!
     * \brief Action for clean console.
     */
    QAction *cleanConsoleAction = nullptr;
    /*!
     * \brief Pointer to help menu.
     */
    QMenu *helpMenu = nullptr;
    /*!
     * \brief Action for about.
     */
    QAction *aboutAction = nullptr;
    /*!
     * \brief Action for about MicrOS.
     */
    QAction *aboutMicrosAction = nullptr;
    /*!
     * \brief Action for about Qt.
     */
    QAction *aboutQtAction = nullptr;

    /// Tabs

    /*!
     * \brief Main tab wiget.
     */
    QTabWidget *mainTabWidget = nullptr;
    /*!
     * \brief Start tab.
     */
    StartTabWidget *startTabWidget = nullptr;
    /*!
     * \brief Tabs with links.
     */
    LinksTabWidget *linksTabWidget = nullptr;
    /*!
     * \brief Tabs with tools.
     */
    ToolsTabWidget *toolsTabWidget = nullptr;
    /*!
     * \brief Tabs with enviroment settings.
     */
    EnvironmentTabWidget *environmentTabWidget = nullptr;
    /*!
     * \brief Tabs with compiler settings.
     */
    CompilerTabWidget *compilerTabWidget = nullptr;
    /*!
     * \brief Tabs with building settings.
     */
    BuildingTabWidget *buildingTabWidget = nullptr;

    /// Console

    /*!
     * \brief Group box for console.
     */
    QGroupBox *consoleGroupBox = nullptr;
    /*!
     * \brief Console widget.
     */
    ConsoleWidget *consoleWidget = nullptr;

    /// Layouts

    /*!
     * \brief Main layout of window.
     * \details From up to down: menu, tabs, console.
     */
    QVBoxLayout *mainLayout = nullptr;
    /*!
     * \brief Layout for console.
     */
    QVBoxLayout *consoleLayout = nullptr;

    /*!
     * \brief Default loger instance.
     */
    Logger *logger = nullptr;

    /*!
     * \brief Database manager instance.
     */
    DatabaseManager *databaseManager = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    explicit MainWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~MainWidget();

private slots:
    /*!
     * \brief Function that shows message box about program.
     */
    void showAboutMessage();
    /*!
     * \brief Function that shows message box about MicrOS.
     */
    void showAboutMicrosMessage();
    /*!
     * \brief Function that toggles console visibility.
     */
    void toggleConsoleVisibility();
    /*!
     * \brief Function that saves log to file.
     */
    void saveLogToFile();
};
#endif // MAINWIDGET_H
