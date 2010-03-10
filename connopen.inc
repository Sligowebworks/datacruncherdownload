<%
	Function GetDownloadDBConn()
		Dim Conn
		Set Conn = Server.CreateObject("ADODB.Connection")
		Conn.ConnectionTimeout = 300
		Conn.CommandTimeout = 300
		Conn.Open "Provider=sqloledb;Data Source=(local);Initial Catalog=WIDownloadFiles;User Id=netwisco;Password=wkce99;"
		set GetDownloadDBConn = Conn
	End Function
	Function GetXPCmdConn()
		Dim Conn
		Set Conn = Server.CreateObject("ADODB.Connection")
		Conn.ConnectionTimeout = 300
		Conn.CommandTimeout = 300
		Conn.Open "Provider=sqloledb;Data Source=(local);Initial Catalog=Master;User Id=netwisco;Password=wkce99;"
		set GetXPCmdConn = Conn
	End Function
%>

