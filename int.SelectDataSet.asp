<!--#INCLUDE file="functions.inc" -->
<!--#INCLUDE file="connopen.inc" -->
<!--#INCLUDE file="adovbs.inc" -->
<% 
' "Data Cruncher" Download Feature
' Dataset Selection Form handler
'
' First entry: validate selection and display result to user
'
' Second Entry (post-back)(user confirmed): Processes form input and log request to db
'
' logging in db returns a unique ID to be used throughout process
' SQL stored procedure is used to obtain a file list based on form selections
' file list is written to a file identified with ID
' zip script is kicked off with id as argument


Dim strRequest	'raw form values for purpose of logging
Dim strAddress	' user IP
Dim strYears	'form values
Dim strCESAs	'form values
Dim strQuestions	'form values

Dim adoConn
Dim adoCommand
Dim adoRS

Dim FSO		'FileSystemObject
Dim tsFileList	'text stream object
Dim Shell	'command shell object

'configuration settings:
Dim strWorkingFilePath	' working directory: temp files and download files
Dim strDataFilePath	'raw csv's
Dim strRoot	'components directory (where this file is)

Dim i
Dim blnDebug
Dim blnIsPostBack	'user confirmed submit
Dim intZipID	'request ID assigned upon commit

'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~
'*** Initialize
'Config variables:
strRoot = "/DownloadOptions"
strWorkingFilePath = strRoot & "/Zips"
strDataFilePath = strRoot & "/Data"
strExePath = "D:\Program Files"

If Not IsEmpty(Request.Form("frmIsPostBack")) Then
	blnIsPostBack = Request.Form("frmIsPostBack")
Else
	blnIsPostBack = False
End If

If NOT IsEmpty(Request.QueryString("debug")) Then
	blnDebug = CBool(Request.QueryString("debug"))
ElseIf NOT IsEmpty(Request.Form("frmDebug")) AND CBool(Request.Form("frmDebug")) = True Then
	'debug was passed in form instead of querystring
	blnDebug = True
	Response.Write "<br>DEBUG ON<br>"
Else
	blnDebug = False
End IF

Set adoConn = GetDownloadDBConn()	'from connopen.inc
Set adoCommand = Server.CreateObject("ADODB.Command")
Set adoRS = Server.CreateObject("ADODB.Recordset")
adoRS.CursorType = 3
adoRS.LockType = 1
Set FSO = Server.CreateObject("Scripting.FileSystemObject")
If blnIsPostBack Then
	Set Shell = Server.CreateObject("WScript.Shell")
End If

adoCommand.ActiveConnection = adoConn
adoCommand.CommandType = adCmdStoredProc

'get Form submit values
strRequest = Request.Form()	'entire request string as name value pairs 
strAddress = Request.ServerVariables("REMOTE_ADDR")	'IP address
strYears = Request.Form("chkYears")
strCESAs = Request.Form("chkCESAs")
strQuestions = Request.Form("chkQuests")
If blnDebug Then
	Call PrintVar("strYears")
	Call PrintVar("strCESAs")
	Call PrintVar("strQuestions")
End If

'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~
'------------------------- DEBUG ----------------------
If blnDebug Then
'If True Then
	Dim Item
	Dim Item2
	Call PrintVar("Request.Form")
	Call PrintVar("Request.Form.Count")
	For Each Item in Request.form
		PrintVar("Request.Form(""""" & Item & """"")")
		If Request.form(Item).count > 1 Then
			For i = 1 to Request.form(Item).count
				Call PrintVar("Request.Form(""""" & Item & """"")(" & i & ")")
			Next
		End IF
	Next
End If
'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~
'*** Subs:
Sub GetFileList(adoRS)
	'relies on adoCommand to be in scope
	'get FileList
	adoCommand.CommandText = "spGetDownloadFileNames"
	adoCommand.Parameters.Append adoCommand.CreateParameter("strCSVYearIDs",adVarWChar,adParamInput,200, strYears)
	adoCommand.Parameters.Append adoCommand.CreateParameter("strCSVCESAIDs",adVarWChar,adParamInput,200, strCESAs)
	adoCommand.Parameters.Append adoCommand.CreateParameter("strCSVQuestIDs",adVarWChar,adParamInput,200, strQuestions)
	
	Set adoRS = adoCommand.Execute()
	
	'clean
	adoCommand.Parameters.Delete "strCSVYearIDs"
	adoCommand.Parameters.Delete "strCSVCESAIDs"
	adoCommand.Parameters.Delete "strCSVQuestIDs"
