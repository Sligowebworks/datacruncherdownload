<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>
<%
Response.Write Request.Form.count
Response.Write "a" & Request.Form("two")
Response.Write "b" & Request.QueryString("two")
%>


</body>
</html>
