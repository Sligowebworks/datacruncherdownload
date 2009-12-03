<!--#INCLUDE file="functions.inc" -->
<!--#include file="connopen.inc"-->
<%
Dim blnDebug
blnDebug = CBool(Request.QueryString("debug"))
%>
<%
Dim strFormHandlerPage
strFormHandlerPage = "mzd.int.DataDownload.asp"

Dim DBConn
DBConn = GetDownloadDBConn()

Dim RS
Set RS = Server.CreateObject("ADODB.Recordset")

RS.CursorType = 3
RS.LockType = 1
RS.ActiveConnection = DBConn

%>
<!doctype html public "-//W3C//DTD HTML 3.2 Final//EN">
<html>
<head>
	<title>Data Analysis</title> 
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
</head>
<script language="JavaScript" src="/sig/js/cookies.js">
</script>
    <!--#INCLUDE VIRTUAL="/sig/ssi/js_css.inc"-->
    <!--#INCLUDE VIRTUAL="/sig/ssi/js_hotcool.inc"-->
<script language="javascript">
function popup(file,window) 
{
	var winFeatures = 'width=650,height=595,scrollbars=yes,resizable=yes,menubar=yes';
	var pg = file;
	win = open(pg,window,winFeatures);
	if (window.focus) win.focus();
}
</script>
<script language="javascript">
function VerifiedSubmit(form)
	{	var ok
		ok = frmDownloadValidate(form)
		if (ok)
		{	form.submit();
		}
	}
function frmDownloadValidate(form)
	{
		var i;
		var Qnumchecked;	/*Questions*/
		var Ynumchecked;	/*Year*/
		var Cnumchecked;	/*CESA*/
		var element
		var Verified
		Verified = true
		Qnumchecked = 0;
		Ynumchecked = 0;
		Cnumchecked = 0;
		for (i = 0; i < form.elements.length; i++)
		{	element = form.elements[i]
			if (element.type == 'checkbox' && element.checked)
			{	if (element.name == 'chkQuests'){Qnumchecked++}
				if (element.name == 'chkYears'){Ynumchecked++}
				if (element.name == 'chkCESAs'){Cnumchecked++}
			}
		}
		if (Ynumchecked == 0){alert('You must select at least one Year.'); Verified = false;}
		if (Cnumchecked == 0){alert('You must select at least one CESA.'); Verified = false;}
		if (Qnumchecked == 0){alert('You must select at least one question.'); Verified = false;}

		if (Verified)
		{	return true;}
		else
		{	return false;}
	}
