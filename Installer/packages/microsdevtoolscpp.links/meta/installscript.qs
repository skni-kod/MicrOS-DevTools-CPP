function Controller()
{

}

function Component()
{

}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
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
