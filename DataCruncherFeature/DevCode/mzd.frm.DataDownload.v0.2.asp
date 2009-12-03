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
'detritus:
'RS.source = "SELECT * FROM glsQuestions;"
'RS.Open
'Call PrintVar("RS.RecordCount")
%>
<!doctype html public "-//W3C//DTD HTML 3.2 Final//EN">
<html>
<head>
	<title>Data Analysis</title> 
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
</head>
<script language="JavaScript" src="/sig/js/cookies.js">
</script>
	<!-- include file="functions.inc"-->
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
					<!-- <input name="chkYears" type="checkbox" value="all">ALL 
					<input name="chkYears" type="checkbox" value="2003">2002-03
					<input name="chkYears" type="checkbox" value="2002">2001-02
					<input name="chkYears" type="checkbox" value="2001">2000-01
					<input name="chkYears" type="checkbox" value="2000">1999-00
					<input name="chkYears" type="checkbox" value="1999">1998-99
					<input name="chkYears" type="checkbox" value="1998">1997-98
					<input name="chkYears" type="checkbox" value="1997">1996-97 -->
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
					<!-- <input name="chkCESAs" type="checkbox" value="all">All CESA
					<input name="chkCESAs" type="checkbox" value="1">1
					<input name="chkCESAs" type="checkbox" value="2">2
					<input name="chkCESAs" type="checkbox" value="3">3
					<input name="chkCESAs" type="checkbox" value="4">4
					<input name="chkCESAs" type="checkbox" value="5">5
					<input name="chkCESAs" type="checkbox" value="6">6
					<input name="chkCESAs" type="checkbox" value="7">7
					<input name="chkCESAs" type="checkbox" value="8">8
					<input name="chkCESAs" type="checkbox" value="9">9
					<input name="chkCESAs" type="checkbox" value="10">10
					<input name="chkCESAs" type="checkbox" value="11">11 -->
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
				Response.Write ("<br><br>" & Trim(RS("SectionName")) & "<br><br>")
				strSection = RS("SectionName")
			End If
			If NOT strCategory = RS("CategoryName") Then
				Response.Write( Trim(RS("CategoryName")) & "<br>" )
				strCategory = RS("CategoryName")
			End If
			
			Response.Write("<input name=""chkQuests"" type=""checkbox"" value=""" & RS("Abbrev") & """ " & RS("Disabled") & ">" & RS("Question") & "<br>" )
			
			RS.MoveNext
		Loop
	End If
	RS.Close
	%>
<!-- <input name="chkQuests" type="checkbox" DISABLED> ALL <br>
Examining School Performance on Statewide Tests<br>
<input name="chkQuests" type="checkbox" value="1">	How did students perform on the state reading test at grade 3? <br>
<input name="chkQuests" type="checkbox" value="1">	How did students perform on state tests at grades 4, 8, and 10? <br>
<input name="chkQuests" type="checkbox" value="1">	How did performance of all students enrolled compare to continuing students only?<br>
<input name="chkQuests" type="checkbox" value="1">	How did the performance of my district compare to other districts statewide? <br>
	<br>
Examining Test Participation and Alternate Assessments<br>
<input name="chkQuests" type="checkbox" value="1">	How many students were not tested on WKCE and why?<br>
	<br>
Reviewing Other Student Performance Indicators<br>
<input name="chkQuests" type="checkbox" value="1">	What other evidence of student proficiency is available locally?<br>
<input name="chkQuests" type="checkbox" value="1">	What percent of students did not advance to the next grade level? <br>
<input name="chkQuests" type="checkbox" value="1">	How did students perform on college admissions and placement tests?<br>
<input name="chkQuests" type="checkbox" value="1">	What are the graduation rates? (Schools with grade 12 only)<br>
<input name="chkQuests" type="checkbox" value="1">	What are students' postgraduation plans? (Schools with grade 12 only)<br>
<br><br>
II
<br><br>
Reviewing School Programs and Processes<br>
<input name="chkQuests" type="checkbox" value="1">	What school-supported activities are offered?<br>
<input name="chkQuests" type="checkbox" value="1">	What are the district requirements for high school graduation?<br>
<input name="chkQuests" type="checkbox" value="1">	What advanced courses are offered? <br>
<br>
Examining Staffing Patterns<br>
<input name="chkQuests" type="checkbox" value="1">	What staff are available in this district?<br>
<input name="chkQuests" type="checkbox" value="1">	What are the qualifications of teachers? <br>
<br>
Examining Spending Patterns<br>
<input name="chkQuests" type="checkbox" value="1">	How much money is received and spent in this district?<br>
<input name="chkQuests" type="checkbox"  value="1" DISABLED>	[simple link]Where can I find more detailed school finance data? <br>
<br><br>
III
<br><br>
Examining Attendance Patterns<br>
<input name="chkQuests" type="checkbox" value="1">	What percent of students attend school each day?<br>
<input name="chkQuests" type="checkbox" value="1">	What percent of students are habitually truant?<br>
<br>
Examining Student Involvement<br>
<input name="chkQuests" type="checkbox" value="1">	Do students participate in school supported activities?<br>
<input name="chkQuests" type="checkbox" value="1">	What courses are students taking?<br>
<br>
Examining Disciplinary Patterns<br>
<input name="chkQuests" type="checkbox" value="1">	What percentage of students were suspended or expelled last year?<br>
<input name="chkQuests" type="checkbox" value="1">	What percentage of school days were lost due to suspension or expulsion?<br>
<input name="chkQuests" type="checkbox" value="1">	What types of incidents resulted in suspensions or expulsions? <br>
<input name="chkQuests" type="checkbox" value="1">	What happens after students are expelled?<br>
<br>
Examining Dropout Rates<br>
<input name="chkQuests" type="checkbox" value="1">	How many students dropped out of school last year?<br>
<br><br>
IV
<br><br>
<input name="chkQuests" type="checkbox" value="1">	What is the enrollment by student group?<br>
<input name="chkQuests" type="checkbox" value="1">	What are the primary disabilities of students in need of special education services? (not avail at school level until 2000-01)<br>
<input name="chkQuests" type="checkbox" value="1">	What are the characteristics of limited English proficient students at this school?<br>
 --><br><br>
<input type="button" value="Add File" onClick="VerifiedSubmit(frmDownload)">
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

