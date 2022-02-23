function Controller()
{

}

function Component()
{
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    var page = gui.pageWidgetByObjectName("TargetDirectoryPage");
    if(page.StartMenuPathLineEdit.text.includes("Program Files"))
    {
        WarningLabel.setText("Instalacja w chronionej lokalizacji może spowodować problemy z aktualizacją");
    }
    else
    {
        WarningLabel.setText("");
    }
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        // Desktop
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOS-DevTools-CPP.exe", "@DesktopDir@/MicrOS DevTools CPP.lnk");

        // Main icons
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOS-DevTools-CPP.exe", "@StartMenuDir@/MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Instalator.exe", "@StartMenuDir@/Instalator.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/ReadMe.txt", "@StartMenuDir@/ReadMe.lnk");

        // Licenses
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-micros-devtools-cpp.txt",
            "@StartMenuDir@/Licencje/Licencja MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-openssl-ssleay.txt",
            "@StartMenuDir@/Licencje/Licencja OpenSSL.lnk");

        // Urls
        component.addOperation("Mkdir", "@StartMenuDir@/Linki");
        component.addOperation("Copy", "@TargetDir@/Links/ClubSite.url",
            "@StartMenuDir@/Linki/Strona koła.url");
        component.addOperation("Copy", "@TargetDir@/Links/DocumentationGitHub.url",
            "@StartMenuDir@/Linki/GitHub dokumentacji MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/MicrOSDocumentationGitHub.url",
            "@StartMenuDir@/Linki/GitHub dokumentacji MicrOSa.url");
        component.addOperation("Copy", "@TargetDir@/Links/MicrOSGitHub.url",
            "@StartMenuDir@/Linki/GitHub MicrOSa.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectDoxygen.url",
            "@StartMenuDir@/Linki/Doxygen projektu MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectGitHub.url",
            "@StartMenuDir@/Linki/GitHub MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectSite.url",
            "@StartMenuDir@/Linki/Strona projektu MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjektMicrOSSite.url",
            "@StartMenuDir@/Linki/Strona projektu MicrOS.url");
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
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/ReadMe.txt");
            }
        }
    } catch(e)
    {
        console.log(e);
    }
}