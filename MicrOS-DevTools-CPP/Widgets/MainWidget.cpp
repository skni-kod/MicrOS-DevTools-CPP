#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("MicrOS DevTools CPP");

    // Menu bar
    menuBar = new QMenuBar();
    // Program menu
    programMenu = new QMenu(tr("&Program"));
    menuBar->addMenu(programMenu);
    exitAction = new QAction(tr("&Wyjście"));
    exitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    programMenu->addSeparator();
    programMenu->addAction(exitAction);
    // Tabs menu
    tabsMenu = new QMenu(tr("&Zakładki"));
    menuBar->addMenu(tabsMenu);
    startTabAction = new QAction(tr("&Start"));
    startTabAction->setShortcut(QKeySequence(tr("Ctrl+1")));
    liknsTabAction = new QAction(tr("&Przydatne linki"));
    liknsTabAction->setShortcut(QKeySequence(tr("Ctrl+2")));
    toolsTabAction = new QAction(tr("&Narzędzia"));
    toolsTabAction->setShortcut(QKeySequence(tr("Ctrl+3")));
    environmentTabAction = new QAction(tr("Ś&rodowisko"));
    environmentTabAction->setShortcut(QKeySequence(tr("Ctrl+4")));
    compilerTabAction = new QAction(tr("&Kompilator"));
    compilerTabAction->setShortcut(QKeySequence(tr("Ctrl+5")));
    buildingTabAction = new QAction(tr("Konfiguracja &budownia"));
    buildingTabAction->setShortcut(QKeySequence(tr("Ctrl+6")));
    tabsMenu->addAction(startTabAction);
    tabsMenu->addAction(liknsTabAction);
    tabsMenu->addAction(toolsTabAction);
    tabsMenu->addAction(environmentTabAction);
    tabsMenu->addAction(compilerTabAction);
    tabsMenu->addAction(buildingTabAction);
    // Console menu
    consoleMenu = new QMenu(tr("&Konsola"));
    menuBar->addMenu(consoleMenu);
    saveConsoleAction = new QAction(tr("&Zapisz zawartość konsoli"));
    showConsoleAction= new QAction(tr("&Pokaż konsole"));
    showConsoleAction->setCheckable(true);
    showConsoleAction->setChecked(true);
    cleanConsoleAction = new QAction(tr("&Wyczyść konsole"));
    consoleMenu->addAction(saveConsoleAction);
    consoleMenu->addAction(showConsoleAction);
    consoleMenu->addAction(cleanConsoleAction);
    // Help menu
    helpMenu = new QMenu(tr("P&omoc"));
    menuBar->addMenu(helpMenu);
    aboutCheckForUpdates = new QAction(tr("&Sprawdź aktualizacje"));
    aboutAction = new QAction(tr("&O programie"));
    aboutAction->setShortcut(QKeySequence(tr("Ctrl+A")));
    aboutMicrosAction = new QAction(tr("O &MicrOSie"));
    aboutQtAction = new QAction(tr("O &Qt"));
    helpMenu->addAction(aboutCheckForUpdates);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutMicrosAction);
    helpMenu->addAction(aboutQtAction);

    // Tab widget
    mainTabWidget = new QTabWidget();
    mainTabWidget->setMinimumWidth(600);
    mainTabWidget->setMinimumHeight(400);
    // Tabs
    linksTabWidget = new LinksTabWidget();
    startTabWidget = new StartTabWidget();
    toolsTabWidget = new ToolsTabWidget();
    environmentTabWidget = new EnvironmentTabWidget();
    compilerTabWidget = new CompilerTabWidget();
    buildingTabWidget = new BuildingTabWidget();

    mainTabWidget->addTab(startTabWidget, tr("Start"));
    mainTabWidget->addTab(linksTabWidget, tr("Przydatne linki"));
    mainTabWidget->addTab(toolsTabWidget, tr("Narzędzia"));
    mainTabWidget->addTab(environmentTabWidget, tr("Środowisko"));
    mainTabWidget->addTab(compilerTabWidget, tr("Kompilator"));
    mainTabWidget->addTab(buildingTabWidget, tr("Konfiguracja budownia"));

    // Logger
    logger = new Logger(true, this);

    // Console
    consoleGroupBox = new QGroupBox();
    consoleGroupBox->setTitle(tr("Konsola"));
    consoleWidget = new ConsoleWidget();
    connect(logger, &Logger::messageLogged, consoleWidget, &ConsoleWidget::printMessage);
    logger->logMessage(tr("MicrOS DevTools CPP 0.1"), Logger::LogLevel::Info);

    // Layouts
    mainLayout = new QVBoxLayout();
    consoleLayout = new QVBoxLayout();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(mainTabWidget);
    mainLayout->addWidget(consoleGroupBox);
    consoleLayout->addWidget(consoleWidget);

    this->setLayout(mainLayout);
    consoleGroupBox->setLayout(consoleLayout);

    // Database
    databaseManager = new DatabaseManager(logger, this);

    // Updater
    updater = new Updater(logger, this);

    // Connections
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(startTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(0);});
    connect(liknsTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(1);});
    connect(toolsTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(2);});
    connect(environmentTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(3);});
    connect(compilerTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(4);});
    connect(buildingTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(5);});
    connect(saveConsoleAction, &QAction::triggered, this, &MainWidget::saveLogToFile);
    connect(showConsoleAction, &QAction::triggered, this, &MainWidget::toggleConsoleVisibility);
    connect(cleanConsoleAction, &QAction::triggered, consoleWidget, &ConsoleWidget::clear);
    connect(aboutCheckForUpdates, &QAction::triggered, this, &MainWidget::checkForUpdates);
    connect(aboutAction, &QAction::triggered, this, &MainWidget::showAboutMessage);
    connect(aboutMicrosAction, &QAction::triggered, this, &MainWidget::showAboutMicrosMessage);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(updater, &Updater::updateAvailable, this, &MainWidget::checkUpdateResult);

