 
<%
Dim oWSHShell
Dim intReturn

Set oWSHShell = Server.CreateObject("WScript.Shell")

'oWSHShell.Run "Rundll32.exe MSHTML.dll,PrintHTML " & filename, 1, true

'oWSHShell.Run  "mkdir d:\mzdTemp\dir", 1, false

'doesn't work.  only lists forst file when extracting
'intReturn = oWSHShell.Run  ("%comspec% /c COPY /B ""d:\WisconsinWebSite\DataDownload\FsZipX.exe"" /B + ""d:\WisconsinWebSite\DataDownload\Zips\0.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\1.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\2.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\3.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\4.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\5.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\6.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\7.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\8.datafile.zip"" /B" & _
'	" + ""d:\WisconsinWebSite\DataDownload\Zips\9.datafile.zip"" /B" & _
'	" ""d:\WisconsinWebSite\DataDownload\Downloads\My Exe.exe""", 0, True)

'Second attempt, one file at a time
'same result only last file is the only one listed (must be overwritting)
'intReturn = oWSHShell.Run  ("%comspec% /c COPY /B ""d:\WisconsinWebSite\DataDownload\FsZipX.exe"" /B +" & _
'	" ""d:\WisconsinWebSite\DataDownload\Zips\0.datafile.zip"" /B" & _
'	" ""d:\WisconsinWebSite\DataDownload\Downloads\My Exe.exe""", 0, True)
'
'intReturn = oWSHShell.Run  ("%comspec% /c COPY /B ""d:\WisconsinWebSite\DataDownload\FsZipX.exe"" /B +" & _
'	" ""d:\WisconsinWebSite\DataDownload\Zips\1.datafile.zip"" /B" & _
'	" ""d:\WisconsinWebSite\DataDownload\Downloads\My Exe.exe""", 0, True)

intReturn = oWSHShell.Run  ("%comspec% /c COPY /B ""d:\WisconsinWebSite\DataDownload\FsZipX.exe"" /B +" & _
	" ""d:\WisconsinWebSite\DataDownload\Data\1.datafile.zip"" /B" & _
	" ""d:\WisconsinWebSite\DataDownload\Zips\My Exe.exe""", 0, false)


set oWSHShell = Nothing
%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>



</body>
</html>