</script>
<BODY alink="#0000FF" link="#0000FF" vlink="#0000FF" bgcolor="#FFFFFF">
    <div align=center>
        <table cellpadding="0" cellspacing="0" border="0" width="600">
			<tr valign="bottom"><td><a href="http://www.dpi.state.wi.us/sig/index.html" ONMOUSEOVER="img_hot('mortar_big')" ONMOUSEOUT="img_cool('mortar_big')"><img src="/sig/images/wins_big.gif" width=84 height=40 hspace=0 vspace=0 border=0 alt="WINSS"><img src="/sig/images/mortar_big.gif" width=61 height=40 hspace=0 vspace=0 border=0 alt="" name="mortar_big"><img src="/sig/images/guide_big.gif" width=109 height=40 hspace=0 vspace=0 border=0 alt="Successful School Guide"></a><BR></td><td width=342 align=right><a href="/data/questions.asp"><img src="/sig/images/data_big.gif" width=342 height=45 hspace=0 vspace=0 border=0 alt="Data Analysis"></a></td></tr>
			<tr><td valign=top colspan=2><img src="/sig/images/assess_runner.gif" width=600 height=5 hspace=0 vspace=0 border=0 alt=""></TD></TR>
			<tr><td valign=top colspan=2><img src="/sig/images/white.gif" width=1 height=10 border=0 alt=""></td></tr>
		</table>
        <table cellpadding="0" cellspacing="0" border="0" width="600">
            <tr valign="TOP">
                <td bgcolor="#D82058" rowspan="1" width="200">
                    <!-- start of Side Bar -->
                	<table width="200" border="0" cellspacing="0" cellpadding="5" valign="TOP">
                	    <tr valign="TOP">
                            <td class="datatext">
								<p>
									<em>Download all Data on WINSS for any specific question.</em> <br>
									 Select year, locale, and questions of interest.  Then click on DOWNLOAD NOW.  Each year, location and question are included in a seperate file.  View README files for file layouts and more information (link? quote,"this should go to a page on DPI server). </p><p>Data are zipped and in comma delimited format (*.csv).  Files are updated when new data are loaded and are periodically updated.  Not all data may be available for all years.
								</p>
                            </td>
                        </tr>	
                	</table>
                    <!-- end of Side Bar -->
                </td>
				<td width="10"><img src="/sig/images/white.gif" width=10 height=231 border=0 alt=""></td>
				<td  width="390">
                    <!-- start of Body -->
					<Form name="frmDownload" method="Post" action="<%= strFormHandlerPage %>">
					<%
					If blnDebug Then
						Response.Write("<input name=""debug"" type=""hidden"" value=""" & blnDebug & """>")
					End If
					%>
					<%
					If NOT RS.State = 0 Then
						RS.Close
					End IF
					RS.Source = "SELECT ID, [Year], Label, [Disabled] FROM glsYears ORDER BY [ID]"
					RS.Open
					If RS.RecordCount > 0 Then
						RS.MoveFirst
						Do Until RS.EOF
							Response.Write("<input name=""chkYears"" type=""checkbox"" value=""" & RS("Year") & """ " & RS("Disabled") & ">" & RS("Label") )
							RS.MoveNext
						Loop
					End If
					RS.Close
					%>
					<br><br>
					<HR>
					<%
					If NOT RS.State = 0 Then
						RS.Close
					End IF
					RS.Source = "SELECT ID, CESA, Label, [Disabled] FROM glsCESAs ORDER BY [ID]"
					RS.Open
					If RS.RecordCount > 0 Then
						RS.MoveFirst
						Do Until RS.EOF
							Response.Write("<input name=""chkCESAs"" type=""checkbox"" value=""" & RS("CESA") & """ " & RS("Disabled") & ">" & RS("Label") )
							RS.MoveNext
						Loop
					End If
					RS.Close
					%>
					<br><br>
					<HR>
					<%
					If NOT RS.State = 0 Then
						RS.Close
					End IF
					RS.Source = "SELECT ID, Abbrev, Question, SectionName, CategoryName, [Disabled] FROM v_Questions ORDER BY [PrimarySort], [SecondarySort], [TertiarySort]"
					RS.Open
					If RS.RecordCount > 0 Then
						RS.MoveFirst
						Dim strSection		'RS("SectionName")
						Dim strCategory 		'RS("CategoryName")
						strSection = RS("SectionName")
						strCategory = RS("CategoryName")
						Do Until RS.EOF
							If NOT strSection = RS("SectionName") Then
								strSection = RS("SectionName")
								If Trim(strSection) = "" Then
									Response.Write( "<br>" & vbNewLine )
								Else
									Response.Write ("<br><br><b><font size=""+1"">" & strSection & "</font></b><br>" & vbNewLine)
								End If
							End If
							'Call PrintVar("strCategory")
							'Response.Write(RS("CategoryName"))
							If NOT strCategory = RS("CategoryName") Then
								strCategory = RS("CategoryName")
								If Trim(strCategory) = "" Then
									Response.Write( "<br>" & vbNewLine )
								Else
									Response.Write( "<br><b>" & strCategory & "</b><br>" & vbNewLine )
								End If
							End If
							
							Response.Write("<input name=""chkQuests"" type=""checkbox"" value=""" & RS("Abbrev") & """ " & RS("Disabled") & ">" & RS("Question") & "<br>" & vbNewLine)
							
							RS.MoveNext
						Loop
					End If
					RS.Close
					%>
					<br><br>
					<input type="button" value="Submit" onClick="VerifiedSubmit(frmDownload)">
					</Form>
                    <!-- end of Body -->
                </td>
            </tr>
            <FORM NAME="Form1" METHOD="post" ACTION="">
			<tr bgcolor="#D82058">
				<td colspan="3"><!--#include virtual="/data/ssi/bot_nav.inc" --></td>
			</tr>
            </form>
        </table>
    </div>
</body>
</html>
<%
    Conn.close
    Set conn = nothing
%>

