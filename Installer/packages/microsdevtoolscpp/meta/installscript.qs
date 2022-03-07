function Controller()
{

}

function Component()
{
    // For checkbox to show "Open ReadMe"
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);

    // For changing information on target directory page
    if (!installer.isCommandLineInstance())
    {
        page = gui.pageWidgetByObjectName("TargetDirectoryPage");
        if(page !== null)
        {
            page.entered.connect(changeTargetDirectoryLabels);
        }
    }
}

changeTargetDirectoryLabels = function()
{
    page = gui.pageWidgetByObjectName("TargetDirectoryPage");
    page.MessageLabel.setText("Podaj katalog, w którym ma zostać zainstalowany element MicrOS DevTools CPP."+
    "\n" + "Jeśli instalujesz ten program z konta zwykłego użytkownika nie rób tego w folderze chronionym np. Program Files." +
    "\n" + "Spowoduje to problem z dostępem do folderu, gdzie instalator spróbuje przechować tymczasowe pliki instalacyjne. Szczegółowe informacje w dokumentacji.");
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        // Desktop
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOSDevToolsCPP/MicrOSDevToolsCPP.exe", "@DesktopDir@/MicrOS DevTools CPP.lnk");

        // Main icons
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOSDevToolsCPP/MicrOSDevToolsCPP.exe", "@StartMenuDir@/MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Instalator.exe", "@StartMenuDir@/Instalator.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOSDevToolsCPP/ReadMe.txt", "@StartMenuDir@/ReadMe.lnk");

        // Licenses
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-micros-devtools-cpp.txt",
            "@StartMenuDir@/Licencje/Licencja MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-openssl-ssleay.txt",
            "@StartMenuDir@/Licencje/Licencja OpenSSL.lnk");
    }
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try
    {
        if (installer.isInstaller() && installer.status == QInstaller.Success)
        {
            installer.addWizardPageItem( component, "FinishCheckBoxForm", QInstaller.InstallationFinished );
        }
    } catch(e)
    {
        console.log(e);
    }
}

Component.prototype.installationFinished = function()
{
    try
    {
        if (installer.isInstaller() && installer.status == QInstaller.Success)
        {
            var checkboxForm = component.userInterface( "FinishCheckBoxForm" );
            if (checkboxForm && checkboxForm.readMeCheckBox.checked)
            {
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/MicrOSDevToolsCPP/ReadMe.txt");
            }
        }
    } catch(e)
    {
        console.log(e);
    }
}