<%

Dim Shell

Set Shell = Server.CreateObject("WScript.Shell")

'Dim FSO
'Set FSO = Server.CreateObject("Scripting.FileSystemObject")

'FSO.CreateTextFile("d:\WisconsinWebSite\online\data\DataDownload\fsotest.txt")

'Shell.Run "DIR >>D:\WisconsinWebSite\online\data\DataDownload\MZD.TEST.txt"

Shell.Run "wscript //T:10 d:\WisconsinWebSite\online\data\DataDownload\test.vbs", 0, False

'Shell.Run "net send WINTERMUTE asp-net-send"

'Call Shell.Run(" time /t >>D:\WisconsinWebSite\online\data\DataDownload\MZD.TEST.txt", 7, False)

'Call Shell.Run("", 7, False)

'Dim objExec

'Set objExec = Shell.exec( "wscript d:\WisconsinWebSite\online\data\DataDownload\test.vbs")


'Response.Write objExec.StdErr.ReadAll
RESPONSE.Write "DONE"

%>