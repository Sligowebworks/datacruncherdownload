<% OPTION EXPLICIT
'Data Download Data Cruncher Zip Status Page
'
'Uses meta http-equivalent=refresh content=5
'to keep the user updated of the status of the zip process.
'
'When zip is complete, a link is displayed and the refresh is stopped.
'
'
'A query string variable is used to know which zip file status to check
' this script will look for a file named zipfilename.zip.tab that will holds a 
' boolean field for completion.
' 
'
Dim intID
Dim blnDone
Dim FSO

intID = CINT(Request.QueryString("id"))
'Response.Write "intID" & intID
blnDone = False

Set FSO = Server.CreateObject("Scripting.FileSystemObject")

If FSO.FileExists( FSO.BuildPath( Server.MapPath("/DownloadOptions/Zips") , intID & ".done" ) ) Then
	blnDone = True
End If
%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<SCRIPT>
/*function refreshPeriodic() {
   // Reload the page every 30 seconds
   location.reload();
   timerID = setTimeout("refreshPeriodic()",5000);
}
timerID = setTimeout("refreshPeriodic()",5000);
*/</SCRIPT>
<html>
<head>
	<title>Untitled</title>
	<% IF NOT blnDone Then %>
	<!-- <meta http-equiv="refresh" content="5; URL=http://homer:31000<%= Request.ServerVariables("URL") & "?" & Request.QueryString%>"> -->
	<meta http-equiv="refresh" content="5; URL=http://<%= Request.ServerVariables("HTTP_HOST") %><%= Request.ServerVariables("URL") & "?" & Request.QueryString%>">
	<% End IF %>
</head>

<body>
<%
If blnDone Then
	Response.Write "<b>Your Custom Data Download:<br>" & _
		"<a name=""downloadLink"" href=""/DownloadOptions/Zips/" & intID & ".SelfExtractingArchive.exe"">"  & _
		"download</a><br></b>"
Else
	Response.Write "<b>Please stand by.  Your custom download is being generated.</b><br>" & _
		"This page will refresh automatically every five seconds.  If your browser does not support meta-tags, please refresh manually to check your status." & _
		"<br> Last refresh:&nbsp;&nbsp;" & DateAdd("h", -1, Now)
End If
%>

</body>
</html>