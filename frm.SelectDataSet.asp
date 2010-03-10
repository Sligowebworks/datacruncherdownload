<!--#INCLUDE file="functions.inc" -->
<!--#include file="connopen.inc"-->
<!-- 
SUMMARY:
form for selecting dimension members for data cruncher download

DEPENDANCIES:
Function, GetDownloadDBConn() -- connopen.inc
	returns an ADODB.Connection string to the download files database
 -->
<%
Dim blnDebug
blnDebug = CBool(Request.QueryString("debug"))
Dim intFormElementID
intFormElementID = 0
%>
<%
Dim strFormHandlerPage
strFormHandlerPage = "int.SelectDataSet.asp"

Dim DBConn
DBConn = GetDownloadDBConn()	' returns a connection String (not using Set keyword to get an object)

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

		return Verified
	}
function CountChecks(e)
{	//alert("hi");
	if (!e)
	{	var e = window.event;
		target = e.srcElement;
	} else
	{target = e.target;	}

	var i;
	var numchecked;
	var element
	var max
	var form

	form = document.frmDownload;
	max = 15

	numchecked = 0;
	for (i = 0; i < form.elements.length; i++)
	{	element = form.elements[i]
		//if (element.type == "checkbox" && element.name == target.name && element.checked) numchecked++ ;
		if (element.type == "checkbox")
		{	if (element.name == "chkYears" || element.name == "chkQuests" || element.name == "chkCESAs")
			{	if (element.checked) numchecked++ ;
			}
		}
	}
	if (numchecked > max) 
	{	target.checked = false;
		alert("sorry, no more than " + max + " selections total.");
	}
		return true;	
}
function onloadH(e)		//The event handler for the onLoad event.
{	emod = (e) ? (e.eventPhase) ? "W3C" : "NN4" : (window.event) ? "IE4+"  : "unknown";
				
	if (emod == "NN4") document.captureEvents(Event.CLICK);

	switch (emod)
    {	case "W3C":
    		for (i=0; i < document.frmDownload.elements.length; i++)
            {	if (document.getElementById(i).type == "checkbox")
				{	document.getElementById(i).addEventListener("click",CountChecks,true); }
			}
		break;
		case "NN4":
        	document.captureEvents(Event.CLICK);
        	document.onclick = CountChecks;
		break;
		case "IE4+":
			//var i = 0;
            //while (document.forms[i].name != 'frmDownload'){i++}
             		
			for (n = 0; n < document.frmDownload.elements.length; n++)
			{	if (document.frmDownload.elements[n].type == "checkbox")
				{	document.frmDownload.elements[n].onclick = CountChecks ;
				}
			}
        break;
	}
    return true;
}

//define the event handler for the onload event
window.onload = onloadH;

