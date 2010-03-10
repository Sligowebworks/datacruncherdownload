
<% 
Dim IP
Dim host
'IP

IP = Request.ServerVariables( "REMOTE_ADDR" )

'remote host name
host = Request.ServerVariables( "REMOTE_HOST" )

Response.Write IP & "<br>"
Response.Write host & "<br>"
 %>

 