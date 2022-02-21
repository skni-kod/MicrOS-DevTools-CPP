function Component()
{
    if (!installer.isCommandLineInstance())
	{
		var widget = gui.pageById(QInstaller.StartMenuSelection);
		widget.left.connect(getStartMenuGroup);
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

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/MicrOS-DevTools-CPP.exe", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/MicrOS DevTools CPP.lnk");
		console.log("StartMenuGroup during creating shortcut: " + StartMenuGroup);
		component.addOperation("CreateShortcut", "@TargetDir@/Instalator.exe", "@AllUsersStartMenuProgramsPath@/" + StartMenuGroup + "/Instalator.lnk");
		console.log("StartMenuGroup during creating shortcut: " + StartMenuGroup);
    }
}