//global vars
var emod; //the event model
</script>
<BODY alink="#0000FF" link="#0000FF" vlink="#0000FF" bgcolor="#FFFFFF">
<!--#INCLUDE VIRTUAL="/sig/ssi/js_css.inc"-->
<!--#INCLUDE VIRTUAL="/sig/ssi/js_hotcool.inc"-->
    <div align=center>
        <table cellpadding="0" cellspacing="0" border="0" width="600">
			<tr valign="bottom"><td><a href="http://www.dpi.state.wi.us/sig/index.html" ONMOUSEOVER="img_hot('mortar_big')" ONMOUSEOUT="img_cool('mortar_big')"><img src="/sig/images/wins_big.gif" width=84 height=40 hspace=0 vspace=0 border=0 alt="WINSS"><img src="/sig/images/mortar_big.gif" width=61 height=40 hspace=0 vspace=0 border=0 alt="" name="mortar_big"><img src="/sig/images/guide_big.gif" width=109 height=40 hspace=0 vspace=0 border=0 alt="Successful School Guide"></a><BR></td><td width=342 align=right><a href="/data/questions.aspx"><img src="/sig/images/data_big.gif" width=342 height=45 hspace=0 vspace=0 border=0 alt="Data Analysis"></a></td></tr>
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
									<em>Download all data on WINSS for any specific question.</em> <br>
									 <!-- Select year, location, and questions of interest.  Then click on SUBMIT.  View <a href="http://www.dpi.state.wi.us/sig/data/readme.html">README</a> files for file layouts and more information. -->
									 Select year, location, and questions of interest.  Then click on SUBMIT.  For more information, see <a href="http://www.dpi.state.wi.us/sig/data/readme.html" class=lightblue>Using WINSS Download Options</a>.

								<p>Each combination of year, location and question are included in a seperate file in comma delimited format (*.csv).  Data files are bundled in a single self-extracting zip-archive for download.  Files are updated periodically after new data are loaded on WINSS.  Not all data is available for all years.
								<!-- <p>More <a href="http://www.dpi.state.wi.us/sig/data/download.html">download options</a> are also available. -->
								
                            </td>
                        </tr>	
                	</table>
                    <!-- end of Side Bar -->
                </td>
				<td width="10"><img src="/sig/images/white.gif" width=10 height=231 border=0 alt=""></td>
				<td  width="390" class="text">
                    <!-- start of Body -->
					<table cellpadding="0" cellspacing="0" border="0" width="390">
					<tr valign="middle">
						<td bgcolor="#cccccc" valign="middle" height="35" colspan="2" class="title"> &nbsp;<font size="+1">Download Options</font></td>
					</tr>
					</table>
			<BR>
					<Form name="frmDownload" method="Post" action="<%= strFormHandlerPage %>">
					<%
					If blnDebug Then
						Response.Write("<input name=""frmDebug"" type=""hidden"" value=""" & blnDebug & """>")
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
							Response.Write "<nobr>"
							If InStr(RS("Disabled"), "DISABLED") > 0 Then
								Response.Write "<font color=""#777777"">"
							Else
								Response.Write "<font class=""text"">"
							End If
							Response.Write("<input id=""" & intFormElementID & """ name=""chkYears"" type=""checkbox"" value=""" & RS("ID") & """ " & RS("Disabled") & ">" & _
											RS("Label") & "&nbsp;&nbsp;&nbsp;&nbsp;")
							Response.Write "</font></nobr>"
							intFormElementID = intFormElementID + 1
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
							Response.Write "<nobr>"
							If InStr(RS("Disabled"), "DISABLED") > 0 Then
								Response.Write "<font color=""#777777"">"
							Else
								Response.Write "<font class=""text"">"
							End If
							Response.Write("<input id=""" & intFormElementID & """ name=""chkCESAs"" type=""checkbox"" value=""" & RS("ID") & """ " & RS("Disabled") & ">" & RS("Label") & "&nbsp;&nbsp;&nbsp;&nbsp;")
							Response.Write "</font></nobr>"
							RS.MoveNext
							intFormElementID = intFormElementID + 1
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
					RS.Source = "SELECT ID, Display, SectionName, SectionQuestion, CategoryName, [Disabled] FROM v_Questions ORDER BY [PrimarySort], [SecondarySort], [TertiarySort]"
					RS.Open
					If RS.RecordCount > 0 Then
						RS.MoveFirst
						Dim strSection		'RS("SectionName")
						Dim strCategory 		'RS("CategoryName")
						Dim intQuestionID	'
						'strSection = RS("SectionName")
						strSection = RS("SectionQuestion")
						strCategory = RS("CategoryName")
						Do Until RS.EOF  
							If NOT strSection = RS("SectionQuestion") Then
								strSection = RS("SectionQuestion")
								Response.Write ("<br><br><font size=""+1"" color=""#D82058"">" & strSection & "</font><br>" & vbNewLine)
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
							intQuestionID = RS("ID")
							If InStr(RS("Disabled"), "DISABLED") > 0 Then
								Response.Write "<font color=""#777777"">"
							Else
								Response.Write "<font class=""text"">"
							End If
							Response.Write("<input id=""" & intFormElementID & """ name=""chkQuests"" type=""checkbox"" value=""" & intQuestionID & """ " & RS("Disabled") & ">" & RS("Display") & "<br>" & vbNewLine)
							Response.Write("</font>")
							RS.MoveNext
							intFormElementID = intFormElementID + 1
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
				<td colspan="3"><!--#include virtual="/ssi/bot_nav.inc" --></td>
			</tr>
            </form>
        </table>
    </div>
</body>
</html>
<%
    'DBConn is a string becasue of the way GetDownloadDBConn() was called.
	'DBConn.Close
    'Set DBConn = nothing
%>

