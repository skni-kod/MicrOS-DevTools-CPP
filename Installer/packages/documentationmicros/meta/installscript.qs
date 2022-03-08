function Component()
{

}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        // Main icons
        component.addOperation("CreateShortcut", "@TargetDir@/Documentation/DokumentacjaMicrOSa.pdf",
            "@StartMenuDir@/Dokumentacja/Dokumentacja MicrOSa.lnk");
    }
}

