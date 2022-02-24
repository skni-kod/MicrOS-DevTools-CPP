function Component()
{

}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        // Main icons
        component.addOperation("CreateShortcut", "@TargetDir@/Documentation/DokumentacjaMicrOSDevToolsCPP.pdf",
            "@StartMenuDir@/Dokumentacja/Dokumentacja MicrOS DevTools CPP.lnk");
    }
}