End Sub

'~,~'~,~'~,~'~,~'~,~'~,~' POST-BACK ~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~'~,~
If blnIsPostBack Then
	'log the request
	adoCommand.Parameters.Append adoCommand.CreateParameter("Address",adVarWChar,adParamInput,15, strAddress)
	adoCommand.Parameters.Append adoCommand.CreateParameter("Request",adVarWChar,adParamInput,500, strRequest)
	adoCommand.Parameters.Append adoCommand.CreateParameter("ID",adInteger,adParamOutput)

	adoCommand.CommandText = "spNewZipFile"
	adoCommand.Execute()
	'retreive the ID
	intZipID = CInt(adoCommand.Parameters("ID").Value)
	If blnDebug Then
		Call Printvar("intZipID")
	End If

	'clean
	adoCommand.Parameters.Delete "ID"
	adoCommand.Parameters.Delete "Request"
	adoCommand.Parameters.Delete "Address"

	'load the RS
	Call GetFileList(adoRS)

	If NOT adoRS.EOF Then
		If blnDebug Then
			response.Write "create Text File:" & FSO.BuildPath( Server.MapPath(strWorkingFilePath) , intZipID & ".FileList.txt")
		End If
		
		Set tsFileList = FSO.CreateTextFile(FSO.BuildPath( Server.MapPath(strWorkingFilePath) , intZipID & ".FileList.txt") )
		
		Do Until adoRS.EOF
			If blnDebug Then
				response.write "<br> " & adoRS.Fields(0).Value & "<br>"
			End If
			If FSO.FileExists( FSO.BuildPath( Server.MapPath(strDataFilePath) , adoRS.Fields(0).Value ) ) Then	'"
				'valid files only
				tsFileList.WriteLine( FSO.BuildPath( Server.MapPath(strDataFilePath) , adoRS.Fields(0).Value ))
			End If
			adoRS.MoveNext
		Loop
		tsFileList.Close
		Set tsFileList = Nothing
	End IF

	'kick off the zip script
	'Call  Shell.Run( """" & FSO.BuildPath(strExePath , "wscript.exe") & """ """ & _
	'		FSO.BuildPath( Server.MapPath(strRoot) , "ZipScript.vbs") & """ " & CStr(intZipID) & _
	'		" """ & Server.MapPath(strRoot)	& """"_
	'		, 7, False)	'minimized window, no focus, no wait on return
	
	adoCommand.ActiveConnection = GetXPCmdConn()
	strShellCmd =  "'wscript.exe " & _
			FSO.BuildPath( Server.MapPath(strRoot) , "ZipScript.vbs") & " " & CStr(intZipID) & _
			" " & Server.MapPath(strRoot)	& "'"
	adoCommand.CommandType = adCmdText ' for unknown reason, doesn't work as stored proc type
	adoCommand.CommandText = "xp_cmdshell " & strShellCmd & ", NO_OUTPUT"
	
	'adoCommand.Parameters.Append adoCommand.CreateParameter("ExecStmt",adVarWChar,adParamInput,500, strShellCmd)
	
	Response.Write adoCommand.CommandText '& strShellCmd
	Set adoRS = adoCommand.Execute()
	
	'clean
	'adoCommand.Parameters.Delete "ExecStmt"

	'Call  Shell.Exec( """" & FSO.BuildPath(strExePath , "wscript.exe") & """ """ & _
	'		FSO.BuildPath( Server.MapPath(strRoot) , "ZipScript.vbs") & """ " & CStr(intZipID) & _
	'		" """ & Server.MapPath(strRoot)	& """")
			
	'Script.Wait(100)
	
	'redirect to status page
	If NOT blnDebug Then 
		Response.Redirect("status.asp?id=" & intZipID )
	Else
		Response.Write "Response.Redirect(status.asp?id=" & intZipID & ")"
	End If
End If

'~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~
'*** VALIDATE REQUEST

