OPTION EXPLICIT

Dim Shell
Dim strCommand
Dim FSO
Dim colArgs
Dim strPath

'Set colArgs = WScript.Arguments
'strPath = CInt(colArgs(0))
'set colArgs= nothing

Set Shell = WScript.CreateObject("WScript.Shell")

strCommand = "D:\WisconsinWebsite\online20060112\data\DataDownload\ZipScript.vbs " & "14" & _
		" " & "D:\WisconsinWebsite\online20060112\data\DataDownload"	_
		

Shell.Run strCommand, 0, false

'Set FSO = WScript.CreateObject("Scripting.FileSystemObject")

'FSO.CreateTextFile(strPath & "\" & "test.txt")	'"

'msgBox("hello")

Set Shell = Nothing