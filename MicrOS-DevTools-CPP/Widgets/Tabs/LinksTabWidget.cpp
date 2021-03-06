#include "LinksTabWidget.h"

LinksTabWidget::LinksTabWidget(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel();
    mainLabel->setText(tr("<h3>Przydatne linki</h3>"
                          "<p>Repozytorium systemu MicrOS<br/>"
                          "(<a href=\"https://github.com/skni-kod/MicrOS\">www.github.com</a>)</p>"
                          "<p>Dokumentacja systemu MicrOS<br/>"
                          "(<a href=\"https://github.com/skni-kod/MicrOSa-Dokumentacja\">www.github.com</a>)</p>"
                          "<p>Repozytorium narzędzia MicrOS DevTools<br/>"
                          "(<a href=\"https://github.com/skni-kod/MicrOS-DevTools\">www.github.com</a>)</p>"
                          "<p>Repozytorium narzędzia MicrOS DevTools CPP<br/>"
                          "(<a href=\"https://github.com/AzuxDario/MicrOS-DevTools-CPP\">www.github.com</a>)</p>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    nextTabLabel = new QLabel();
    nextTabLabel->setText(tr("<p><b>Po zapoznaniu się z tymi linkami możesz przejść do zakładki Narzędzia.</b></p>"));
    nextTabLabel->setOpenExternalLinks(true);
    nextTabLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    nextTabLabel->setWordWrap(true);

    /// Layouts
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(nextTabLabel);
    this->setLayout(mainLayout);
}

LinksTabWidget::~LinksTabWidget()
{
}