If NOT blnIsPostBack Then
	Dim Output
	Dim strFontColor
	Dim blnAvailable
	'load RS
	Call GetFileList(adoRS)
	i = 0
	Output = "<Table cols=""4"" border=""1"" cellpadding=""6"" cellspacing=""2"">" & vbNewLine & _
		"<TR><TD><strong>Year</strong></TD><TD><strong>Location</strong></TD><TD><strong>Question</strong></TD><TD><strong>Availability</strong></TD></TR>" & vbNewLine 
	'Response.Write adoRS.State
	If NOT adoRS.EOF Then
		Do Until adoRS.EOF
			If blnDebug Then
				Output = Output & "<br>" & adoRS.Fields(0).Value & "<br>"
			End If
			Output = Output & "<TR>"
			If FSO.FileExists( FSO.BuildPath( Server.MapPath(strDataFilePath) , adoRS.Fields(0).Value ) ) Then
				strFontColor = "green"
				blnAvailable = True
				i = i + 1
			Else
				strFontColor = "red"
				blnAvailable = False
			End If
			Output = Output & _
			vbTab & "<TD><font color=""" & strFontColor & """>" & vbNewLine & _
			vbTab & vbTab & "<nobr>" & adoRS("YearLabel") & "</nobr>" & vbNewLine & _
			vbTab & "</font></TD>" & vbNewLine & _
			vbTab & "<TD><font color=""" & strFontColor & """>" & vbNewLine & _
			vbTab & vbTab & "CESA " & adoRS("CESA") & vbNewLine & _
			vbTab & "</font></TD>" & vbNewLine & _
			vbTab & "<TD><font color=""" & strFontColor & """>" & vbNewLine & _
			vbTab & vbTab & adoRS("Question") & vbNewLine & _
			vbTab & vbTab & "&nbsp;&nbsp;" & adoRS("QuestSubDivLabel") & vbNewLine & _
			vbTab & "</font></TD>" & vbNewLine 
			If blnAvailable Then
				Output = Output & _
				vbTab & "<TD><font color=""" & strFontColor & """>" & vbNewLine & _
				vbTab & vbTab & "Yes" & vbNewLine & _
				vbTab & "</font></TD>" & vbNewLine
			Else
				Output = Output & _
				vbTab & "<TD><font color=""" & strFontColor & """>" & vbNewLine & _
				vbTab & vbTab & "No" & vbNewLine & _
				vbTab & "</font></TD>" & vbNewLine
			End If
			 Output = Output & "</TR>"
			adoRS.MoveNext
		Loop
		Output = Output & "</Table>" & vbNewLine
		Output = Output & "<input type=""hidden"" name=""frmintValidDatasets"" value=""" & i & """>" & vbNewLine
	Else
		'Sorry, no results returned
		'(impossible)
	End If
	
%>	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

	<html>
	<head>
		<title>Verify Download Selection</title>
	</head>

	<body>

	<H2>Confirm Your Selection</H2>
	<div align="Left">
		<!-- If some of your data sets are marked unavailable, it is most likely due to years selections that are not available for that data.  Go back to change your selection or proceed to download the datasets displayed in green. -->
	</div>
	<p>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Data sets are labeled available (green) or unavailable (red) for the selected years.  Click on the "Back" button to change your selection.  Click on "Download Now" to download the available data sets.
		For more information, view <a href="http://www.dpi.state.wi.us/sig/data/readme.html">Read Me files</a>.
	</p>
	<Form name="form" method="post" action="<%= Request.ServerVariables("URL")%>">
		<input type="hidden" name="frmIsPostBack" value="<%= CBool(NOT blnIsPostBack)%>">
		<input type="hidden" name="frmDebug" value="<%= blnDebug%>">
	<%
	For each Item in Request.Form
		If InStr(Item, "frm") = 0 Then
			%>
			<input name="<%= Item %>" type="hidden" value="<%= Request.Form(Item) %>">
			<%
		End If
	Next	%>
	<input type="button" onClick="history.go(-1)" value="Back"><%
	If i > 0 Then
		%>&nbsp;&nbsp;<input type="Submit" value="Download Now"><%
	End If
	%><br><br>
	<%=Output%><br>
	<input type="button" onClick="history.go(-1)" value="Back">
	<%
	If i > 0 Then
		%>&nbsp;&nbsp;<input type="Submit" value="Download Now"><%
	End If
	%>
	</Form>
	</body>
	</html>
	<%
End If

'~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~
'*** House keeping
Set Shell = Nothing
Set adoCommand = Nothing
If not adoRS.State = 0 Then
	adoRS.Close
End If
Set adoRS = Nothing
If NOT adoConn.State = 0 Then
	adoConn.Close
End If
Set adoConn = Nothing
%>
