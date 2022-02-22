function Component()
{
    if (!installer.isCommandLineInstance())
    {
        var widget = gui.pageById(QInstaller.StartMenuSelection);
        widget.left.connect(getStartMenuGroup);
    }
    else
    {
        StartMenuGroup = "MicrOS DevTools CPP";
    }
    console.log("Constructor");
}

getStartMenuGroup = function()
{
    var widget = gui.pageById(QInstaller.StartMenuSelection);
    StartMenuGroup = widget.StartMenuPathLineEdit.text;
    console.log("StartMenuGroup: " + StartMenuGroup);
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        console.log("StartMenuGroup during creating shortcut: " + StartMenuGroup);

        // Desktop
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOS-DevTools-CPP.exe", "@DesktopDir@/" + "/MicrOS DevTools CPP.lnk");

        // Main icons
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOS-DevTools-CPP.exe", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Instalator.exe", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Instalator.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/ReadMe.txt", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/ReadMe.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Documentation/DokumentacjaMicrOSDevToolsCPP.pdf",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Dokumentacja.lnk");

        // Licenses
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-micros-devtools-cpp.txt",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Licencje/Licencja MicrOS DevTools CPP.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@/Licenses/licencja-openssl-ssleay.txt",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Licencje/Licencja OpenSSL.lnk");

        // Urls
        component.addOperation("Mkdir", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki");
        component.addOperation("Copy", "@TargetDir@/Links/ClubSite.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/Strona koła.url");
        component.addOperation("Copy", "@TargetDir@/Links/DocumentationGitHub.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/GitHub dokumentacji MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/MicrOSDocumentationGitHub.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/GitHub dokumentacji MicrOSa.url");
        component.addOperation("Copy", "@TargetDir@/Links/MicrOSGitHub.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/GitHub MicrOSa.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectDoxygen.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/Doxygen projektu MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectGitHub.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/GitHub MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjectSite.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/Strona projektu MicrOS DevTools CPP.url");
        component.addOperation("Copy", "@TargetDir@/Links/ProjektMicrOSSite.url",
            "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Linki/Strona projektu MicrOS.url");
    }
}

