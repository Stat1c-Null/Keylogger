Dim WshShell, currentDir
Set WshShell = CreateObject("WScript.Shell") 
currentDir = WshShell.CurrentDirectory
WshShell.Run currentDir & "\main.exe", 0
Set WshShell = Nothing