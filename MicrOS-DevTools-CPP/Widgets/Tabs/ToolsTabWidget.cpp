#include "ToolsTabWidget.h"

ToolsTabWidget::ToolsTabWidget(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel();
    mainLabel->setText(tr("<h3>Procedura tworzenia nowego środowiska</h3>"
                          "<p>Należy zainstalować poniższe programy, gdyż aktualne skrypty są pod nie przygotowane.</p>"
                          "<p> - Visual Studio Code (wymagany jest także dodatek od obsługi C/C++ od Microsoftu)<br/>"
                          "(<a href=\"https://code.visualstudio.com/\">https://code.visualstudio.com/</a>)</p>"
                          "<p> - QEMU (emulator procesora)<br/>"
                          "(<a href=\"https://www.qemu.org/\">https://www.qemu.org/</a>)</p>"
                          "<p> - Imdisk (montowanie dyskietki)<br/>"
                          "(<a href=\"https://sourceforge.net/projects/imdisk-toolkit/files/20190130/ImDiskTk-x64.exe/download\">https://sourceforge.net</a>)</p>"
                          "<p> - MSYS2 (środowisko Linuxowe)<br/>"
                          "(<a href=\"https://www.msys2.org/\">https://www.msys2.org</a>)</p>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    nextTabLabel = new QLabel();
    nextTabLabel->setText(tr("<p><b>Gdy skończysz przejdź do zakładki Środowisko.</b></p>"));
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

ToolsTabWidget::~ToolsTabWidget()
{
}
