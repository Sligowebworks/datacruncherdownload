<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>
<%
Dim Item
For Each Item in Request.Form
	Response.Write Item & ": " & Item.Value & "<br>"
Next
%>


</body>
</html>
