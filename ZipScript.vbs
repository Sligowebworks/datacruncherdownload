OPTION EXPLICIT
' ZIP SCRIPT

'called with the Run method from intSelectDataSet.asp

'Arguments: 
	'ID -- the id of the job being completed
		'used to identify the appropriate file list.
		'Stamped at begining of all files generated in this script.
	'Dir -- the base directory for all operations (where this file is) not where zips are made

'DEPENDS:
'-- winzip self extractor installed to default location
'-- winzip command line support
' -- licensed versions to allow batch file exec without license warning message
'-- sub dir of arg Dir named 'Zips'


Dim colArgs
Dim intID
Dim strWorkingDir
Dim FSO
Dim strZipDir
Dim strExePath
Dim strCommand
Dim Shell
Dim f	'throw-away file reference

'CONFIGURE: set path to exe's, no trailing slash
strExePath = "D:\wwwroot"

'Instance FileSystemObject
Set FSO = WSH.CreateObject("Scripting.FileSystemObject")

'get id from args
Set colArgs = WSH.Arguments
intID = CInt(colArgs(0))
strWorkingDir = CStr(colArgs(1))
strZipDir = FSO.BuildPath(strWorkingDir, "Zips")
Set colArgs = Nothing

Set Shell = WSH.CreateObject("WScript.Shell")

'Build Zip Command
'wzzip [options] zipfile [@listfile]
strCommand = """" & FSO.BuildPath(strExePath, "WinZip\WZZIP.EXE") & """ """ & FSO.BuildPath(strZipDir, intID & ".SelfExtractingArchive.zip") & """ " & _
			"@""" & FSO.BuildPath(strZipDir, intID & ".FileList.txt""")
'DEBUG CODE
'Set f = FSO.CreateTextFile(FSO.BuildPath(strZipDir, intID & ".LKHSELIRUGFLKJASBD"))
'/DEBUG CODE
			
'msgbox strcommand
Call Shell.Run( strCommand, 7, true)	'minimized window, wait on return

'Build create-self-extractor command
StrCommand = """" & FSO.BuildPath(strExePath, "WinZip Self-Extractor\WZIPSE32.EXE") & """ """ & _
			FSO.BuildPath(strZipDir, intID & ".SelfExtractingArchive.zip""") & " -y"

'msgbox strcommand
Call Shell.Run( strCommand, 7, True)	'minimized window, wait on return

'Flag as job done
Set f = FSO.CreateTextFile(FSO.BuildPath(strZipDir, intID & ".Done"))

'clean
Set f = Nothing
Set Shell = Nothing
Set FSO = Nothing
