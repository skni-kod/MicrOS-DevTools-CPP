#include "StartTabWidget.h"
#include <QDebug>
StartTabWidget::StartTabWidget(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel();
    mainLabel->setText(tr("<h3>MicrOS DevTools CPP</h3>"
                          "<p>Program stanowi narzędzie developerskie przydatne programistom MicrOSa.</p>"
                          "<p>Na kolejnych zakładkach znajdziesz:</p>"
                          "<p> - narzędzia potrzebne do rozpoczącia pracy</p>"
                          "<p> - konfigurację środowiska</p>"
                          "<p> - konfigurator skryptów służących uruchomieniu MicrOSa</p>"
                          "<p><b>Jeśli jesteś tu pierwszy raz zacznij od zakładki Narzędzia.</b></p>"
                          "<p>Przydatne linki:</p>"
                          "<p>Repozytorium systemu MicrOS (<a href=\"https://github.com/skni-kod/MicrOS\">www.github.com</a>)</p>"
                          "<p>Dokumentacja systemu MicrOS (<a href=\"https://github.com/skni-kod/MicrOSa-Dokumentacja\">www.github.com</a>)</p>"
                          "<p>Repozytorium narzędzia MicrOS DevTools (<a href=\"https://github.com/skni-kod/MicrOS-DevTools\">www.github.com</a>)</p>"
                          "<p>Repozytorium narzędzia MicrOS DevTools CPP (<a href=\"https://github.com/AzuxDario/MicrOS-DevTools-CPP\">www.github.com</a>)</p>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    /// Layouts
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainLabel);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

StartTabWidget::~StartTabWidget()
{
}
