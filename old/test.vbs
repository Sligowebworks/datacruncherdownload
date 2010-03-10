

Dim FSO
Dim Shell

SET FSO = WSH.CreateObject("Scripting.FileSystemObject")

Set Shell = WSH.CreateObject("WScript.Shell")

Shell.Run ("net send wintermute test")
FSO.CreateTextFile("D:\WisconsinWebSite\online\data\DataDownload\test.vbs.textFile.txt")

Set FSO = NOTHING
Set Shell = Nothing