#ifndef _DEBUG
    createAppDataFolder();
#endif
    databaseManager->init();
    checkForUpdates();
    logger->logMessage(tr("Uruchamianie zakończone"), Logger::LogLevel::Ok);
}

MainWidget::~MainWidget()
{

}

void MainWidget::showAboutMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("O programie"));
    msgBox.setText(tr("<h3>O programie</h3>"
                      "<p>Program stanowi narzędzie developerskie przydatne programistom MicrOSa.</p>"
                      "<p>Wersja: " APPLICATION_VERSION "</p>"
                      "<p>MicrOS to 32-bitowy system operacyjny, opracowany przez członków Sekcji Aplikacji Desktopowych Mobilnych i Webowych. "
                      "Naszym głównym celem było stworzenie od podstaw OS'a posiadającego możliwości podobne do systemu operacyjnego MS-DOS.</p>"
                      "<p>Repozytorium narzędzia MicrOS DevTools CPP (<a href=\"https://github.com/skni-kod/MicrOS-DevTools-CPP\">www.github.com</a>)"
                      "<p>W tworzeniu programu wykorzystano Qt 5.12 (<a href=\"https://www.qt.io/\">www.qt.io</a>)</p>"
                      "<p>Program objęty jest licencją GPL 3.0 (<a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">www.gnu.org/licenses/gpl-3.0.en.html</a>)</p>"
                      "<p>Logo MicrOSa jest własnością koła naukowego. <br\\>"
                      "Znajdują się na nim dodane ikony trybika oraz synchronizacji pochodzące z Google Material Desing Icons (<a href=\"https://github.com/google/material-design-icons\">GitHub</a>)</p>"));
    msgBox.setIconPixmap(QPixmap(":/pictures/DevToolsIcon").scaled(80, 80));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWidget::showAboutMicrosMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("O MicrOSie"));
    msgBox.setText(tr("<h3>O MicrOSie</h3>"
                      "<p>MicrOS to 32-bitowy system operacyjny, opracowany przez członków Sekcji Aplikacji Desktopowych Mobilnych i Webowych. "
                      "Naszym głównym celem było stworzenie od podstaw OS'a posiadającego możliwości podobne do systemu operacyjnego MS-DOS.</p>"
                      "<p>Repozytorium systemu MicrOS (<a href=\"https://github.com/skni-kod/MicrOS\">www.github.com</a>)"));
    msgBox.setIconPixmap(QPixmap(":/pictures/MicrosIcon").scaled(80, 80));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWidget::toggleConsoleVisibility()
{
    if(consoleGroupBox->isVisible())
    {
        consoleGroupBox->hide();
        showConsoleAction->setChecked(false);
    }
    else
    {
        consoleGroupBox->show();
        showConsoleAction->setChecked(true);
    }
}

void MainWidget::saveLogToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz plik"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                    tr("Log files (*.log);;Text files (*.txt)"));
    if(fileName.isNull())
    {
        return;
    }

    QSaveFile saveFile(fileName);
    saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&saveFile);

    logger->logMessage(tr("Zapis logu do pliku: ") + QDir::toNativeSeparators(fileName), Logger::LogLevel::Info);

    stream << consoleWidget->getLog();
    saveFile.commit();
}

void MainWidget::checkForUpdates()
{
    updater->checkForUpdates();
}

void MainWidget::checkUpdateResult(Updater::UpdateStatus status)
{
    switch(status)
    {
        case Updater::UpdateStatus::updateAvailable:
        {
            logger->logMessage(tr("Aktualizacja dostępna"), Logger::LogLevel::Info);
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Dostępne aktualizacje"));
            msgBox.setText(tr("<p>Zaktualizować MicrOS DevTools CPP?</p>"
                              "<p>Spowoduje to zamknięcie programu</p>"));
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int result = msgBox.exec();
            if(result == QMessageBox::Ok)
            {
                logger->logMessage(tr("Rozpoczęcie aktualizacji"), Logger::LogLevel::Info);
                updater->performUpdate();
                qApp->closeAllWindows();
            }
            break;
        }
        case Updater::UpdateStatus::updateNotAvailable:
        {
            logger->logMessage(tr("Brak dostępnych aktualizacji"), Logger::LogLevel::Info);
            break;
        }
        case Updater::UpdateStatus::error:
        {
            logger->logMessage(tr("Błąd podczas wyszukiwania aktualizacji"), Logger::LogLevel::Error);
            break;
        }
        case Updater::UpdateStatus::updateAlreadyInProgress:
        {
            logger->logMessage(tr("Aktualnie trwa już wyszukiwanie aktualizacji"), Logger::LogLevel::Info);
            break;
        }
    }
}

void MainWidget::createAppDataFolder()
{
    QDir databaseDir;
    if(!databaseDir.cd(QStandardPaths::writableLocation(QStandardPaths::DataLocation)))
    {
        if(databaseDir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)) == false)
        {
            logger->logMessage(tr("Nie można utworzyć folderu aplikacji w AppData\\Local"), Logger::LogLevel::Error);
        }
    }
}
