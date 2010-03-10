<%
Function CountSQLColumns(ByVal strSelectList, strFieldPrefix)
'MZD 20030606
'takes a string that is a SELECT statement and a "field prefix"
'assumes that each column in the SELECT List has a common prefix
	' therefore it wont work for a SQL call with a join
	' however, you could call the function twice and add the results
'strFieldPrefix should be like: "v_Dropouts." 
'strSelectList should only contain a SELECT statement and NOT a full SQL statement
'strSelectList the variable passed will NOT be affected (notice "ByVal")
dim strFind
dim intLength
dim intPosOne
dim intPosTwo
strFind = strFieldPrefix
intLength = Len(strFind)
CountSQLColumns = 0
Do While InStr(strSelectList, strFind)
	'hunt, discard, increment -- you know the drill...
	If InStr(strSelectList, strFind) Then
		intPosOne = InStr(strSelectList, strFind)
		If InStr(intPosOne + intLength, strSelectList, strFind) Then
			intPosTwo = InStr(intPosOne + intLength, strSelectList, strFind)
			strSelectList = Mid(strSelectList, intPosTwo)
		Else
			strSelectList = ""
		End IF
		CountSQLColumns = CountSQLColumns + 1
	End IF
Loop
End Function
'*************************
Sub PrintVar(strVarName)
	'mzd: 20030603
	'strVarName is a string containing a variable Name.
	'prints to screen in format <br>VarName[VarValue]<br>
	'works only with "global" variables
	execute( "Response.Write (""<br>" & strVarName & "["" & " & Replace(strVarName, """""","""") & " & ""]<br>"")" )
'Response.Write( "Response.Write (""<br>" & strVarName & "["" & " & strVarName & " & ""]<br>"")" )
End Sub
'*****************************************
SUB session_filename(zFiletitle)
	'HT June10/03: called in download file code; zFiletitle=zGraphtitle 
	'or zFiletitle=Chart.Title(CHART_TOPTIT) depending on each page
	if strOrgLevel="DI" or strOrgLevel="ST" then
		zFiletitle=replace(zFiletitle,":","")
		Session("FileName") = Replace(Replace(Replace(replace(zFiletitle,"/","_"), chr(13), "_"), chr(10), "_"), " ", "_")
	else
		Session("FileName") = Replace(Replace(Replace(replace(zFiletitle,"/","_"), chr(13), "_"), chr(10), "_"), " ", "_")
	end if
end sub
sub filequery(zView)
	'ht june 9/03: this sub is called in the Download file code on 
	'each individual page eg. gattendance, truancy ect...
	'together with session_filename(zFiletitle)
	' where zFiletitle=zGraphtitle or zFiletitle=Chart.Title(CHART_TOPTIT) depending on each page
	'filesql = lcase(filesql)  'doesn't work 
	filesql = replace(filesql,"&nbsp;","Student Group")
	filesql=replace(filesql,"v_enrollment.suppressed,","") 
	'filesql=replace(filesql,"fullkey,","")
	zYearFile="yearformatted as 'Year',"
	zDelete=zView & ".PriorYears , "
	filesql=replace(filesql,zDelete," ")
	zDelete=zView & ".PriorYear as 'Student Group'"
	filesql=replace(filesql,zDelete," ")
	zDelete=zView & ".PriorYear as 'Year'"
	filesql=replace(filesql,zDelete," ") 
	'if zView = "v_enrollment"  then
		'zPrepend = "Select keys.cesa,keys.[district number]," & _
					'"keys.[school Number], keys.[district name],keys.[School Name]," &_
					'"keys.schooltype,keys.charter,keys.AgencyKey,keys.Year,keys.Gender," &_
					'"keys.Race,keys.Grade, "
	'else
		zPrependA="Select " & zView & ".cesa, " & zView & ".[district number]," & zView & ".[school Number], " & zView & ".[district name]," & zView & ".[School Name]," & zView & ".schooltype," & zView & ".charter," & zView & ".AgencyKey,"
		zPrepend=zPrependA & zYearfile & "sexlabel as 'Gender',racelabel as 'Race',gradelabel as 'Grade',"
	'end if
	filesql=replace(filesql,"Select",zPrepend)
	filesql=replace(filesql,"select",zPrepend)  
	filesql=replace(filesql,"SELECT",zPrepend) 
	'ht take out the unwanted comma after , for eg. [Attendance Rate],
	'filequery=lcase(filequery) ' Not work whole filesql disappeared???
	'filesql=replace(filesql,", FROM","FROM") ' Not work
	'gmoney:
	filesql=replace(filesql,"DistState as 'Student GroupStudent Group',","DistState as 'DistState'," )
	filesql=replace(filesql,"Category as 'Student Group',","Category as 'Category',")
	zDelComma="Rate],"  '''' unsual characters eg. [, ' & ect.. have to be set in a variable then used in replace()
	filesql=replace(filesql,zDelComma,"Rate]") 
	'gssactivities
	filesql =replace(filesql,"v_enrollment.year,","v_enrollment.year as 'Enrollment Year',")
	session("filequery")=filesql
	'response.write("LAST FILE SQL:" & filesql)
	'END HT June9/03
END SUB

Sub BuildSQLWhere(ByRef strString, ByVal strNewConditions, ByVal strAndOr)
'MZD 20030527
'For adding db fields to a WHERE statement
'to make bln operator management easier in concatenation
'NO SQL KEYWORDS i.e. "WHERE ..." is wrong
'strAndOr must be "AND", "OR" (case in-sensitive)
'strString may be empty
'number of conditions in strNewConditions is irrelevant
'no dependancies
	strString = Trim(strString)
	strNewConditions = Trim(strNewConditions)
	If Len(strNewConditions) = 0 Then	'no conditions to add?
		Exit Sub
	End IF
	If NOT (UCase(strAndOr) = "AND" OR UCase(strAndOr) = "OR") Then
		If Trim(strAndOr) = "&" OR Trim(strAndOr) = "&&" Then	'I don't know why I am adding this option....
			strAndOr = "AND"
		ElseIf Trim(strAndOr) = "||" Then
			strAndOr = "OR"
		Else
			strAndOR = "AND"
		End IF	
	End IF
	If Len(strString) = 0 Then
		strString = strNewConditions
	Else
		strString = strString & " " & strAndOr & " " & strNewConditions
	End If
End Sub
'**************************************************************************
Sub BuildSQLOrderBy(ByRef strString, ByRef strNewFields, ByRef blnAddEnd)
	call BuildSQLSelect(strString, strNewFields, blnAddEnd)
End SUB
'**************************************************************************
Sub BuildSQLSelect(ByRef strString, ByVal strNewFields, ByRef blnAddEnd)
'MZD 20030527
'For adding db fields to a select statement
'to make seperator management easier in concatenation
'NO SQL KEYWORDS i.e. "SELECT ..." is wrong
'blnAddEnd = False "pre"-pends
'strString may be empty
'number of fields in strNewFields is irrelevant
'no dependancies
	strString = Trim(strString)
	strNewFields = Trim(strNewFields)
	If Len(strNewFields) = 0 Then	'no fields to add?
		Exit Sub
	End IF
	IF InStrRev(strNewFields,",") = Len(strNewFields) AND NOT Len(strString) = 0Then	'chop trailing commas
		strNewFields = Mid(strNewFields, 0, Len(strNewFields) - 1)
	End IF
	IF InStrRev(strString,",") = Len(strString) AND NOT Len(strString) = 0 Then	'chop trailing commas
		strString = Mid(strString, 0, Len(strString) - 1)
	End IF
	If Len(strString) = 0 Then
		strString = strNewFields
	ElseIF blnAddEnd Then
		strString = strString & ", " & strNewFields
	ElseIF NOT blnAddEnd Then
		strString = strNewFields & ", " & strString
	End If
End Sub
'**************************************************************************
Sub BuildSQLSelect2(ByRef strString, ByVal strNewFields, ByRef blnAddEnd)
' jdj: adding more extensive comma cleanup at bottom so can use commas between variables that are sometimes empty
'MZD 20030527
'For adding db fields to a select statement
'to make seperator management easier in concatenation
'NO SQL KEYWORDS i.e. "SELECT ..." is wrong
'blnAddEnd = False "pre"-pends
'strString may be empty
'number of fields in strNewFields is irrelevant
'no dependancies
	strString = Trim(strString)
	strNewFields = Trim(strNewFields)
	If Len(strNewFields) = 0 Then	'no fields to add?
		Exit Sub
	End IF
	IF InStrRev(strNewFields,",") = Len(strNewFields) AND NOT Len(strString) = 0Then	'chop trailing commas
		strNewFields = Mid(strNewFields, 0, Len(strNewFields) - 1)
	End IF
	IF InStrRev(strString,",") = Len(strString) AND NOT Len(strString) = 0 Then	'chop trailing commas
		strString = Mid(strString, 0, Len(strString) - 1)
	End IF
	If Len(strString) = 0 Then
		strString = strNewFields
	ElseIF blnAddEnd Then
		strString = strString & ", " & strNewFields
	ElseIF NOT blnAddEnd Then
		strString = strNewFields & ", " & strString
	End If
	' chop leading commas
	do while left(trim(strString),1) = "," 
		strString = right(strString,(len(strString)-1))
	loop
	' chop trailing commas
	do while right(trim(strString),1) = "," 
		strString = left(strString,(len(strString)-1))
	loop
	' remove spaces before checking for double commas
	strString = replace(strString,", ",",")
	strString = replace(strString," ,",",")
	' eliminate double commas
	do until InStr(strString,",,") = 0
		strString = replace(strString,",,",",")
	loop
	' put trailing spaces back in for convenience 
	strString = replace(strString,",",", ")
End Sub
'**************************************************************************
Function SchoolYearFormat(strYear)
'mzd 20030521  
'accepts YYYY
'returns YYYY - YY
	strYear = Trim(strYear)
	If NOT IsNumeric(strYear) OR NOT Len(strYear) = 4 Then
		Exit Function
	End IF
	SchoolYearFormat = CSTR(CINT(strYear)-1) & "-" & Right(strYear,2)
End Function
'**************************************************************************
Sub TableFromSQLColRange(zRS, intNumColumn, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	'mzd 20030521
	'intNumColumn is the number of columns to show starting with the first column(field) (of the recordset)
	'neg one intNumColumn uses recordcount
	'Dependence: ColumnAlignArray(); ColumnFormatArray(); nodata; zGraphTitle; BrMaker(); FormatTableCall();
	'Operates on: zDetailTable
	dim intTopBlankCellSpan
	dim strFieldName
	dim field
	dim zFirstColHold
	IF NOT nodata Then	'this test should prolly be replaced with a direct test on the RS to make this sub more self contained...
		zRS.movefirst
		IF intNumColumn = -1 Then
			intNumColumn = zRS.Fields.Count - 1
		Else
			intNumColumn = intNumColumn - 1	'make zero-based
		End IF
		strFieldName = CSTR(zRS.Fields(0).Name)
		intTopBlankCellSpan = 0
		For each field in zRS.Fields
			If strFieldName = CSTR(field.Name) Then
				intTopBlankCellSpan = intTopBlankCellSpan + 1
			Else
				Exit For
			End If
		Next
		'Table Header
		zDetailTable = "<table width=""460"" border=""1"" cellpadding=""2"">" & vbNewLine & "<TR>"  & vbNewLine & _
						"<TD colspan=""" & (intTopBlankCellSpan + intNumColumn + 1 ) & """ " & _
						"ALIGN=""CENTER"" VALIGN=""TOP"" BGCOLOR=""" & HeadBGColor & """><span class=""text"">" & _
						BrMaker(zGraphTitle) & "</span></TD></TR>" & vbNewLine & "<TR>" & vbNewLine
		'create column header row
		zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD colspan=""" & intTopBlankCellSpan & """>&nbsp;</TD>"
		For i = intTopBlankCellSpan  To intNumColumn
		  	zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD ALIGN=""CENTER"" VALIGN=""TOP""><span class=""text"">" & _
							zRS.Fields(i).name & "</span></TD>" & vbNewLine
		Next
		zDetailTable = zDetailTable & "</TR>" & vbNewLine 
		' set zSpanRow
		zFirstColHold = cSTR(zRS.Fields(0).Value)
		zSpanRow = 0 
		Do while not zRS.EOF
			If zFirstColHold = cSTR(zRS.Fields(0).Value) Then
				zSpanRow = zSpanRow + 1
			Else
				Exit Do
			End IF
			zRS.MoveNext
		Loop
		zRS.movefirst
		zFirstColHold = ""
		Do While Not zRS.EOF
	    	zDetailTable = zDetailTable & vbNewLine  & "<TR>"
			For i = 0 To intNumColumn	'loop through the fields
				zDisplayMe = FormatTableCol(zRS, i, ColumnFormatArray(i))
				' brb add wkce suppression overrides to the tabe data
				Select Case left(zDisplayMe,3)
				Case "-10"
					'' replace with *
					zDisplayMe = "*"
				Case "-20","-40"
					zDisplayMe = "N/A"
				Case "-30"
					zDisplayMe = "All"
				End Select
				zDisplayMe = "<span class=""text"">" & zDisplayMe & "</span>"
				' was this zDisplayMe = "<span class=""text"">" & FormatTableCol(zRS, i, ColumnFormatArray(i)) & "</span>"
				If i = 0 THEN
					If NOT trim(zFirstColHold) = trim(zRS.Fields(0).Value) THEN '?write the first column td?
					    zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD VALIGN=""TOP"" ROWSPAN=""" & zSpanRow & """ ALIGN=""" & _
										ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
						zFirstColHold = trim(zRS.Fields(0).Value)	'next val to hold
					END IF
				ELSE
				    zDetailTable = zDetailTable & vbTab & vbTab & "<TD ALIGN=""" & ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
				END IF
			Next
		    zDetailTable = zDetailTable & "</TR>" & vbNewLine
			zRS.MoveNext
		Loop
	    zDetailTable = zDetailTable & "</TABLE>" & vbNewLine
	END IF
END SUB
'**************************************************************************
Sub TableFromSQLColRangeSubHeaderRow(zRS, intNumColumn, HeadBGcolor, ColumnAlignArray, ColumnFormatArray, strSubHeaderRow)
	'mzd 20030521
	'intNumColumn is the number of columns to show starting with the first column(field) (of the recordset)
	'neg one intNumColumn uses recordcount
	'Dependence: ColumnAlignArray(); ColumnFormatArray(); nodata; zGraphTitle; BrMaker(); FormatTableCall();
	'Operates on: zDetailTable
	dim intTopBlankCellSpan
	dim strFieldName
	dim field
	dim zFirstColHold
	IF NOT nodata Then	'this test should prolly be replaced with a direct test on the RS to make this sub more self contained...
		zRS.movefirst
		IF intNumColumn = -1 Then
			intNumColumn = zRS.Fields.Count - 1
		Else
			intNumColumn = intNumColumn - 1	'make zero-based
		End IF
		strFieldName = CSTR(zRS.Fields(0).Name)
		intTopBlankCellSpan = 0
		For each field in zRS.Fields
			If strFieldName = CSTR(field.Name) Then
				intTopBlankCellSpan = intTopBlankCellSpan + 1
			Else
				Exit For
			End IF
		Next
		'Table Header
		zDetailTable = "<table width=""460"" border=""1"" cellpadding=""2"">" & vbNewLine & "<TR>"  & vbNewLine & _
						"<TD colspan=""" & (intTopBlankCellSpan + intNumColumn + 1 ) & """ " & _
						"ALIGN=""CENTER"" VALIGN=""TOP"" BGCOLOR=""" & HeadBGColor & """><span class=""text"">" & _
						BrMaker(zGraphTitle) & "</span></TD></TR>" & vbNewLine & strSubHeaderRow & vbNewLine & "<TR>" & vbNewLine
		'create column header row
		' this hard-codes the upper right one or two cells of the table to be blank - not good - better to control this in the page
		zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD colspan=""" & intTopBlankCellSpan & """>&nbsp;</TD>"
		For i = intTopBlankCellSpan to intNumColumn
		  	zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD ALIGN=""CENTER"" VALIGN=""TOP""><span class=""text"">" & _
							zRS.Fields(i).name & "</span></TD>" & vbNewLine
		Next
		zDetailTable = zDetailTable & "</TR>" & vbNewLine 
		' set zSpanRow
		zFirstColHold = zRS.Fields(0).Value
		zSpanRow = 0 
		Do UNTIL zRS.EOF
			If zFirstColHold = zRS.Fields(0).Value Then
				zSpanRow = zSpanRow + 1
			Else
				Exit Do
			End IF
			zRS.MoveNext
		Loop
		zRS.movefirst
		zFirstColHold = ""
		Do While Not zRS.EOF
	    	zDetailTable = zDetailTable & vbNewLine  & "<TR>"
			For i = 0 To intNumColumn	'loop through the fields
				zDisplayMe = "<span class=""text"">" & FormatTableCol(zRS, i, ColumnFormatArray(i)) & "</span>"
				If i = 0 THEN
					If NOT trim(zFirstColHold) = trim(zRS.Fields(0).Value) THEN '?write the first column td?
					    zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD VALIGN=""TOP"" ROWSPAN=""" & zSpanRow & """ ALIGN=""" & _
										ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
						zFirstColHold = trim(zRS.Fields(0).Value)	'next val to hold
					END IF
				ELSE
				    zDetailTable = zDetailTable & vbTab & vbTab & "<TD ALIGN=""" & ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
				END IF
			Next
		    zDetailTable = zDetailTable & "</TR>" & vbNewLine
			zRS.MoveNext
		Loop
	    zDetailTable = zDetailTable & "</TABLE>" & vbNewLine
	END IF
END SUB
'************************************************************************************
Sub TableFromSQL(zRS, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	'mzd wuz here 20030516
	'Dependence: ColumnAlignArray(); ColumnFormatArray(); nodata; zGraphTitle; BrMaker(); FormatTableCall();
	'Operates on: zDetailTable
	dim intNumColumn
	dim intTopBlankCellSpan
	dim strFieldName
	dim field
	dim zFirstColHold
	IF NOT nodata Then	'where the heck does this var come from? - mzd
		zRS.movefirst
		intNumColumn = zRS.Fields.Count - 1
		strFieldName = CSTR(zRS.Fields(0).Name)
		intTopBlankCellSpan = 0
		For each field in zRS.Fields
			If strFieldName = CSTR(field.Name) Then
				intTopBlankCellSpan = intTopBlankCellSpan + 1
			Else
				Exit For
			End IF
		Next
		'Table Header
		zDetailTable = "<table width=""460"" border=""1"" cellpadding=""2"">" & vbNewLine & "<TR>"  & vbNewLine & _
						"<TD colspan=""" & (intNumColumn + 1 ) & """ " & _
						"ALIGN=""CENTER"" VALIGN=""TOP"" BGCOLOR=""" & HeadBGColor & """><span class=""text"">" & _
						BrMaker(zGraphTitle) & "</span></TD></TR>" & vbNewLine & "<TR>" & vbNewLine
		'create column header row
		zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD colspan=""" & intTopBlankCellSpan & """>&nbsp;</TD>"
		For i = intTopBlankCellSpan  To intNumColumn
		  	zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD ALIGN=""CENTER"" VALIGN=""TOP""><span class=""text"">" & _
							zRS.Fields(i).name & "</span></TD>" & vbNewLine
		Next
		zDetailTable = zDetailTable & "</TR>" & vbNewLine 
		' set zSpanRow
		zFirstColHold = zRS.Fields(0).Value
		zSpanRow = 0 
		Do UNTIL zRS.EOF
			If zFirstColHold = zRS.Fields(0).Value Then
				zSpanRow = zSpanRow + 1
			Else
				Exit Do
			End IF
			zRS.MoveNext
		Loop
		zRS.movefirst
		zFirstColHold = ""
		Do While Not zRS.EOF
	    	zDetailTable = zDetailTable & vbNewLine  & "<TR>"
			For i = 0 To intNumColumn	'loop through the fields
				zDisplayMe = "<span class=""text"">" & FormatTableCol(zRS, i, ColumnFormatArray(i)) & "</span>"
				If i = 0 THEN
					If NOT trim(zFirstColHold) = trim(zRS.Fields(0).Value) THEN '?write the first column td?
					    zDetailTable = 	zDetailTable & vbTab & vbTab & "<TD VALIGN=""TOP"" ROWSPAN=""" & zSpanRow & """ ALIGN=""" & _
										ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
						zFirstColHold = trim(zRS.Fields(0).Value)	'next val to hold
					END IF
				ELSE
				    zDetailTable = zDetailTable & vbTab & vbTab & "<TD ALIGN=""" & ColumnAlignArray(i) & """>" & zDisplayMe & "</TD>" & vbNewLine 
				END IF
			Next
		    zDetailTable = zDetailTable & "</TR>" & vbNewLine
			zRS.MoveNext
		Loop
	    zDetailTable = zDetailTable & "</TABLE>" & vbNewLine
	END IF
END SUB
'***************************************************************************
Sub TableFromSQLgroup(zRS, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	If nodata = false then
		zRS.movefirst
		zDetailTable = "<table width='460' border='1' cellpadding='2'><TR>"
		zDetailTable = zDetailTable & "<TD colspan='" & zRS.Fields.Count & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & BrMaker(zGraphTitle) & "</span></TD></TR><TR>"
		MaxColumn = zRS.Fields.Count - 1
		For i = 0 To MaxColumn
		  	zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRS.Fields(i).name & "</span></TD>"
		Next
		zDetailTable = zDetailTable & "</TR>"
		zSpanRow = 0 
		zFirstColHold =  trim(zRS.Fields(0).Value)
		Do while Not zRS.EOF
			If trim(zFirstColHold) = trim(zRS.Fields(0).Value) THEN
				zSpanRow = zSpanRow + 1
				zFirstColHold = trim(zRS.Fields(0).Value) 
			Else
				exit do
			END IF
			zRS.movenext
		Loop
		zRS.movefirst
		zFirstColHold = ""
		Do While Not zRS.EOF
	    	zDetailTable = zDetailTable & "<TR>"
			For i = 0 To MaxColumn
				zDisplayMe = "<span class='text'>" & FormatTableCol(zRS, i, ColumnFormatArray(i)) & "</span>"
				If i = 0 THEN
					If trim(zFirstColHold) <> trim(zRS.Fields(0).Value) THEN
					    zDetailTable = zDetailTable & "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>"
					END IF
					zFirstColHold = trim(zRS.Fields(0).Value)
				ELSE
				    zDetailTable = zDetailTable & "<TD ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>"
				END IF
			Next
		    zDetailTable = zDetailTable & "</TR>"
			zRS.MoveNext
		Loop
	    zDetailTable = zDetailTable & "</TABLE>"
	END IF
END SUB
'***************************************************************************
Function showFay()
	IF strOrgLevel="SC" or strOrgLevel="DI" THEN
		showFay = " FAY "
	ELSE
		showFay = ""
	END IF
end function
'***************************************************************************
function ShowSC ()
		If strOrgLevel="SC" then
				if trim(session("SchoolWebAddress"))="ftp://" or trim(session("SchoolWebAddress"))="http://" or session("SchoolWebAddress")="" or session("SchoolWebAddress") = " " then
								ShowSC = session("schoolname")
				elseif trim(session("SchoolWebAddress"))<>"ftp://" or trim(session("SchoolWebAddress"))<>"http://" or session("SchoolWebAddress")<>"" or session("SchoolWebAddress") = " " then
						ShowSC = "<A HREF=javascript:popup('" & session("SchoolWebAddress") & "') >" & Session("SchoolName") & "</A>" 
				end if
		elseif strOrgLevel="DI" then
				if trim(session("DistrictWebAddress"))="ftp://" or trim(session("DistrictWebAddress"))="http://" or session("DistrictWebAddress")="" or session("SchoolWebAddress") = " " then
						ShowSC = session("districtname")
				elseif trim(session("DistrictWebAddress"))<>"ftp://" or trim(session("DistrictWebAddress"))<>"http://" or session("DistrictWebAddress")<>"" or session("SchoolWebAddress") = " " then
						ShowSC = "<A HREF=javascript:popup('" & session("DistrictWebAddress") & "') >" & Session("DistrictName") & "</A>" 
				end if
		else
				ShowSC = strAgencyTitle 
		end if
end function
'***************************************************************************
Function FormatTableCol(zRS, zWhich, zEvalString)
	If not isnull(zRS.Fields(zWhich).Value) THEN

		' capture the string from the RS and apply WKCESuppressed
		strTemp = zRS.Fields(zWhich).Value 'WKCESuppressed(zRS.Fields(zWhich).Value)
		Select Case zEvalString
		Case "STR"
			FormatTableCol = strTemp ' trim(cSTR(strTemp))
		Case "DEC1"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,1)
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "NUM"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,0)
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "DEC2"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,2)
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "CUR"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatCurrency(strTemp,0)
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "PERC"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,0) + "%"
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "DEC1PERC"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,1) + "%"
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "DEC2PERC"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,2) + "%"
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		CASE "DEC3PERC"
			If isnumeric(trim(strTemp)) THEN
				FormatTableCol = FormatNumber(strTemp,3) + "%"
			ELSE
				FormatTableCol = trim(cSTR(strTemp))
			END IF
		End Select
	Else
		FormatTableCol = "n/a"
	END IF
	
End Function
'***************************************************************************
FUNCTION BrMaker(zInputString)
        do while inSTR(zInputString,chr(13) & chr(10)) > 0
            zInputString = mid(zInputString,1,InSTR(zInputString,chr(13) & chr(10))-1) + "<BR>" + mid(zInputString,(InSTR(zInputString,chr(13) & chr(10)) + 1))
        loop
        BrMaker =  ZInputString
END FUNCTION
'***************************************************************************
FUNCTION SuspExpLinks(ZQueryString)
	SuspExpLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><tr valign='top'><TD WIDTH=60 class='text'>Show:</TD><TD class='text'>"
	If zSuspExp = "SUSP" THEN
		SuspExpLinks = SuspExpLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Suspensions</FONT> &#149; <A HREF='graphshell.asp?SUSPEXP=EXP&" & zQueryString & "'>Expulsions</A>"
	ELSE
		SuspExpLinks = SuspExpLinks & "<A HREF='graphshell.asp?SUSPEXP=SUSP&" & zQueryString & "'>Suspensions</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Expulsions</FONT>"
	END IF
	SuspExpLinks = SuspExpLinks & "</TD></tr></TABLE>"
END FUNCTION
'***************************************************************************
FUNCTION SuspExpWeaponLinks(ZQueryString)
	SuspExpWeaponLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><tr valign='top'><TD WIDTH=60 class='text'>Type:</TD><TD class='text'>"
	If zWeapon = "YES" THEN
		SuspExpWeaponLinks = SuspExpWeaponLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Weapon/Drug Related</FONT> &#149; " & _ 
			"<A HREF='graphshell.asp?WEAPON=NO&" & zQueryString & "'>Not Weapon/Drug Related</A>"
	ELSE
		SuspExpWeaponLinks = SuspExpWeaponLinks & "<A HREF='graphshell.asp?WEAPON=YES&" & zQueryString & "'>Weapon/Drug Related</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Not Weapon/Drug Related</FONT>"
	END IF
	SuspExpWeaponLinks = SuspExpWeaponLinks & "</TD></tr></TABLE>"
END FUNCTION
'***************************************************************************
FUNCTION SuspExpIncidentLinks(ZQueryString)
	SuspExpIncidentLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</FONT></TD><td class='text'>"
	If zINCIDENT = "RATE" THEN
		SuspExpIncidentLinks = SuspExpIncidentLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Incident Rate</FONT> &#149; "
			If zGroup = "AllStudentsFAY" or zCompareTo <> "CURR" Then
				SuspExpIncidentLinks = SuspExpIncidentLinks & _
				"<A HREF='graphshell.asp?INCIDENT=CONS&" & zQueryString & "'>Disciplinary Consequences</A>"
			Else
				SuspExpIncidentLinks = SuspExpIncidentLinks & " <A HREF='graphshell.asp?INCIDENT=SHORT&" & zQueryString & "'>Disciplinary Consequences: " & _
				"Short Suspension</A> | " & _ 
				"<A HREF='graphshell.asp?INCIDENT=LONG&" & zQueryString & "'>Long Suspension</A> | " & _ 
				"<A HREF='graphshell.asp?INCIDENT=EXPULSION&" & zQueryString & "'>Expulsion</A>"
			END IF
	Elseif zINCIDENT = "CONS" THEN
		SuspExpIncidentLinks = SuspExpIncidentLinks & "<A HREF='graphshell.asp?INCIDENT=RATE&" & zQueryString & "'>Incident Rate</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Disciplinary Consequences</FONT>"
	ELSEIF zINCIDENT = "SHORT" THEN
		SuspExpIncidentLinks = SuspExpIncidentLinks & "<A HREF='graphshell.asp?INCIDENT=RATE&" & zQueryString & "'>Incident Rate</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Short Suspension</FONT> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=LONG&" & zQueryString & "'>Long Suspension</A> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=EXPULSION&" & zQueryString & "'>Expulsion</A> &#149; "
	ELSEIF zINCIDENT = "LONG" THEN
		SuspExpIncidentLinks = SuspExpIncidentLinks & "<A HREF='graphshell.asp?INCIDENT=RATE&" & zQueryString & "'>Incident Rate</A> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=SHORT&" & zQueryString & "'>Short Suspension</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & ">Long Suspension</FONT> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=EXPULSION&" & zQueryString & "'>Expulsion</A>"
	ELSEIF zINCIDENT = "EXPULSION" THEN
		SuspExpIncidentLinks = SuspExpIncidentLinks & "<A HREF='graphshell.asp?INCIDENT=RATE&" & zQueryString & "'>Incident Rate</A> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=SHORT&" & zQueryString & "'>Short Suspension</A> &#149; " & _ 
			"<A HREF='graphshell.asp?INCIDENT=LONG&" & zQueryString & "'>Long Suspension</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Expulsion</FONT>"
	END IF
	SuspExpIncidentLinks = SuspExpIncidentLinks & "</TD></tr></TABLE>"
END FUNCTION
'***************************************************************************
' dsr 2/16/01
FUNCTION SSActLinks(ZQueryString)
	SSActLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	If zShow = "EXTRA" Then
		SSActLinks = SSActLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Extra/Co-curricular Activities</FONT> &#149; "
		SSActLinks = SSActLinks & _
		"<A HREF='graphshell.asp?Graphfile=SSACTIVITIES&Show=COMM" & zQueryString & "'>Community Activities</A>"
	Else 'COMM
		SSActLinks = SSActLinks & _
		"<A HREF='graphshell.asp?Graphfile=SSACTIVITIES&Show=EXTRA" & zQueryString & "'>Extra/Co-curricular Activities</A> &#149; "
		SSActLinks = SSActLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Community Activities</FONT>"
	END IF
	SSactLinks = SSactLinks & "</TD></TABLE>"
END FUNCTION
'***************************************************************************
FUNCTION WKCEParticipationLinks(ZQueryString)
	WKCEParticipationLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	If zNTVar = "EXCLUDED" THEN
		  WKCEParticipationLinks =  WKCEParticipationLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Pre-Req Skills/Eng.</FONT> &#149; "
	ELSE
		 WKCEParticipationLinks =  WKCEParticipationLinks & "<A HREF='graphshell.asp?NTVAR=EXCLUDED&" & zQueryString & "'>Pre-Req Skills/Eng.</A> &#149; "
	END IF
	If zNTVar = "EXCUSED" THEN
		 WKCEParticipationLinks =  WKCEParticipationLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Excused by parent</FONT> &#149; "
	ELSE
		 WKCEParticipationLinks =  WKCEParticipationLinks & "<A HREF='graphshell.asp?NTVAR=EXCUSED&" & zQueryString & "'>Excused by parent</A> &#149; "
	END IF
	If zNTVar = "ELIGNT" THEN
		 WKCEParticipationLinks =  WKCEParticipationLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Eligible not tested</FONT>"
	ELSE
		 WKCEParticipationLinks =  WKCEParticipationLinks & "<A HREF='graphshell.asp?NTVAR=ELIGNT&" & zQueryString & "'>Eligible not tested</A> "
	END IF
 	WKCEParticipationLinks =  WKCEParticipationLinks & "</TD></TABLE>"
END FUNCTION
'***************************************************************************
Function GetSuspExp()
	If not isempty(Request.QueryString("SuspExp")) THEN
		GetSuspExp = Request.QueryString("SuspExp")
	ELSE
		GetSuspExp = "SUSP"
	END IF
End Function
'***************************************************************************
FUNCTION CheckForApostrophe(zInputString)
        do while inSTR(zInputString,"'") > 0
            zInputString = mid(zInputString,1,InSTR(zInputString,"'")-1) + "~" + mid(zInputString,(InSTR(zInputString,"'") + 1))
        loop
        do while inSTR(zInputString,"~") > 0
             zInputString = mid(zInputString,1,InSTR(zInputString,"~")-1) + "''" + mid(zInputString,(InSTR(zInputString,"~") + 1))
        loop
        CheckForApostrophe =  ZInputString
END FUNCTION
'***************************************************************************
Function RaceName(zWhich)
	Select Case zWhich
	Case "1"
		Racename = "American Indian/Alaskan Native"
	Case "2"
		RaceName = "Asian/Pacific Islander"
	Case "3"
		RaceName = "Black (Not of Hispanic Origin)"
	Case "4"
		RaceName = "Hispanic"
	Case "5"
		RaceName = "White (Not of Hispanic Origin)"
	Case "6"
		RaceName =  "Combined Groups/Small Number"		
	Case "8"
		RaceName =  "Missing/Invalid"
	End Select
End Function
'***************************************************************************
Function Gendername(zWhich)
	Select Case zWhich
	Case "1"
		Gendername = "Female"
	Case "2"
		Gendername = "Male"
	Case "8"
		Gendername = "Missing/Invalid"
	Case "9"
		Gendername = "Combined"
	End Select
End Function
'***************************************************************************
Function WKCESuppressed(zValue)
IF NOT Isnull(zValue) THEN
	IF rtrim(cSTR(zValue)) = "-10" THEN
		WKCESuppressed = "*"
	Elseif rtrim(cSTR(zValue)) = "-20" or rtrim(cSTR(zValue)) = "-40" THEN
		WKCESuppressed = "N/A"
	Elseif rtrim(cSTR(zValue)) = "-30" THEN
		WKCESuppressed = "All"
	ELSE
		WKCESuppressed = "NO" ' rtrim(cstr(zValue))
	END IF
	'IF NOT Isnull(zValue) THEN
	'	Select Case rtrim(cSTR(zValue))
	'	Case "-10"
	'		WKCESuppressed = "*"
	'	Case "-20"
	'		WKCESuppressed = "N/A"
	'	Case "-30"
	'		WKCESuppressed = "All"
	'	Case "-40"
	'		WKCESuppressed = "N/A"
	'	
	'	Case Else
	'		WKCESupressed = rtrim(cstr(zValue))
	'	End Select
	ELSE
		WKCESuppressed = "N/A"
	END IF
	
End Function
'***************************************************************************
Function NonWKCESuppressed(zValue)
	IF NOT Isnull(zValue) THEN
		Select Case cSTR(zValue)
		Case "-10"
			NonWKCESuppressed = "*"
		Case "-20"
			NonWKCESuppressed = "N/A"
		Case "-30"
			NonWKCESuppressed = "All"
		Case "0"
			NonWKCESuppressed = "*"
		Case Else
			NonWKCESuppressed = "NO"
		End Select
	ELSE
		NonWKCESuppressed = "N/A"
	END IF
End Function
'***************************************************************************
Function WKCESuppressedFormat(zCheck,zValue,multiplier)
	IF NOT Isnull(zCheck) THEN
		Select Case cSTR(zCheck)
		Case "-10"
			WKCESuppressedFormat = "*"
		Case "-20"
			WKCESuppressedFormat = "N/A"
		Case "-30"
			WKCESuppressedFormat = "All"
		Case Else
			WKCESuppressedFormat = formatnumber(zValue*multiplier,1)
		End Select
	ELSE
		WKCESuppressedFormat = "N/A"
	END IF
End Function
'***************************************************************************
Function WKCESuppressedAdded(zValue)
	' function which deals with suppression when 2 perf levels are added together
	IF NOT Isnull(zValue) THEN
		Select Case cSTR(zValue)
		' jdj: fails when -10 comes thru - adding test
		Case "-10"
			WKCESuppressedAdded = "*"
		Case "-20"
			WKCESuppressedAdded = "*"
		Case "-40"
			WKCESuppressedAdded = "N/A"
		Case "-60"
			WKCESuppressedAdded = "All"
		Case Else
			WKCESuppressedAdded = "NO"
		End Select
	ELSE
		WKCESuppressedAdded = "N/A"
	END IF
End Function
'***************************************************************************
Function WKCESuppressedAdded3(zValue)
	' huong 11/28/01: to add adv + prof + basic perf levels
	' function which deals with suppression when 3 perf levels are added together
	IF NOT Isnull(zValue) THEN
		Select Case cDBL(zValue)
		Case -30
			WKCESuppressedAdded3 = "*"
		Case -60
			WKCESuppressedAdded3= "N/A"
		Case -90
			WKCESuppressedAdded3 = "All"
		Case Else
			WKCESuppressedAdded3 = "NO"
		End Select
	ELSE
		WKCESuppressedAdded3 = "N/A"
	END IF
End Function
'***************************************************************************
Function WKCEGradeLinks(ZQueryString)
WKCEGradeLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Grade:<br><img src='/sig/images/spacer.gif' width=54 height=1 border=0 alt=''></TD><TD class='text'>" 
If strOrgLevel = "SC" THEN
	IF Session("HasG4") = "T" THEN
		If zGrade = "4" THEN
			WKCEGradeLinks = WKCEGradeLinks & "<FONT COLOR='" & zActiveLinkColor & "'>4</FONT>"
		ELSE
			WKCEGradeLinks = WKCEGradeLinks & "<A HREF='graphshell.asp?Grade=4&" & zQueryString & "'>4</A>"
		END IF
	Else
		WKCEGradeLinks = WKCEGradeLinks & "<FONT COLOR='#bcbcbc'>4</FONT>"
	END IF
	WKCEGradeLinks = WKCEGradeLinks & " &#149; "
	IF Session("HasG8") = "T" THEN
		If zGrade = "8" THEN
			WKCEGradeLinks = WKCEGradeLinks & " <FONT COLOR='" & zActiveLinkColor & "'>8</FONT>"
		ELSE
			WKCEGradeLinks = WKCEGradeLinks & " <A HREF='graphshell.asp?Grade=8&" & zQueryString & "'>8</A>"
		END IF
	Else
		WKCEGradeLinks = WKCEGradeLinks & "<FONT COLOR='#bcbcbc'>8</FONT>"
	END IF
	WKCEGradeLinks = WKCEGradeLinks & " &#149; "
	IF Session("HasG10") = "T" THEN
		If zGrade = "10" THEN
			WKCEGradelinks = WKCEGradeLinks & " <FONT COLOR='" & zActiveLinkColor & "'>10</FONT></A>"
		ELSE
			WKCEGradelinks = WKCEGradeLinks & " <A HREF='graphshell.asp?Grade=10&" & zQueryString & "'>10</A>"
		END IF
	Else
		WKCEGradeLinks = WKCEGradeLinks & "<FONT COLOR='#bcbcbc'>10</FONT>"
	END IF
Else
		If zGrade = "4" THEN
			WKCEGradeLinks = WKCEGradeLinks & "<FONT COLOR='" & zActiveLinkColor & "'>4</FONT>"
		ELSE
			WKCEGradeLinks = WKCEGradeLinks & "<A HREF='graphshell.asp?Grade=4&" & zQueryString & "'>4</A>"
		END IF
		WKCEGradeLinks = WKCEGradeLinks & " &#149; "
		If zGrade = "8" THEN
			WKCEGradeLinks = WKCEGradeLinks & " <FONT COLOR='" & zActiveLinkColor & "'>8</FONT>"
		ELSE
			WKCEGradeLinks = WKCEGradeLinks & " <A HREF='graphshell.asp?Grade=8&" & zQueryString & "'>8</A>"
		END IF
		WKCEGradeLinks = WKCEGradeLinks & " &#149; "
		If zGrade = "10" THEN
			WKCEGradelinks = WKCEGradeLinks & " <FONT COLOR='" & zActiveLinkColor & "'>10</FONT></A>"
		ELSE
			WKCEGradelinks = WKCEGradeLinks & " <A HREF='graphshell.asp?Grade=10&" & zQueryString & "'>10</A>"
		END IF
END IF
WKCEGradeLinks = WKCEGradeLinks & "</TD></TR></TABLE>"
End Function
'***************************************************************************
Function FirstWKCEGrade()
	IF Session("HasG4") = "T" THEN
		FirstWKCEGrade = "4"
	ELSEIF Session("HasG8") = "T" THEN
		FirstWKCEGrade = "8"
	ELSEIF Session("HasG10") = "T" THEN
		FirstWKCEGrade = "10"
	ELSE
        IF strOrglevel = "SC" THEN
    		FirstWKCEGrade = "XX"
        ELSE
    		FirstWKCEGrade = "4"
        END IF
		'no WKCE eligible grades for this school so flag to put up a message
	END IF
End Function
'***************************************************************************
Function WKCESubjectLinks(zQueryString)
'used by gACT as well --mzd 03-02
' KEY: Reading = 1RE ; Language/English = 2LA ; Mathematics = 3MA ; Science = 4SC ; Social Studies = 5SS ; Summary =6SM;
WKCESubjectlinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Subject:</TD><td class='text'>"
	If zSubjectID = "1RE" THEN
		WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Reading</FONT>" & " &#149; "
	ELSE
		WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=1RE&" & zQueryString & "'>Reading</A>" & " &#149; "
	END IF
'WKCESubjectlinks = WKCESubjectlinks & " &#149; "
WKCESubjectlinks = WKCESubjectlinks 
	IF zGraphInclude <> "ACT" THEN
		If zSubjectID = "2LA"  THEN
			WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Language</FONT>"
		ELSE
			WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=2LA&" & zQueryString & "'>Language</A>"
		END IF
	ELSE
		If zSubjectID = "2LA"  THEN
			WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>English</FONT>"
		ELSE
			WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=2LA&" & zQueryString & "'>English</A>"
		END IF
	END IF
WKCESubjectlinks = WKCESubjectlinks & " &#149; "
	If zSubjectID = "3MA" THEN
		WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Mathematics</FONT>"
	ELSE
		WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=3MA&" & zQueryString & "'>Mathematics</A>"
	END IF
	WKCESubjectlinks = WKCESubjectlinks & " &#149; "
	If zSubjectID = "4SC" THEN
		WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Science</FONT>"
	ELSE
		WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=4SC&" & zQueryString & "'>Science</A>"
	END IF
WKCESubjectlinks = WKCESubjectlinks & " &#149; "
	IF zGraphInclude = "ACT" THEN
		WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='#BCBCBC'>Social Studies</FONT>"
	ELSE
		If zSubjectID = "5SS" THEN
			WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Social Studies</FONT>"
		ELSE
			WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=5SS&" & zQueryString & "'>Social Studies</A>"
		END IF
	END IF
WKCESubjectlinks = WKCESubjectlinks & " &#149; "
	IF zGraphInclude <> "ACT" THEN
		WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='#BCBCBC'>Summary</FONT>"
	ELSE
		If zSubjectID = "6SM" THEN
			WKCESubjectlinks = WKCESubjectlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Summary</FONT>"
		ELSE
			WKCESubjectlinks = WKCESubjectlinks &  "<A HREF='graphshell.asp?SubjectID=6SM&" & zQueryString & "'>Summary</A>"
		END IF
	END IF	
WKCESubjectlinks = WKCESubjectlinks & "</TD></TR></TABLE>"
End Function
'***************************************************************************
'Function WKCEGroupLinks(zQueryString)
	'WKCEGrouplinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	'If zGroup = "AllStudentsFAY" THEN
	'	WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	'ELSE
		'WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	'If zGroup = "Gender" THEN
		'WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
	'ELSE
		'WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	'If zGroup = "Race/Ethnicity" THEN
	'	WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
	'ELSE
		'WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	'If zGroup = "Disability" THEN
	'	WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
	'ELSE
	'	WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	'If zGroup = "EconomicStatus" THEN
	'	WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Economic Status</FONT> "
	'ELSE
		'WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=EconomicStatus&" & zQueryString & "'>Economic Status</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	'If zGroup = "EnglishProficiency" THEN
		'WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>English Proficiency</FONT> "
	'ELSE
		'WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=EnglishProficiency&" & zQueryString & "'>English Proficiency</A> "
	'END IF
	'WKCEGrouplinks = WKCEGrouplinks & "</TD></TR></TABLE>"
'End Function
'***************************************************************************
'ht jan 6/03 begin test of WKCEGrouplinks
Function WKCEGroupLinks(zQueryString)
	WKCEGrouplinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD ALIGN='LEFT' WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "Gender" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
	END IF
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "Race/Ethnicity" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
	END IF
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "Disability" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
	END IF
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "EconomicStatus" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Economic Status</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=EconomicStatus&" & zQueryString & "'>Economic Status</A> "
	END IF
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "EnglishProficiency" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>English Proficiency</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=EnglishProficiency&" & zQueryString & "'>English Proficiency</A> "
	END IF
	'ht feb7/03
	'if trim(zGraphinclude) <> "RETENTSCH" then
	WKCEGrouplinks = WKCEGrouplinks & " &#149; "
	If zGroup = "Migrant" THEN
		WKCEGrouplinks = WKCEGrouplinks & "<font color='" & zActiveLinkColor & "'>Migrant Status</FONT> "
	ELSE
		WKCEGrouplinks = WKCEGrouplinks & "<A HREF='graphshell.asp?Group=Migrant&" & zQueryString & "'>Migrant Status</A> "
	END IF
	'end if
	WKCEGrouplinks = WKCEGrouplinks & "</TD></TR></TABLE>"
End Function
''end test
'***************************************************************************
Function GetFullkeyList()
' 11/2001 code
	GetFullkeyList = "'" & strFullKeySQL & "'"
'	GetFullkeyList = "'" & Session("Fullkey") & "'"
	If not isempty(trim(Session("sSchool4ID"))) and Session("sSchool4ID") <> "zz" THEN
		GetFullkeyList = GetFullkeyList & ",'" & Session("sSchool4ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool3ID"))) and Session("sSchool3ID") <> "zz"  THEN
		GetFullkeyList = GetFullkeyList & ",'" & Session("sSchool3ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool2ID"))) and Session("sSchool2ID") <> "zz" THEN
		GetFullkeyList = GetFullkeyList & ",'" & Session("sSchool2ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool1ID"))) and Session("sSchool1ID") <> "zz"  THEN
		GetFullkeyList = GetFullkeyList & ",'" & Session("sSchool1ID") & "'"
	END IF
End Function
'***************************************************************************
Function WKCEEligibleOnlyLinks(zQueryString)
	'ht:Jan 28/02
	If strOrgLevel = "SC" or strOrgLevel = "DI" THEN
		zFay = " FAY "
		zFayDef = "<BR><FONT Size=-2>FAY = full (prior) academic year</FONT></TD></TR></TABLE>"
	else
		zFay = ""
		zFayDef = "<BR></TD></TR></TABLE>"
	end if
	'ht: end 
	WKCEEligibleOnlyLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>&nbsp;</TD><TD class='text'>"
	IF zEligibleOnly <> "NO" THEN
		WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "[<A HREF='graphshell.asp?EligibleOnly=NO&" & zQueryString & "'>All Enrolled " & zFay & "</A> | "
	Else 
		WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "[<FONT COLOR='" & zActiveLinkColor & "'>All Enrolled " & zFay & "</FONT> | " 
	End if
	IF zEligibleOnly <> "YES" THEN
		WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "<A HREF='graphshell.asp?EligibleOnly=YES&" & zQueryString & "'>Eligibles Enrolled " & zFay & "</A>"
	ELSE
		WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "<FONT COLOR='" & zActiveLinkColor & "'>Eligibles Enrolled " & zFay & "</FONT> "
	END IF
'	If strOrgLevel = "DI" THEN
'		If zGroup = "AllStudentsFAY" or zGraphInclude = "SCATTERPLOT" THEN
'			' only show this option with the all students graphs...
'			If zEligibleOnly <> "SS" THEN
'				WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "| <A HREF='graphshell.asp?EligibleOnly=SS&" & zQueryString & "'>Enrolled Single School FAY</A>]"
'			Else
'				WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "| <font COLOR='" & zActiveLinkColor & "'>Enrolled Single School FAY</A></FONT>]"
'			END IF
'		ELSE
'			WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "]"
'		END IF
'	Else
'		WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "]"
'	END IF
	WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & "]"
	WKCEEligibleOnlyLinks = WKCEEligibleOnlyLinks & zFayDef
End Function
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function SelSchoolNameNew(zFullkey)
'ht: hot links for SC/DI
'	IF trim(zFullkey) = Session("Fullkey") THEN
	IF trim(zFullkey) = strFullKeySQL THEN
		SelSchoolNameNew = "Current " & IncludeIfMatchElse(strOrgLevel, "DI", "District", "School")
	ELSE
		If trim(zFullkey) = Session("sSchool1ID") THEN
			if trim(session("sSchool1WebUrl"))="ftp://" or trim(session("sSchool1WebUrl"))="http://" or session("sSchool1WebUrl")=" " then
				if trim(session("sCounty1WebUrl"))="ftp://" or trim(session("sCounty1WebUrl"))="http://" or session("sCounty1WebUrl")=" "then
					SelSchoolNameNew = Session("sSchool1Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew = Session("sSchool1Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sHoldSCCUrl1") & "')>" & "" &Session("sCounty1Name")& "</A>")	
				end if
			else
				if trim(session("sCounty1WebUrl"))="ftp://" or trim(session("sCounty1WebUrl"))="http://" or session("sCounty1WebUrl") = " " then
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool1WebUrl") & "') >" & Session("sSchool1Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool1WebUrl") & "') >" & Session("sSchool1Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sHoldSCCUrl1") & "') >" & "" &Session("sCounty1Name")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool2ID") THEN
			if trim(session("sSchool2WebUrl"))="ftp://" or trim(session("sSchool2WebUrl"))="http://" or session("sSchool2WebUrl")= " " then
				if trim(session("sCounty2WebUrl"))="ftp://" or trim(session("sCounty2WebUrl"))="http://" or session("sCounty2WebUrl")=" " then
					SelSchoolNameNew = Session("sSchool2Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew = Session("sSchool2Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty2WebUrl") & "') >" & "" &Session("sCounty2Name")& "</A>")	
				end if
			else
				if trim(session("sCounty2WebUrl"))="ftp://" or trim(session("sCounty2WebUrl"))="http://" or session("sCounty2WebUrl") = " " then
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool2WebUrl") & "') >" & Session("sSchool2Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty2Name"))	
				else
				SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool2WebUrl") & "') >" & Session("sSchool2Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty2WebUrl") & "') >" & "/" &Session("sCounty2Name")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool3ID") THEN
			if trim(session("sSchool3WebUrl"))="ftp://" or trim(session("sSchool3WebUrl"))="http://" or session("sSchool3WebUrl")= " " then
				if trim(session("sCounty3WebUrl"))="ftp://" or trim(session("sCounty3WebUrl"))="http://" or session("sCounty3WebUrl") = " " then
					SelSchoolNameNew = Session("sSchool3Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty3Name"))	
				else
					SelSchoolNameNew = Session("sSchool3Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty3WebUrl") & "') >" & "" &Session("sCounty3Name")& "</A>")	
				end if
			else
				if trim(session("sCounty3WebUrl"))="ftp://" or trim(session("sCounty3WebUrl"))="http://" or session("sCounty3WebUrl")= " " then
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool3WebUrl") & "') >" & Session("sSchool3Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty3Name"))	
				else
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool3WebUrl") & "') >" & Session("sSchool3Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty3WebUrl") & "')>" & "/" &Session("sCounty3Name")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool4ID") THEN
			if trim(session("sSchool4WebUrl"))="ftp://" or trim(session("sSchool4WebUrl"))="http://" or session("sSchool4WebUrl")= " " then
				if trim(session("sCounty4WebUrl"))="ftp://" or trim(session("sCounty4WebUrl"))="http://" or session("sCounty4WebUrl")= " " then
					SelSchoolNameNew = Session("sSchool4Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty4Name"))	
				else
					SelSchoolNameNew = Session("sSchool4Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty4WebUrl") & "') >" & "" &Session("sCounty4Name")& "</A>")	
				end if
			else
				if trim(session("sCounty4WebUrl"))="ftp://" or trim(session("sCounty4WebUrl"))="http://" or session("sCounty4WebUrl")=" " then
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool4WebUrl") & "') >" & Session("sSchool4Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty4Name"))	
				else
					SelSchoolNameNew = "<A HREF=javascript:popup('" & session("sSchool4WebUrl") & "') >" & Session("sSchool4Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty4WebUrl") & "') >" & "/" &Session("sCounty4Name")& "</A>")	
				end if
			end if
		END IF
	END IF
END Function
'''''''''''''''

Function SelSchoolNameNew2(zFullkey)
'ht: hot links for SC/DI
'	IF trim(zFullkey) = Session("Fullkey") THEN
	IF trim(zFullkey) = strFullKeySQL THEN
		SelSchoolNameNew2 = "Current " & IncludeIfMatchElse(strOrgLevel, "DI", "District", "School")
	ELSE
		If trim(zFullkey) = Session("sSchool1ID") THEN
			if trim(session("sSchool1WebUrl"))="ftp://" or trim(session("sSchool1WebUrl"))="http://" or session("sSchool1WebUrl")=" " then
				if trim(session("sCounty1WebUrl"))="ftp://" or trim(session("sCounty1WebUrl"))="http://" or session("sCounty1WebUrl")=" "then
					SelSchoolNameNew2 = Session("sSchool1Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew2 = Session("sSchool1Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sHoldSCCUrl1") & "')>" & "/" & Session("sCounty1Name")& "</A>")	
				end if
			else
				if trim(session("sCounty1WebUrl"))="ftp://" or trim(session("sCounty1WebUrl"))="http://" or session("sCounty1WebUrl") = " " then
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool1WebUrl") & "') >" & Session("sSchool1Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", Session("districtName"))	
				else
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool1WebUrl") & "') >" & Session("sSchool1Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sHoldSCCUrl1") & "') >" & "/" & Session("districtName")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool2ID") THEN
			if trim(session("sSchool2WebUrl"))="ftp://" or trim(session("sSchool2WebUrl"))="http://" or session("sSchool2WebUrl")= " " then
				if trim(session("sCounty2WebUrl"))="ftp://" or trim(session("sCounty2WebUrl"))="http://" or session("sCounty2WebUrl")=" " then
					SelSchoolNameNew2 = Session("sSchool2Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew2 = Session("sSchool2Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty2WebUrl") & "') >" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			else
				if trim(session("sCounty2WebUrl"))="ftp://" or trim(session("sCounty2WebUrl"))="http://" or session("sCounty2WebUrl") = " " then
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool2WebUrl") & "') >" & Session("sSchool2Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
				SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool2WebUrl") & "') >" & Session("sSchool2Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty2WebUrl") & "') >" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool3ID") THEN
			if trim(session("sSchool3WebUrl"))="ftp://" or trim(session("sSchool3WebUrl"))="http://" or session("sSchool3WebUrl")= " " then
				if trim(session("sCounty3WebUrl"))="ftp://" or trim(session("sCounty3WebUrl"))="http://" or session("sCounty3WebUrl") = " " then
					SelSchoolNameNew2 = Session("sSchool3Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty3Name"))	
				else
					SelSchoolNameNew2 = Session("sSchool3Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty3WebUrl") & "') >" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			else
				if trim(session("sCounty3WebUrl"))="ftp://" or trim(session("sCounty3WebUrl"))="http://" or session("sCounty3WebUrl")= " " then
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool3WebUrl") & "') >" & Session("sSchool3Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty3Name"))	
				else
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool3WebUrl") & "') >" & Session("sSchool3Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty3WebUrl") & "')>" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			end if
		ELSEIF trim(zFullkey) = Session("sSchool4ID") THEN
			if trim(session("sSchool4WebUrl"))="ftp://" or trim(session("sSchool4WebUrl"))="http://" or session("sSchool4WebUrl")= " " then
				if trim(session("sCounty4WebUrl"))="ftp://" or trim(session("sCounty4WebUrl"))="http://" or session("sCounty4WebUrl")= " " then
					SelSchoolNameNew2 = Session("sSchool4Name") & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew2 = Session("sSchool4Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty4WebUrl") & "') >" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			else
				if trim(session("sCounty4WebUrl"))="ftp://" or trim(session("sCounty4WebUrl"))="http://" or session("sCounty4WebUrl")=" " then
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool4WebUrl") & "') >" & Session("sSchool4Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "",Session("sCounty1Name"))	
				else
					SelSchoolNameNew2 = "<A HREF=javascript:popup('" & session("sSchool4WebUrl") & "') >" & Session("sSchool4Name") & "</A>" & IncludeIfMatchElse(strOrgLevel, "DI", "", " <A HREF=javascript:popup('" & session("sCounty4WebUrl") & "') >" & "/" &Session("sCounty1Name")& "</A>")	
				end if
			end if
		END IF
	END IF
END Function

''''''''''''''''''''''''''''''''''''''''
Function WKCECompareToLinks(zQueryString)
'ht jan 31/02 : want to get prioryears link turns black when chosen
if zCompareTo = "PRIORYEARS" then
	WKCECompareToLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>" & _ 
	"<font color='" & zActivelinkcolor & "'>Prior Years</font> "
else
	WKCECompareToLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>" & _ 
	"<A HREF='graphshell.asp?GraphFile=GWKCEPRIORYEARS&CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A>  "
end if
	
		IF zGroup = "AllStudentsFAY" THEN
			If strOrgLevel = "SC" THEN
				WKCECompareToLinks = WKCECompareToLinks & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>District/State/Nation</A> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinks = WKCECompareToLinks & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>State/Nation</A> "			
			Elseif strOrgLevel = "ST" THEN
				WKCECompareToLinks = WKCECompareToLinks & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>Nation</A> "			
			END IF
		ELSE
			If strOrgLevel = "SC" THEN
				WKCECompareToLinks = WKCECompareToLinks & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>District/State</A> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinks = WKCECompareToLinks & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>State</A> "			

				' no state option because no national data to compare to 
				
			END IF
		END IF
        ' switch out district/School level depending on orglevel, turn link off if state level
		'ht: Jan 28/02
		'If strOrgLevel = "SC" or strOrgLevel = "DI" THEN
			'If strOrgLevel = "DI" then
				'WKCECompareToLinks = WKCECompareToLinks & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & ("&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current District Data Only</A> ") & "</FONT></TD></TR></TABLE>"
			'else
				'WKCECompareToLinks = WKCECompareToLinks & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & ("&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS" & zQueryString & "'>Current School Data Only</A> ") & "</FONT></TD></TR></TABLE>"
			'end if
		'else
			'WKCECompareToLinks = WKCECompareToLinks & ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Districts</A> ") & ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&" & zQueryString & "'>Selected Schools</A> ") & ("&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data Only</A> ") & "</FONT></TD></TR></TABLE>"
		'end if
		'ht jan 31/02 :go back to before attempt to make any change for current data only
		WKCECompareToLinks = WKCECompareToLinks & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "</FONT></TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function WKCECompareToLinksNew(zQueryString)
'ht Feb. 4/02 to make compareTo links black when active
if trim(zGraphinclude)="GWKCEPRIORYEARS"  then
	WKCECompareToLinksNew = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>" & _ 
	"<font color='black'>Prior Years </font>"
else
	 if trim(zGraphinclude) = "GWKCEDISTSTATE"  then
	WKCECompareToLinksNew = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>" & _ 
	"<A HREF='graphshell.asp?GraphFile=GWKCEPRIORYEARS&CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A>  "
	else
	WKCECompareToLinksNew = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>" & _ 
	"<A HREF='graphshell.asp?GraphFile=GWKCEPRIORYEARS&CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A>  "
	end if
end if
 if trim(zGraphinclude) <> "GWKCESTATEDIST"  then
		IF zGroup = "AllStudentsFAY" THEN
			If strOrgLevel = "SC" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>District/State/Nation</A> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>State/Nation</A> "			
			Elseif strOrgLevel = "ST" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>Nation</A> "			
			END IF
		ELSE
			If strOrgLevel = "SC" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>District/State</A> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESTATEDIST&" & zQueryString & "'>State</A> "			
				' no state option because no national data to compare to 
			END IF
		END IF
else
	IF zGroup = "AllStudentsFAY" THEN
			If strOrgLevel = "SC" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>District/State/Nation</font> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>State/Nation</font> "			
			Elseif strOrgLevel = "ST" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>Nation</font> "			
			END IF
	ELSE
			If strOrgLevel = "SC" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>District/State</font> "
			Elseif strOrgLevel = "DI" THEN
				WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>State</font> "			
				' no state option because no national data to compare to 
			END IF
	END IF

end if
if  trim(zGraphinclude) = "2PROFLEVALLSUBS" then
	if strOrgLevel="SC" or strOrgLevel="DI" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <font color='black'>Current Data Only</font> " & "</FONT>"
	else
		'WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; <font color='#bcbcbc'>Selected Schools/Districts</font>", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; <font color='#bcbcbc'>Similar Schools/Districts</font>"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <font color=''>Current Data Only</font> " & "</FONT>"
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='#bcbcbc'>Selected Districts&#149; Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data </A> " & "</FONT>"
	end if
elseif trim(zGraphinclude)="GWKCESIMILARSCHOOLS" then
	if strOrgLevel="SC" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>" & " &#149; <font color='black'>Similar Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> "
	elseif strOrgLevel="DI" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>" & " &#149; <font color='black'>Similar Districts</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> "
	'ht 03/06/02
	else
	WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='#bcbcbc'>Selected Districts&#149; Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data</A> " & "</FONT>"
	end if
	'end ht
Elseif trim(zGraphinclude)="GWKCESELSCHOOLS" then
	if strOrgLevel="SC" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&CompareTo=SIMILARSCHOOLS&" & zQueryString & "'>Similar Schools</A> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> "
	elseif strOrgLevel="DI" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='black'>Selected Districts</font> &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&CompareTo=SIMILARSCHOOLS&" & zQueryString & "'>Similar Districts</A> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> "
	'ht 03/06/02
	else
	WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='#bcbcbc'>Selected Districts &#149; Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data</A> " & "</FONT>"
	end if
	'end ht
elseif trim(zGraphinclude)="GWKCEPRIORYEARS" then
	if strOrgLevel="SC" or strOrgLevel="DI" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> " & "</FONT>"
	else
		'ht 03/06/02 commented line below then put in new line
		'WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; <font color='#bcbcbc'>Selected Districts/Schools</font>", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; <font color='#bcbcbc'>Similar Schools/Districts</font>"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> " & "</FONT>"
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='#bcbcbc'>Selected Districts &#149; Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data</A> " & "</FONT>"
		'ht end 
	end if
Else
	if strOrgLevel="SC" or strOrgLevel="DI" then
		WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; Selected Schools/Districts", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; Similar Schools/Districts"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> " & "</FONT>"
	else
		'ht 03/06/02 commented line below then put in new line
		'WKCECompareToLinksNew = WKCECompareToLinksNew & IncludeIfMatchElse(strOrgLevel, "DI", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</A>"), IncludeIfMatchElse(strOrgLevel, "ST", "&#149; <font color='#bcbcbc'>Selected Districts/Schools</font>", ("&#149; <A HREF='graphshell.asp?GraphFile=GWKCESELSCHOOLS&CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</A>"))) & IncludeIfMatchElse(strOrgLevel, "ST", (" &#149; <font color='#bcbcbc'>Similar Schools/Districts</font>"), (" &#149; <A HREF='graphshell.asp?GraphFile=GWKCESIMILARSCHOOLS&" & zQueryString & "'>Similar " & IncludeIfMatchElse(strOrgLevel, "SC", "Schools", "Districts") & "</A> ")) & "&#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current Data Only</A> " & "</FONT>"
		WKCECompareToLinksNew = WKCECompareToLinksNew & "&#149; <font color='#bcbcbc'>Selected Districts &#149; Selected Schools</font> &#149; <A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Current State Data</A> " & "</FONT>"
		'end ht
	end if
end if
WKCECompareToLinksNew = WKCECompareToLinksNew & "</TD></TR></TABLE>"
End Function

''''''''''''''''''''''''''''''''''''''''
Function StaffLinks(zQueryString)
	StaffLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show Ratio of:</TD><td class='text'>"
	If zRatio = "STUDENTSTAFF" THEN
		StaffLinks = StaffLinks &  "<font color='" & zActiveLinkColor & "'>Students to Staff</font>&nbsp; &#149; &nbsp;" & _ 
		"<A HREF='graphshell.asp?GraphFile=STAFF&RATIO=STAFFSTUDENT&" & zQueryString & "'>Staff to Students</A>"
	ELSE
		StaffLinks = StaffLinks &  "<A HREF='graphshell.asp?GraphFile=STAFF&RATIO=STUDENTSTAFF&" & zQueryString & "'>Students to Staff</A>&nbsp; &#149; &nbsp;" & _ 
		"<font color='" & zActiveLinkColor & "'>Staff to Students</FONT>"
	END IF
	StaffLinks = StaffLinks & "</TD></TR></TABLE>"
End Function
'''''''''''''''''''''''''''''''
Function MoneyLinks(zQueryString)
	MoneyLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	If zRatio = "REVENUE" THEN
		MoneyLinks = MoneyLinks &  "<font color='" & zActiveLinkColor & "'>Revenue Per Member</font>&nbsp; &#149; &nbsp;" & _ 
		"<A HREF='graphshell.asp?GraphFile=MONEY&RATIO=EXPENDITURE&" & zQueryString & "'>Cost Per Member</A>"
	ELSE
		MoneyLinks = MoneyLinks &  "<A HREF='graphshell.asp?GraphFile=MONEY&RATIO=REVENUE&" & zQueryString & "'>Revenue Per Member</A>&nbsp; &#149; &nbsp;" & _ 
		"<font color='" & zActiveLinkColor & "'>Cost Per Member</FONT>"
	END IF
	MoneyLinks = MoneyLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinks(zQueryString)
	GenGroupLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinks = GenGroupLinks & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinks = GenGroupLinks & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinks = GenGroupLinks & " &#149; "
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinks = GenGroupLinks & " &#149; "
		GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinks = GenGroupLinks & " &#149; "
		GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Grade</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinks = GenGroupLinks & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinks = GenGroupLinks & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinks = GenGroupLinks & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinks = GenGroupLinks & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinks = GenGroupLinks & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
				IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
					GenGroupLinks = GenGroupLinks & " &#149; "
					GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Grade</FONT> "
				ELSE
					IF zCompareTo  = "SELSCHOOLS"  THEN
					' brb remove for now so that grade shows for current only...
					' or zCompareTo  = "CURRENTONLY"
						GenGroupLinks = GenGroupLinks & " &#149; "
						GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Grade</FONT> "
						' brb leaving the link off for selected schools option...
						' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
						'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
						' brb adding susp_exp by grade back in 
					ELSEIF zGraphInclude = "GGRADRATE" THEN
						GenGroupLinks = GenGroupLinks & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinks = GenGroupLinks & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Grade</FONT> "
						END IF
					ELSE
						GenGroupLinks = GenGroupLinks & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinks = GenGroupLinks & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinks = GenGroupLinks & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
						END IF
					END IF
				END IF
				GenGroupLinks = GenGroupLinks & " &#149; "
				IF zGraphInclude = "ACT" THEN 'this is redundant at the momment but will be necessary when Disability is activated
					GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Disability</FONT> "
				Else
					GenGroupLinks = GenGroupLinks & "<font color='#bcbcbc'>Disability</FONT> "
				End IF
			END IF
		END IF

GenGroupLinks = GenGroupLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksCS(zQueryString)
	GenGroupLinksCS = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksCS = GenGroupLinksCS & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksCS = GenGroupLinksCS & " &#149; "
	' jdj: includes test for currentonly
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zCompareTo <> "CURRENTONLY" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinksCS = GenGroupLinksCS & " &#149; "
		GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinksCS = GenGroupLinksCS & " &#149; "
		GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Grade</FONT> "
		GenGroupLinksCS = GenGroupLinksCS & " &#149; "
		GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Migrant</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinksCS = GenGroupLinksCS & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinksCS = GenGroupLinksCS & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinksCS = GenGroupLinksCS & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
				IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
					GenGroupLinksCS = GenGroupLinksCS & " &#149; "
					GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Grade</FONT> "
				ELSE
					IF zCompareTo  = "SELSCHOOLS"  THEN
					' brb remove for now so that grade shows for current only...
					' or zCompareTo  = "CURRENTONLY"
						GenGroupLinksCS = GenGroupLinksCS & " &#149; "
						GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Grade</FONT> "
						' brb leaving the link off for selected schools option...
						' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
						'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
						' brb adding susp_exp by grade back in 
					ELSEIF zGraphInclude = "GGRADRATE" THEN
						GenGroupLinksCS = GenGroupLinksCS & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Grade</FONT> "
						END IF
					ELSE
						GenGroupLinksCS = GenGroupLinksCS & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCS = GenGroupLinksCS & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
						END IF
					END IF
				END IF
				GenGroupLinksCS = GenGroupLinksCS & " &#149; "
				IF zGraphInclude = "ACT" THEN 'this is redundant at the momment but will be necessary when Disability is activated
					GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Disability</FONT> "
				Else
					GenGroupLinksCS = GenGroupLinksCS & "<font color='#bcbcbc'>Disability</FONT> "
				End IF
			END IF
			'GenGroupLinksCS = GenGroupLinksCS & " &#149; "
				'If zGroup = "Migrant" THEN
					'GenGroupLinksCS = GenGroupLinksCS & "<font color='" & zActiveLinkColor & "'>Migrant</FONT> "
				'ELSE
					'GenGroupLinksCS = GenGroupLinksCS & "<A HREF='graphshell.asp?Group=Migrant&" & zQueryString & "'>Migrant</A> "
				'END IF
		END IF
GenGroupLinksCS = GenGroupLinksCS & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenCompareToLinks(zQueryString)
	GenCompareToLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
	' brb adding if here to capture stacked graphs which have to be limited when All School Types is chosen
	' force to Current Data Only on include page and grey out options here:
	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and (zGraphInclude = "SUSPEXPINCIDENTS" and zINCIDENT = "CONS")THEN
		GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>Prior Years</FONT> &#149; "
		GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>District/State</FONT> &#149; "
		GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>Selected Districts</FONT>  "
	ELSE 
	' end brb add
		IF zCompareTo = "PRIORYEARS" THEN
			GenCompareToLinks = GenCompareToLinks & "<font color='" & zActiveLinkColor & "'>Prior Years</FONT> &#149; "
		ELSE
			GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A> &#149; "
		END IF
		IF zCompareTo = "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
			GenCompareToLinks = GenCompareToLinks & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
		ELSEIF zCompareTo <> "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
			GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
		END IF
	    ' adding Orglevel test for 11/2001
		'If zGroup = "Disability"  THEN
		'	GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>Selected Schools</FONT>"
		'elseif strOrgLevel = "ST" then
		If strOrgLevel = "ST" then
			GenCompareToLinks = GenCompareToLinks& "<font color='#bcbcbc'>Selected Districts</font> &#149; <font color='#bcbcbc'>Selected Schools</FONT>"
		ELSE
			IF zCompareTo = "SELSCHOOLS" and zGraphInclude <> "MONEY" and zGraphInclude <> "AP" THEN
				GenCompareToLinks = GenCompareToLinks & "<font color='" & zActiveLinkColor & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</FONT>"
			ELSEIF zCompareTo = "SELSCHOOLS" and (zGraphInclude = "MONEY" or zGraphInclude = "AP") THEN
				GenCompareToLinks = GenCompareToLinks & "<font color='" & zActiveLinkColor & "'>Selected Districts</FONT>"
			ELSE
				IF zGraphInclude <> "MONEY" and zGraphInclude <> "AP" and zGraphInclude <> "LEP" THEN
					'ht to delete this commemt:GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
					GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
				ELSEif zGraphInclude = "MONEY" or zGraphInclude = "AP" THEN
					'ht to delete this commemt: GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>Selected Districts</FONT>"
					GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</a>"
				Else
					'ht to delete this commemt: GenCompareToLinks = GenCompareToLinks & "<font color='#bcbcbc'>Selected Schools</FONT>"
					GenCompareToLinks = GenCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</a>"
				END IF
			END IF
		END IF
	END IF
	if strOrgLevel <> "ST" then 
		IF zCompareTo <> "CURRENTONLY" then 
			GenCompareToLinks = GenCompareToLinks & " &#149; <A HREF='graphshell.asp?CompareTo=CURRENTONLY&" & zQueryString & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </a>"
		else 
			GenCompareToLinks = GenCompareToLinks & " &#149; <font color='" & zActiveLinkColor & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
		end if
	else 
		GenCompareToLinks = GenCompareToLinks & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	end if
	GenCompareToLinks = GenCompareToLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function WKCELeaveCompareLink(zQueryString)
	WKCELeaveCompareLink = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'></TD><TD class='text'>" & _ 
		"<A HREF='graphshell.asp?GraphFile=2PROFLEVALLSUBS&" & zQueryString & "'>Back to current school data</A> " & _ 
		"</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function Grad_plan_View_By(zQueryString)
	Grad_plan_View_By = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		Grad_plan_View_By = Grad_plan_View_By & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		Grad_plan_View_By = Grad_plan_View_By & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	Grad_plan_View_By = Grad_plan_View_By & " &#149; "
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zGraphInclude <> "GGRADPLAN" THEN
 		' District View the summary options are greyed out for all these..
		Grad_plan_View_By = Grad_plan_View_By & "<font color='#bcbcbc'>Gender</FONT> "
		Grad_plan_View_By = Grad_plan_View_By & " &#149; "
		Grad_plan_View_By = Grad_plan_View_By & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			Grad_plan_View_By = Grad_plan_View_By & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			Grad_plan_View_By = Grad_plan_View_By & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		Grad_plan_View_By = Grad_plan_View_By & " &#149; "
		If zGroup = "Race/Ethnicity" THEN
			Grad_plan_View_By = Grad_plan_View_By & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
		ELSE
			Grad_plan_View_By = Grad_plan_View_By & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
		END IF
	END IF
	Grad_plan_View_By = Grad_plan_View_By & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function grad_plan_showLinks(zQueryString)
	grad_plan_showLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	IF zPlan = "All" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>All Options</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=All&" & zQueryString & "'>All Options</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "4-Yr" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>4-Yr College/University</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=4-Yr&" & zQueryString & "'>4-Yr College/University</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Voc" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Voc/Tec College</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Voc&" & zQueryString & "'>Voc/Tec College</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Emp" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Employment</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Emp&" & zQueryString & "'>Employment</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Military" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Military</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Military&" & zQueryString & "'>Military</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Job" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Job Training</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Job&" & zQueryString & "'>Job Training</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "SeekEmp" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Seeking Employment</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=SeekEmp&" & zQueryString & "'>Seeking Employment</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Other" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Other Plans</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Other&" & zQueryString & "'>Other Plans</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "Undecided" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>Undecided</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=Undecided&" & zQueryString & "'>Undecided</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & " &#149; "
	IF zPlan = "No-Resp" THEN
		grad_plan_showLinks = grad_plan_showLinks & "<FONT Color='" & zActiveLinkColor & "'>No Response</FONT>"
	ELSE
		grad_plan_showLinks = grad_plan_showLinks & "<A HREF='graphshell.asp?plan=No-Resp&" & zQueryString & "'>No Response</A>"
	END IF
	grad_plan_showLinks = grad_plan_showLinks & "</TD></TR></TABLE>"
end function
''''''''''''''''''''''''''''''''''''''''
Function WKCEProLevelsLinks(zQueryString)
	WKCEProLevelsLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	IF zLevel = "ADV" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced</FONT>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=ADV&" & zQueryString & "'>Advanced</A>"
	END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	IF zLevel = "A-P" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced + Proficient</FONT>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=A-P&" & zQueryString & "'>Advanced + Proficient</A>" 
	END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	
	'huong: put in new link Advanced + Prof + Basic
	IF zLevel = "A-P-B" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced + Proficient + Basic</FONT>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=A-P-B&" & zQueryString & "'>Advanced + Proficient + Basic</A>" 
	END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	' 2nd new link
	IF zLevel = "M-NT" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Min Perf + Pre-Req Skills/Eng + No WSAS</FONT>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=M-NT&" & zQueryString & "'>Min Perf + Pre-Req Skills/Eng + No WSAS</A>" 
	END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	'huong: end 2nd new link
	'ht:3rd link
	IF zLevel = "P-RS" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Pre-Req Skill/Eng</font>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=P-RS&" & zQueryString & "'>Pre-Req Skill/Eng</A>" 
	END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	'4th link
	IF zLevel = "No-W" THEN
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>No WSAS</font>"
	ELSE
		WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=No-W&" & zQueryString & "'>No WSAS</A>" 
	END IF
	' below commented choices still work but eliminated for Jean W.
	'WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	'IF zLevel = "B-M" THEN
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Basic + Minimal</FONT>"
	'ELSE
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=B-M&" & zQueryString & "'>Basic + Minimal</A>"
	'END IF
	'WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	
	'IF zLevel = "PRF" THEN
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Proficient</FONT>"
	'ELSE
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=PRF&" & zQueryString & "'>Proficient</A>"
	'END IF
	'WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149;<BR> "
	'IF zLevel = "BAS" THEN
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Basic</FONT>"
	'ELSE
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=BAS&" & zQueryString & "'>Basic</A>"
	'END IF
	'WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	'IF zLevel = "MIN" THEN
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Minimal</FONT>"
	'ELSE
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=MIN&" & zQueryString & "'>Minimal</A>"
	'END IF
	'WKCEProLevelsLinks = WKCEProLevelsLinks & " &#149; "
	'IF zLevel = "NT" THEN
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Not Tested WKCE</FONT>"
	'ELSE
	'	WKCEProLevelsLinks = WKCEProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=NT&" & zQueryString & "'>Not Tested WKCE</A>"
	'END IF
	WKCEProLevelsLinks = WKCEProLevelsLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function ScatterGroupLinks(zQueryString)
	ScatterGroupLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Relate To:</TD><td class='text'>" 
	If zRel = "Spending" THEN
	' replaced group with Rel
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>District Spending</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Spending&" & zQueryString & "'>District Spending</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Size" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>District Size</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Size&" & zQueryString & "'>District Size</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "EconomicStatus" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Economically Disadvantaged</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=EconomicStatus&" & zQueryString & "'>% Economically Disadvantaged</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "EnglishProficiency" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Limited English Proficient</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=EnglishProficiency&" & zQueryString & "'>% Limited English Proficient</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Disability" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Students with Disabilities</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Disability&" & zQueryString & "'>% Students with Disabilities</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Native" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Am Indian</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Native&" & zQueryString & "'>% Am Indian</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Asian" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Asian</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Asian&" & zQueryString & "'>% Asian</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Black" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Black</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Black&" & zQueryString & "'>% Black</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "Hispanic" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% Hispanic</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=Hispanic&" & zQueryString & "'>% Hispanic</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & " &#149; "
	If zRel = "White" THEN
		ScatterGroupLinks = ScatterGroupLinks & "<font color='" & zActiveLinkColor & "'>% White</FONT> "
	ELSE
		ScatterGroupLinks = ScatterGroupLinks & "<A HREF='graphshell.asp?Rel=White&" & zQueryString & "'>% White</A> "
	END IF
	ScatterGroupLinks = ScatterGroupLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''
Sub CommonStackedBarGraph()
	Chart.Stacked = CHART_STACKED
	Chart.View3DDepth = 10
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 100
	Chart.Axis(AXIS_Y).Decimals = 0
	Chart.Axis(AXIS_Y).Grid = TRUE
    Chart.RgbBk = RGB(255,255,255)
	' Open the communication channel for 4 colors, ht: changed to 6 colors
	Chart.OpenDataEx COD_COLORS,7,0
	' Set the colors
	Chart.Color(0) = RGB(128,128,255)
	Chart.Color(1) = RGB(128,255,128)
	Chart.Color(2) = RGB(255,255,0)
	Chart.Color(3) = RGB(255,0,128)
	If zWKCEorWSAS = "WKCE" THEN	
		Chart.Color(4) = RGB(128,255,255)
		Chart.Color(5) = RGB(128,128,128)
		Chart.Color(6) = RGB(192,192,192)
	Else
		Chart.Color(4) = RGB(128,128,128)
		Chart.Color(5) = RGB(192,192,192)
	END IF
	' Close channel
	Chart.CloseData COD_COLORS
   	Chart.Chart3D = False
	Chart.Axis(AXIS_Y).Title = ""
	Chart.SerLegBox = TRUE
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	'Chart.SerLegBoxObj.BorderStyle = BBD_NONE
	Chart.SerLeg(0) = "Advanced"
  	Chart.SerLeg(1) = "Proficient"
	Chart.SerLeg(2) = "Basic"
	Chart.SerLeg(3) = "Minimal"
	If zWKCEorWSAS = "WKCE" THEN
		Chart.SerLeg(4) = "Pre-Req Eng"
		Chart.SerLeg(5) = "Pre-Req Skill"
		Chart.SerLeg(6) = "No WSAS"
	Else
		Chart.SerLeg(4) = "Pre-Req Skill"
		Chart.SerLeg(5) = "No WSAS"
	END IF
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
End Sub
''''''''''''''''''''''''''''''''''''''''
Function Subjectname(zSubjectID)
	Select Case zSubjectID
	Case "1RE"
		subjectname = "- READING"
	Case "2LA"
		subjectname = "- LANGUAGE ARTS"
	Case "3MA"
		subjectname = "- MATHEMATICS"
	Case "4SC"
		subjectname = "- SCIENCE"
	Case "5SS"
		subjectname = "- SOCIAL STUDIES"
	End Select
End Function
''''''''''''''''''''''''''''''''''''''''
Sub GetGrades()
	Session("LowGrade") = 0
	Session("HighGrade") = 0
	'SQL = "Select * from enrollment where Fullkey = '" & Session("Fullkey") & "' and grade in (12,16,20,24,28,32,36,40,44,48,52,56,60,64) and year = '" & Application("EnrollYear") & "' and race = '9' and sex = '9' order by grade;"
	' jdj: must substitute X or recordset comes back empty
	SQL = "Select * from enrollment where Fullkey = '" & replace(Session("Fullkey"),"Z","X") & "' and grade in (12,16,20,24,28,32,36,40,44,48,52,56,60,64) and year = '" & Application("EnrollYear") & "' and race = '9' and sex = '9' order by grade;"
	Set GradeRS = Server.CreateObject("ADODB.Recordset")
	GradeRS.Open SQL, Conn, ADOpenKeyset, ADLockReadOnly
	If not GradeRS.eof then
		Do while not GradeRS.EOF
			If cDBL(GradeRS("Enrollment")) > 0 THEN
				Session("LowGrade") = GradeRS("Grade")
				exit do
			END IF
			GradeRS.movenext
		Loop
		GradeRS.movelast
		Do until GradeRS.BOF
			If cDBL(GradeRS("Enrollment")) > 0 THEN
				Session("HighGrade") = GradeRS("Grade")
				exit do
			End If
			GradeRS.moveprevious
		Loop
		GradeRS.Movefirst
		Session("HasK") = CheckforGrade("16", GradeRS)
		Session("HasG1") = CheckforGrade("20", GradeRS)
		Session("HasG2") = CheckforGrade("24", GradeRS)
		Session("HasG3") = CheckforGrade("28", GradeRS)
		Session("HasG4") = CheckforGrade("32", GradeRS)
		Session("HasG5") = CheckforGrade("36", GradeRS)
		Session("HasG6") = CheckforGrade("40", GradeRS)
		Session("HasG7") = CheckforGrade("44", GradeRS)
		Session("HasG8") = CheckforGrade("48", GradeRS)
		Session("HasG9") = CheckforGrade("52", GradeRS)
		Session("HasG10") = CheckforGrade("56", GradeRS)
		Session("HasG11") = CheckforGrade("60", GradeRS)
		Session("HasG12") = CheckforGrade("64", GradeRS)
	ELSE
	' eof
		Session("HasK") = "F"
		Session("HasG1") = "F"
		Session("HasG2") = "F"
		Session("HasG3") = "F"
		Session("HasG4") = "F"
		Session("HasG5") = "F"
		Session("HasG6") = "F"
		Session("HasG7") = "F"
		Session("HasG8") = "F"
		Session("HasG9") = "F"
		Session("HasG10") = "F"
		Session("HasG11") = "F"
		Session("HasG12") = "F"
	END IF
	GradeRS.close
	Set GradeRS = nothing
	' brb filling lag year grade session variables as well
	Session("LowGradeLag") = 0
	Session("HighGradeLag") = 0
	
	'SQL = "Select * from enrollment where Fullkey = '" & Session("Fullkey") & "' and grade in (12,16,20,24,28,32,36,40,44,48,52,56,60,64) and year = '" & (cINT(Application("WKCEYear"))-1) & "' and race = '9' and sex = '9' order by grade;"
	' jdj: must substitute X or recordset comes back empty
	SQL = "Select * from enrollment where Fullkey = '" & replace(Session("Fullkey"),"Z","X")  & "' and grade in (12,16,20,24,28,32,36,40,44,48,52,56,60,64) and year = '" & (cINT(Application("WKCEYear"))-1) & "' and race = '9' and sex = '9' order by grade;"
	Set GradeRS = Server.CreateObject("ADODB.Recordset")
	GradeRS.Open SQL, Conn, ADOpenKeyset, ADLockReadOnly
	If not GradeRS.eof then
		Do while not GradeRS.EOF
			If cDBL(GradeRS("Enrollment")) > 0 THEN
				Session("LowGradelag") = GradeRS("Grade")
				exit do
			END IF
			GradeRS.movenext
		Loop
		GradeRS.movelast
		Do until GradeRS.BOF
			If cDBL(GradeRS("Enrollment")) > 0 THEN
				Session("HighGradelag") = GradeRS("Grade")
				exit do
			End If
			GradeRS.moveprevious
		Loop
		GradeRS.Movefirst
		Session("HasKlag") = CheckforGrade("16", GradeRS)
		Session("HasG1lag") = CheckforGrade("20", GradeRS)
		Session("HasG2lag") = CheckforGrade("24", GradeRS)
		Session("HasG3lag") = CheckforGrade("28", GradeRS)
		Session("HasG4lag") = CheckforGrade("32", GradeRS)
		Session("HasG5lag") = CheckforGrade("36", GradeRS)
		Session("HasG6lag") = CheckforGrade("40", GradeRS)
		Session("HasG7lag") = CheckforGrade("44", GradeRS)
		Session("HasG8lag") = CheckforGrade("48", GradeRS)
		Session("HasG9lag") = CheckforGrade("52", GradeRS)
		Session("HasG10lag") = CheckforGrade("56", GradeRS)
		Session("HasG11lag") = CheckforGrade("60", GradeRS)
		Session("HasG12lag") = CheckforGrade("64", GradeRS)
	ELSE
		' eof
		Session("HasKlag") = "F"
		Session("HasG1lag") = "F"
		Session("HasG2lag") = "F"
		Session("HasG3lag") = "F"
		Session("HasG4lag") = "F"
		Session("HasG5lag") = "F"
		Session("HasG6lag") = "F"
		Session("HasG7lag") = "F"
		Session("HasG8lag") = "F"
		Session("HasG9lag") = "F"
		Session("HasG10lag") = "F"
		Session("HasG11lag") = "F"
		Session("HasG12lag") = "F"
	END IF
	GradeRS.close
	Set GradeRS = nothing

	' workaround for schools with no enrollment - fixing per WINSS_checking_010506.doc #18 - view by grade is breaking
	if Session("LowGrade") = 0 then 
		Session("LowGrade") = 12 
	end if 
	if Session("HighGrade") = 0 then 
		Session("HighGrade") = 64
	end if 

END Sub
''''''''''''''''''''''''''''''''''''''''
Function GetSubjectID()
	If not isempty(Request.QueryString("SubjectID")) THEN
		GetSubjectID = Request.QueryString("SubjectID")
	ELSE
		'default to reading
		GetSubjectID = "1RE"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetGroup()
	If not isempty(Request.QueryString("Group")) THEN
		GetGroup = Request.QueryString("Group")
	ELSE
		'default to reading
		GetGroup = "AllStudentsFAY"
	END IF
END FUNCTION
'''''''''''''''''''''''''''''''''''''''
Function GetEligibleOnly()
	If not isempty(Request.QueryString("EligibleOnly")) THEN
		GetEligibleOnly = Request.QueryString("EligibleOnly")
	ELSE
		'default to reading
		GetEligibleOnly = "NO"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetIncident()
	If not isempty(Request.QueryString("INCIDENT")) THEN
		GetIncident = Request.QueryString("INCIDENT")
	ELSE
		'default to rate
		GetIncident = "RATE"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetWeapon()
	If not isempty(Request.QueryString("Weapon")) THEN
		GetWeapon = Request.QueryString("Weapon")
	ELSE
		'default to Weapon related
		GetWeapon = "YES"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetLevel()
	If not isempty(Request.QueryString("Level")) THEN
		GetLevel = Request.QueryString("Level")
	ELSE
		'default to advanced plus proficient
		GetLevel = "A-P"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetCompareTo()
	If not isempty(Request.QueryString("CompareTo")) THEN
		GetCompareTo = Request.QueryString("CompareTo")
	ELSE
		' default to prioryears
		GetCompareTo = "PRIORYEARS"
	END IF
	'fix of simschool bug -mzd -210202
	IF ( not (Request.QueryString("GraphFile") = "GWKCESELSCHOOLS") AND (GetCompareTo = "SIMILARSCHOOLS" )) THEN
		GetCompareTo = "PRIORYEARS"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetGrade()
	If not isempty(Request.QueryString("Grade")) THEN
		GetGrade = Request.QueryString("Grade")
	ELSE
		'default to First Available Grade
		If zGraphinclude <> "DROPOUTS" THEN
			GetGrade = FirstWKCEGrade()
		ELSEIf ZGraphinclude = "GGRADRATE" THEN
			GetGrade = "56"
		ELSE
			If Session("TypeCode") = "3" THEN
				GetGrade = "96"
			ELSEIF Session("TypeCode") = "4"  or Session("TypeCode") = "5" or Session("TypeCode") = "7" THEN
				GetGrade = "95"
			END IF
		END IF
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
' jdj: it seems like this function doesn't work all the time - maybe 'cos setting zOP here keeps it local - try using fncGetOP() to set local variable instead
Function GetzOP()
	If not isempty(Request.QueryString("OP")) THEN
		zOP = Request.QueryString("OP")
	ELSE
		zOP = "OFFER" ' default - other option is PARTIC
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function fncGetOP()
	If not isempty(Request.QueryString("OP")) THEN
		fncGetOP = Request.QueryString("OP")
	ELSE
		fncGetOP = "OFFER" ' default - other option is PARTIC
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetzShow()
	If not isempty(Request.QueryString("Show")) THEN
		zShow = Request.QueryString("Show")
	ELSE
		zShow = "EXTRA" ' default - other option is COMM
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetLEPShow()
	If not isempty(Request.QueryString("Show")) THEN
		GetLEPShow = Request.QueryString("Show")
	ELSE
		' default to prioryears
		GetLEPShow = "ELP"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Sub DetailWKCERow(zWhichRow, zRecordset)
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
'brb adding test for EOF in recordset to add N/A rows where they don't exist
If not zRecordSet.EOF THEN
		IF WKCESuppressed(zRecordset("zDenom")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("zDenom") & " "
		Else
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("zDenom"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 	
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTNotTested")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTNotTested") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTNotTested"))
		END IF	
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		if zEligibleOnly = "NO" THEN
			IF WKCESuppressed(zRecordSet("PctExcluded")) = "NO" THEN
				zDetailTable = zDetailTable & cDBL(zRecordSet("PctExcluded")) & "% "
			ELSE
				zDetailTable = zDetailTable &  WKCESuppressed(zRecordSet("PctExcluded"))
			END IF
		ELSE
			zDetailTable = zDetailTable & "0%"
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTMin")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTMin") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTMin"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD> " & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTBas")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTBas") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTBas"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTPrf")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTprf") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTPrf"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTAdv")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTadv") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTAdv"))
		END IF
ELSE
	' eof on recordset so add n/a row
		zDetailTable = ZDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD>" & _ 	
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = ZDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = zDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = ZDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD> " & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = ZDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = ZDetailTable & "N/A"
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDetailTable = ZDetailTable & "N/A"
END IF
		zDetailTable = ZDetailTable & "</span></TD></TR>"
END SUB
''''''''''''''''''''''''''''''''''''''''
' mike's function
Function OrgLevelText(scInc, diInc, stInc)
Select Case strOrglevel
	Case "DI"
		OrgLevelText = diInc
	Case "SC"
		OrgLevelText = scInc
	Case else
		OrgLevelText = stInc
End Select		
End Function
Function CheckforGrade(zWhich, zRS)
	zRS.Movefirst
	CheckForGrade = "F"
	Do while not zRS.eof
		If cINT(zRS("Grade")) = cINT(zWhich) THEN
			If cDBL(zRS("Enrollment")) > 0 THEN
				CheckforGrade = "T"
				exit do
			END IF
		End IF
		zRS.Movenext
	Loop
End Function
''''''''''''''''''''''''''''''''''''''''
Sub ChartSubjectLabels()
		Chart.Axis(AXIS_X).Label(0) = "Read."
		Chart.Axis(AXIS_X).Label(1) = "Lang."
		Chart.Axis(AXIS_X).Label(2) = "Math."
		Chart.Axis(AXIS_X).Label(3) = "Science"
		Chart.Axis(AXIS_X).Label(4) = "Soc. Stud."
End Sub
Sub ChartGenderLabels()
		Chart.Axis(AXIS_X).Label(0) = "Female"
		Chart.Axis(AXIS_X).Label(1) = "Male"
		Chart.Axis(AXIS_X).Label(2) = "Missing"
End Sub
Sub ChartDisabilityLabels()
		Chart.Axis(AXIS_X).Label(0) = "Disabled"
		Chart.Axis(AXIS_X).Label(1) = "Not Disabled"
		Chart.Axis(AXIS_X).Label(2) = "Missing"
End Sub
Sub ChartEconomicStatusLabels()
		Chart.Axis(AXIS_X).Label(0) = "Economically Disadvantaged"
		Chart.Axis(AXIS_X).Label(1) = "Not Economically Disadvantaged"
		Chart.Axis(AXIS_X).Label(2) = "Missing"
End Sub
Sub ChartELPLabels()
		Chart.Axis(AXIS_X).Label(0) = "Not English Proficient"
		Chart.Axis(AXIS_X).Label(1) = "English Proficient"
		Chart.Axis(AXIS_X).Label(2) = "Missing"
End Sub
Sub ChartDisabilityLabels2()
		Chart.Axis(AXIS_X).Label(0) = "Students With Disabilities"
		Chart.Axis(AXIS_X).Label(1) = "Students Without Disabilities"
		Chart.Axis(AXIS_X).Label(2) = "Missing"
End Sub
Sub ChartSPREthnicLabels()
		Chart.Axis(AXIS_X).Font.Size = 8
		Chart.Axis(AXIS_X).LabelAngle = 50
		Chart.Axis(AXIS_X).Label(0) = "Am. Ind."
		Chart.Axis(AXIS_X).Label(1) = "Asian"
		Chart.Axis(AXIS_X).Label(2) = "Black"
		Chart.Axis(AXIS_X).Label(3) = "Hisp."
		Chart.Axis(AXIS_X).Label(4) = "White"
		If zCompareTo <> "DISTSTATE" THEN
			Chart.Axis(AXIS_X).Label(5) = "Combined"
		END IF
End Sub
Sub ChartEthnicLabels()
		Chart.Axis(AXIS_X).Font.Size = 8
		'Chart.Axis(AXIS_X).LabelAngle = 50
		Chart.Axis(AXIS_X).Label(0) = "Am. Ind."
		Chart.Axis(AXIS_X).Label(1) = "Asian"
		Chart.Axis(AXIS_X).Label(2) = "Black"
		Chart.Axis(AXIS_X).Label(3) = "Hisp."
		Chart.Axis(AXIS_X).Label(4) = "White"
		Chart.Axis(AXIS_X).Label(5) = "Missing"
		Chart.Axis(AXIS_X).Label(6) = "Combined"
End Sub
Sub ChartEthnicLegend()
	    chart.Legend(0) = " American Indian"
      	chart.Legend(1) = " Asian"
		chart.Legend(2) = " Black"
		chart.Legend(3) = " Hispanic"
		chart.Legend(4) = " White"
End Sub
Sub ChartDisabilityLabels()
		Chart.Axis(AXIS_X).Label(0) = "Students with Disabilities"
		Chart.Axis(AXIS_X).Label(1) = "Students w/o Disabilities"
End Sub
Sub ChartEconomicLabels()
		Chart.Axis(AXIS_X).Label(0) = "Economically Disadv."
		Chart.Axis(AXIS_X).Label(1) = "Not Economically Disadv."
End Sub
Sub ChartLEPLabels()
		Chart.Axis(AXIS_X).Label(0) = "Limited English Proficient"
		Chart.Axis(AXIS_X).Label(1) = "English Proficient"
End Sub
Sub ChartMigrantLabels()
		Chart.Axis(AXIS_X).Label(0) = "Migrant"
		Chart.Axis(AXIS_X).Label(1) = "Non-Migrant"
End Sub
Sub ChartEligibleYAxis()
	If zEligibleOnly = "YES" THEN
		Chart.Axis(AXIS_Y).Title = "Percent of Eligible Students Only"
	ELSE
		Chart.Axis(AXIS_Y).Title = "Percent of Students"
	END IF
End Sub
Sub ChartEligibleYAxis_ByLevel()
	' jdj: adding line break to long appends if label too long
	if len(LevelName(zLevel)) > 30 then 
		zNewLine = chr(13) & chr(10) 
	else 
		zNewLine = ""
	end if
	If zEligibleOnly = "YES" THEN
'		Chart.Axis(AXIS_Y).Title = "% " & LevelName(zLevel) & " of Eligible Students Only FAY"
		Chart.Axis(AXIS_Y).Title = "% " & LevelName(zLevel) & zNewLine & " of Eligible Students Only FAY"
	ElseIf zEligibleOnly = "SS" THEN
		Chart.Axis(AXIS_Y).Title = "% " & LevelName(zLevel) & zNewLine & " of Single School FAY"
	ELSE
		Chart.Axis(AXIS_Y).Title = "% " & LevelName(zLevel) & " FAY"
	END IF
End Sub

Sub ChartBlankLabels()
	for x = 1 to zPoints
		Chart.Axis(AXIS_X).Label(zPoints) = ""
	Next
End Sub
Sub SchoolDistStateLabels()
		Chart.Axis(AXIS_X).Label(0) = "Current School"
		Chart.Axis(AXIS_X).Label(1) = "District"
		Chart.Axis(AXIS_X).Label(2) = "State"
End Sub
'''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub CommonBarGraph()
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 100
	Chart.Axis(AXIS_Y).Decimals = 0
	Chart.Axis(AXIS_Y).Grid = TRUE
    Chart.RgbBk = RGB(255,255,255)
   	Chart.Chart3D = False

	Chart.Axis(AXIS_Y).Title = ""
	Chart.SerLegBox = TRUE
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
End Sub
''''''''''''''''''''''''''''''''''''''''
Function Levelname(zLevel)
	Select Case zLevel
	Case "ADV"
		Levelname = "Advanced"
	Case "PRF"
		Levelname = "Proficient"
	Case "BAS"
		Levelname = "Basic"
	Case "MIN"
		Levelname = "Minimal Performance"
	Case "A-P"
		Levelname = "Advanced + Proficient"
	Case "A-P-B"
		Levelname = "Advanced + Proficient + Basic"
	case "B-M-NT"
		If zWKCEorWSAS <> "WKCE" THEN
			Levelname = "Basic + Min Perf + Pre-Req Skills + No WSAS"
		ELSE
			Levelname = "Basic + Min Perf + Pre-Req Skills/Eng + No WSAS"
		END IF
	case "M-NT"
		Levelname = "Min Perf + Pre-Req Skills/Eng + No WSAS"
	case "M-NT-wrct"
		Levelname = "Min Perf + Not Tested on WRCT"
	case "P-RS"
		Levelname = "Pre-Req Skill"
	case "P-RE"
		Levelname = "Pre-Req Eng"
	case "No-W"
		LevelName = "No WSAS"
	Case "B-M"
		Levelname = "Basic + Minimal"
	Case "NT"
		Levelname = "Not Tested WKCE"
	Case "NT-wrct"
		Levelname = "Not Tested on WRCT"
	End Select
End Function
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Sub DetailWKCERowPerfVar(zWhichRow, zRecordset)
	' starts a new row in detail table, and a new cell; zWhichRow gives year
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		' start the second cell in the row for number of students; 
		' if the number of students isn't suppressed, put it in
		IF WKCESuppressed(zRecordset("zDenom")) = "NO" THEN
			' special suppression for Jean: 1998(aka Oct. 1997) eligibles
			' show 0 when they're really N/A
			IF cStr(RS("Year")) = "1998" and zEligibleOnly = "YES" THEN
				zDetailTable = zDetailTable & "N/A "
			ELSE
				zDetailTable = ZDetailTable & FormatNumber(zRecordset("zDenom"),0) & " "
			END IF
			' otherwise put in the suppressed symbol
		Else
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("zDenom"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>"  
		if zLevel="No-W" then 
				IF zEligibleOnly = "NO" THEN
					zDetailTable = ZDetailTable & _
					"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
					IF WKCESuppressed(zRecordset("Excused-By-Parent")) = "NO" THEN
						' start the next cell in the row for  Excused By Parent
						IF cStr(RS("Year")) = "1998" and zEligibleOnly = "YES" THEN
							zDetailTable = zDetailTable & "N/A "
						ELSE
							zDetailTable = ZDetailTable & FormatNumber(zRecordset("Excused-By-Parent"),1) & "%"
						END IF
					' otherwise put in the suppressed symbol
					Else
						zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("Excused-By-Parent"))
					END IF
					' start the third cell in the row for Eligible-But-Not-Tested
					zDetailTable = ZDetailTable & "</span></TD>" & _ 
					"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
					IF WKCESuppressed(zRecordset("Eligible-But-Not-Tested")) = "NO" THEN
						' start the next cell in the row for  Eligible-But-Not-Tested
						IF cStr(RS("Year")) = "1998" and zEligibleOnly = "YES" THEN
							zDetailTable = zDetailTable & "N/A "
						ELSE
							zDetailTable = ZDetailTable & FormatNumber(zRecordset("Eligible-But-Not-Tested"),1) & "%"
						END IF
					' otherwise put in the suppressed symbol
					Else
						zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("Eligible-But-Not-Tested"))
					END IF
				END IF
		end if
		if zLevel="P-RE" then 
			' pre-req Eng has extra columns
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Eng Minimal") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Eng Basic") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Eng Proficient") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Eng Advanced")
		end if
		if zLevel="P-RS" then 
			' pre-req SKILL has extra columns
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Skill Level 1") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Skill Level 2") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Skill Level 3") & "</span></TD>"
			zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRecordset("Percent Pre-Req Skill Level 4")
		end if

		' start the fourth cell in the row for PerfVar
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		' check suppress-ability for these
		If zLEVEL = "A-P" or zLevel = "B-M" or zLevel = "M-NT"  or zLevel = "No-W" THEN
			zEvaluate = WKCESuppressedAdded(zRecordset("Perfvar"))
		ELSEIF zLEVEL = "A-P-B"  THEN
			zEvaluate = WKCESuppressedAdded3(zRecordset("Perfvar"))
		ELSE
			zEvaluate = WKCESuppressed(zRecordset("Perfvar"))
			
		END IF
		' if it doesn't need to be suppressed, put it in
		If zEvaluate = "NO" THEN
			If zLevel = "NT" and zEligibleOnly = "NO" and cINT(RS("year")) >= 2000 THEN
				IF WKCESuppressed(RS("PCTExcluded")) = "NO" THEN
					zDetailTable = zDetailTable & cSTR(cDBL(zRecordset("Perfvar")) + cDBL(zRecordset("PCTExcluded"))) & "%"
				ELSE
					zDisplayValue = cSTR(zRecordset("Perfvar"))
					If cINT(zDisplayValue) > 100 THEN
						zDisplayValue = "100"
					END IF
					zDetailTable = zDetailTable & zDisplayValue & "%"
				END IF
			ELSE
				' special suppression for Jean: 1998(aka Oct. 1997) eligibles
				' show 0 when they're really N/A
				IF cStr(RS("Year")) = "1998" and zEligibleOnly = "YES" THEN
					zDetailTable = zDetailTable & "N/A "
				ELSE
					zDisplayValue = cSTR(zRecordset("Perfvar"))
					If cINT(zDisplayValue) > 100 THEN
						zDisplayValue = "100"
					END IF
					zDetailTable = zDetailTable & zDisplayValue & "%"
				END IF
			END IF
		Else
			zDetailTable = zDetailTable & zEvaluate
		END IF
		zDetailTable = ZDetailTable & "</span></TD></TR>" 
END SUB
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
'test oct3/02 ht
Sub DetailWRCTRowPerfVar(zWhichRow, zRecordset)
	' starts a new row in detail table, and a new cell; zWhichRow gives year
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		' start the second cell in the row for number of students; 
		if isnumeric(zRecordset("zDenom")) then 
		zDetailTable = ZDetailTable & FormatNumber(zRecordset("zDenom"),0)
		else
		zDetailTable = ZDetailTable & zRecordset("zDenom")
		end if
		' start the fourth cell in the row for PerfVar
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		zDisplayValue = cSTR(zRecordset("Perfvar"))
		if isnumeric(zDisplayValue) then
			If cINT(zDisplayValue) > 100 THEN
				zDisplayValue = "100"
			END IF
			zDetailTable = zDetailTable & zDisplayValue & "%"
		else
			zDetailTable = zDetailTable & zDisplayValue
		end if
		
		zDetailTable = ZDetailTable & "</span></TD></TR>" 
END SUB

''''''''''''''''
Sub ChartColorSeries(zPoints)
Chart.OpenDataEx COD_COLORS,zPoints,0
' Set the colors
Select Case cSTR(zPoints)
Case "1"
	Chart.Color(0) = RGB(0,128,256)
Case "2"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
Case "3"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
Case "4"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
Case "5"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
Case "6"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
Case "7"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
Case "8"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
Case "9"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
	Chart.Color(8) = RGB(128,256,0)
Case "10"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
	Chart.Color(8) = RGB(128,256,0)
	Chart.Color(9) = RGB(128,256,233)
Case "11"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
	Chart.Color(8) = RGB(128,256,0)
	Chart.Color(9) = RGB(128,256,233)
'	Chart.Color(10) = RGB(128,256,256)
	Chart.Color(10) = RGB(233,256,128)
Case "12"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
	Chart.Color(8) = RGB(128,256,0)
	Chart.Color(9) = RGB(128,256,233)
	Chart.Color(10) = RGB(233,256,128)
	Chart.Color(11) = RGB(128,128,0)
Case "13"
	Chart.Color(0) = RGB(0,128,256)
	Chart.Color(1) = RGB(233,128,233)
	Chart.Color(2) = RGB(223,36,73)
	Chart.Color(3) = RGB(128,256,128)
	Chart.Color(4) = RGB(256,128,0)
	Chart.Color(5) = RGB(0,256,128)
	Chart.Color(6) = RGB(128,256,256)
	Chart.Color(7) = RGB(256,0,128)
	Chart.Color(8) = RGB(128,256,0)
	Chart.Color(9) = RGB(128,256,233)
	Chart.Color(10) = RGB(233,256,128)
	Chart.Color(11) = RGB(128,128,0)
	Chart.Color(12) = RGB(0,128,0)
Case "21"
	Chart.Color(0) = RGB(233,128,233)
	Chart.Color(1) = RGB(223,36,73)
Case "22"
	Chart.Color(0) = RGB(223,36,73)
End Select
' Close channel
Chart.CloseData COD_COLORS
End Sub
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function SelectListFields()
IF zEligibleOnly = "NO" or zEligibleOnly = "SS" THEN
	Select Case zLevel
	Case "ADV"
		 SelectListFields = " Enrolled as zDenom, PCTAdv "
	CASE "PRF"
		 SelectListFields = " Enrolled as zDenom, PCTPRF "
	CASE "BAS"
		 SelectListFields = " Enrolled as zDenom, PCTBas "
	CASE "MIN"
		 SelectListFields = " Enrolled as zDenom, PCTMin "
	CASE "A-P"
		 SelectListFields = " Enrolled as zDenom, (PCTAdv + PCTPrf) "
	CASE "A-P-B"
		SelectListFields = " Enrolled as zDenom, (PCTAdv + PCTPrf + PCTBAS) "
	'ht:
	CASE "P-RS"
		SelectListFields = " Enrolled as zDenom, (PCTExcluded) "
	CASE "No-W"
		'brb need to fix not working for suppressed Excused or Excluded numbers...
		if zYearCompare <= 1999 then
			SelectListFields = " Enrolled as zDenom, 'Excused-By-Parent' = CASE WHEN Excused < 0 THEN -10 WHEN Enrolled = 0 THEN 0 ELSE ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) END, PCTNotTested as 'Eligible-But-Not-Tested',  CASE WHEN PCTNotTested < 0 THEN -20 WHEN Excused < 0 THEN PCTNotTested WHEN Enrolled = 0 THEN 0 ELSE cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) END "
		else
			SelectListFields = " Enrolled as zDenom, 'Excused-By-Parent' = CASE WHEN Excused < 0 THEN -10 WHEN Enrolled = 0 THEN 0 ELSE ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) END, PCTNotTested as 'Eligible-But-Not-Tested', (PCTNotTested)"
		end if
	CASE "M-NT"
		' brb correcting - this was not including the NO WSAS and Pre-Req 
		' SelectListFields = " Enrolled as zDenom, (PCTMin + PCTNotTested) "
		if zYearCompare <= 1999 then
			SelectListFields = " Enrolled as zDenom, CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN Excused < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded + cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1))) END "
		else
			SelectListFields = " Enrolled as zDenom, CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded+ PCTNotTested) END"
		end if
	CASE "B-M"
		 SelectListFields = " Enrolled as zDenom, (PCTBas + PCTMin) "
	CASE "NT"
		 SelectListFields = " Enrolled as zDenom, PCTNotTested "
	END SELECT
ELSE
	Select Case zLevel
	Case "ADV"
		 SelectListFields = " Eligible as zDenom, PCTAdv_E "
	CASE "PRF"
		 SelectListFields = " Eligible as zDenom, PCTPRF_E "
	CASE "BAS"
		 SelectListFields = " Eligible as zDenom, PCTBas_E "
	CASE "MIN"
		 SelectListFields = " Eligible as zDenom, PCTMin_E "
	CASE "A-P"
		 SelectListFields = " Eligible as zDenom, (PCTAdv_E + PCTPrf_E) "
	CASE "B-M"
		 SelectListFields = " Eligible as zDenom, (PCTBas_E + PCTMin_E) "
	CASE "NT"
		 SelectListFields = " Eligible as zDenom, PCTNotTested_E "
	CASE "A-P-B"
		SelectListFields = " Eligible as zDenom, (PCTAdv_E + PCTPrf_E + PCTBAS_E) "
	CASE "P-RS"
		SelectListFields = " Enrolled as zDenom, (0) "
	CASE "No-W"
		SelectListFields = " Enrolled as zDenom,(PCTNotTested_E) "	
		' ht: have 2 cols of same value because Eligible-But-Not-Tested ( same value as PCTNotTested_E) is used only in No-W and   PCTNotTested_E is for other link
		'SelectListFields = " Enrolled as zDenom, ((Excused/Included)*100) as 'Excused-By-Parent', PCTNotTested_E as 'Eligible-But-Not-Tested', (PCTNotTested_E) "	
	CASE "M-NT"
		SelectListFields = " Eligible as zDenom, (PCTMin_E + PCTNotTested_E) "
	END SELECT
END IF
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function SelectListFields2(zStartPos,zGroup2,zDem2,zDisplay2)
'ht dec 16/02 for scatter plot Table 
ColumnFormatArray(zStartPos) = "NUM"
ColumnFormatArray((zStartPos+1)) = "DEC1"
zSelEnroll=" '# Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END "
zSelEligible=" ' # Eligible'= CASE Eligible WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Eligible as char(6)) END "
IF zEligibleOnly = "NO" or zEligibleOnly = "SS" THEN
	Select Case zLevel
	Case "ADV"
		If zGroup2 = "None" THEN
			SelectListFields2 =  zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Advanced' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & "'% Advanced' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv as char(6)) END "
		end if
	CASE "PRF"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "','% Proficient' = CASE PCTPRF WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF as char(6)) END "
		else
			SelectListFields2 = zSelEnroll &"," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Proficient' = CASE PCTPRF WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF as char(6)) END "
		end if
	CASE "BAS"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Basic' = CASE PCTBAS WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBAS as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Basic' = CASE PCTBAS WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBAS as char(6)) END "
		end if
	CASE "MIN"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Minimum' = CASE PCTMIN WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMIN as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', " & zDem2 & " as '" & zDisplay2 & "', " & " '% Minimum' = CASE PCTMIN WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMIN as char(6)) END "
		end if
	CASE "A-P"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "',  '% Advanced+Proficient' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Advanced+Proficient' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf as char(6)) END "
		end if
	CASE "A-P-B"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Advanced+Proficient+Basic' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf + PCTBAS as char(6)) END " 
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Advanced+Proficient+Basic' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf + PCTBAS as char(6)) END " 
		end if
	'ht:
	CASE "P-RS"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Excluded' = CASE PCTExcluded WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTExcluded) as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "' , '% Excluded' = CASE PCTExcluded WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTExcluded) as char(6)) END "
		end if
	CASE "No-W" ''''''''''''''''''''''''''''''''''''''worked
		if zYearCompare <= 1999 then
			'If zGroup2 = "None" THEN
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)  as numeric(5,1)) as char(7)) END, " & _ 
				   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					" '% No WSAS' = CASE WHEN PCTNotTested < 0 THEN 'N/A' WHEN Excused < 0 THEN cast(PCTNotTested as char(6)) WHEN Enrolled = 0 THEN '0' ELSE cast(cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) as char(7)) END "
					ColumnFormatArray((zStartPos+2)) = "DEC1"
			'else
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				'SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "' , 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)  as numeric(5,1)) as char(7)) END, " & _ 
				 '  " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					' zDem2 & " as '" & zDisplay2 & "', " & " '% No WSAS' = CASE WHEN PCTNotTested < 0 THEN 'N/A' WHEN Excused < 0 THEN cast(PCTNotTested as char(6)) WHEN Enrolled = 0 THEN '0' ELSE cast(cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) as char(7)) END "
					ColumnFormatArray((zStartPos+2)) = "DEC1"
			'end if
		else
			'If zGroup2 = "None" THEN
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "' , 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) as numeric(5,1)) as char(7)) END, " & _ 
				   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					" '% No WSAS' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
				ColumnFormatArray((zStartPos+2)) = "DEC1"
			'else
				'SelectListFields2 = zSelEnroll &"," & zDem1 & " as '" & zDisplay & "', 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) as numeric(5,1)) as char(7)) END, " & _ 
				'   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					' zDem2 & " as '" & zDisplay2 & "', " & " '% No WSAS' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
				ColumnFormatArray((zStartPos+2)) = "DEC1"
			'end if
		end if
		''''''''''''''''''''above worked
	CASE "M-NT"
		if zYearCompare <= 1999 then
			If zGroup2 = "None" THEN
			 'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 =zSelEnroll &"," & zDem1 & " as '" & zDisplay & "'," & zDem1 & " as '" & zDisplay & ",'% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN Excused < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded + cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1))) END "
			else
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN Excused < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded + cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1))) END "
			end if
		else
			If zGroup2 = "None" THEN
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "' , '% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded+ PCTNotTested) END"
			else
			'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
				SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded+ PCTNotTested) END"
			end if
		end if
	CASE "B-M"
		If zGroup2 = "None" THEN
		'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
			SelectListFields2 =zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% Basic + Minimum' = CASE PCTBas WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas + PCTMin as char(6)) END "
		else
		'Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Basic + Minimum' = CASE PCTBas WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas + PCTMin as char(6)) END "
		end if
	CASE "NT"
		If zGroup2 = "None" THEN
		 	SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', '% NotTested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
		else
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "', " & zDem2 & " as '" & zDisplay2 & "', " & " '% NotTested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
		end if
	END SELECT
ELSE
	Select Case zLevel
	Case "ADV"
		If zGroup2 = "None" THEN
		'Eligible'= CASE Eligible WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Eligible as char(6)) END
		 	SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Advanced' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E as char(6)) END "
		else
		 	SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Advanced' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E as char(6)) END "
		end if	
	CASE "PRF"
		If zGroup2 = "None" THEN
		 	SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Proficient' = CASE PCTPRF_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF_E as char(6)) END "
		else
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Proficient' = CASE PCTPRF_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF_E as char(6)) END "
		end if
	CASE "BAS"
		If zGroup2 = "None" THEN
			 SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Basic' = CASE PCTBas_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas_E as char(6)) END "
		else
			 SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Basic' = CASE PCTBas_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas_E as char(6)) END "
		end if
	CASE "MIN"
		If zGroup2 = "None" THEN
			 SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Minimum' = CASE PCTMin_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMin_E as char(6)) END "
		else
			 SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Minimum' = CASE PCTMin_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMin_E as char(6)) END "
		end if
	CASE "A-P"
		If zGroup2 = "None" THEN
			 SelectListFields2 = zSelEligible &"," & zDem1 & " as '" & zDisplay & "', '% Advanced + Proficient' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTAdv_E + PCTPrf_E) as char(6)) END "
		else
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Advanced + Proficient' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTAdv_E + PCTPrf_E) as char(6)) END "
		end if
	CASE "B-M"
		If zGroup2 = "None" THEN
		 	SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Basic + Min' = CASE PCTBas_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTBas_E + PCTMin_E) as char(6)) END "
		else
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Basic + Min' = CASE PCTBas_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTBas_E + PCTMin_E) as char(6)) END "
		end if
	CASE "NT"
		If zGroup2 = "None" THEN
		 	SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "',  '% NotTested' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
		else
			 SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% NotTested' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
		end if
	CASE "A-P-B"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Advanced + Proficient + Basic' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E + PCTPrf_E + PCTBas_E as char(6)) END "
		else
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Advanced + Proficient + Basic' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E + PCTPrf_E + PCTBas_E as char(6)) END "
		end if
	CASE "P-RS"
		If zGroup2 = "None" THEN
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END "
		else
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END "
		end if
	CASE "No-W"
		If zGroup2 = "None" THEN
		'Enrolled' = CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "','% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END , 'No WSAS' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
		else
		'Enrolled' = CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END
			SelectListFields2 = zSelEnroll & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END , 'No WSAS' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
		end if
	CASE "M-NT"
		If zGroup2 = "None" THEN
		'Eligible'= CASE Eligible WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Eligible as char(6)) END 
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "', '% Min + NotTested' = CASE PCTMin_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTMin_E + PCTNotTested_E) as char(6)) END "
		else
		'Eligible'= CASE Eligible WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Eligible as char(6)) END
			SelectListFields2 = zSelEligible & "," & zDem1 & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "', " & " '% Min + NotTested' = CASE PCTMin_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTMin_E + PCTNotTested_E) as char(6)) END "
		end if
	END SELECT
END IF
End Function

''''''''''''''''''
Function SelectListFields3(zStartPos,zGroup2,zDem2,zDisplay2)
'ht mar6/03 for scatter plot Table  specif. for district spending and size
ColumnFormatArray(zStartPos) = "NUM"
ColumnFormatArray((zStartPos+1)) = "DEC1"
zSelEnroll=" '# Enrolled'= CASE Enrolled WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Enrolled as char(6)) END "
zSelEligible=" '# Eligible'= CASE Eligible WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(Eligible as char(6)) END "
IF zEligibleOnly = "NO" or zEligibleOnly = "SS" THEN
	Select Case zLevel
	Case "ADV"
			zMoreSelect =   ", '% Advanced' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv as char(6)) END "
	CASE "PRF"
			zMoreSelect =  ",'% Proficient' = CASE PCTPRF WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF as char(6)) END "
	CASE "BAS"
			zMoreSelect =  ", '% Basic' = CASE PCTBAS WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBAS as char(6)) END "
	CASE "MIN"
			zMoreSelect = ", '% Minimum' = CASE PCTMIN WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMIN as char(6)) END "
	CASE "A-P"
			zMoreSelect =  ",  '% Advanced+Proficient' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf as char(6)) END "
	CASE "A-P-B"
			zMoreSelect =  ", '% Advanced+Proficient+Basic' = CASE PCTAdv WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv + PCTPrf + PCTBAS as char(6)) END " 
	CASE "P-RS"
			zMoreSelect =  ", '% Excluded' = CASE PCTExcluded WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTExcluded) as char(6)) END "
	CASE "No-W" 
		if zYearCompare <= 1999 then
			'If zGroup2 = "None" THEN
				'zMoreSelect =  ", 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)  as numeric(5,1)) as char(7)) END, " & _ 
				'   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
				'	" '% No WSAS' = CASE WHEN PCTNotTested < 0 THEN 'N/A' WHEN Excused < 0 THEN cast(PCTNotTested as char(6)) WHEN Enrolled = 0 THEN '0' ELSE cast(cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) as char(7)) END "
					'ColumnFormatArray((zStartPos+2)) = "DEC1"
			'else
			'mar27/03 conmented out by HT so that District spending, size will be at the left, not after Eligible-But-Not-Tested column
				'zMoreSelect =  " ,'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)  as numeric(5,1)) as char(7)) END, " & _ 
				  ' " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					' zDem2 & " as '" & zDisplay2 & "', " & " '% No WSAS' = CASE WHEN PCTNotTested < 0 THEN 'N/A' WHEN Excused < 0 THEN cast(PCTNotTested as char(6)) WHEN Enrolled = 0 THEN '0' ELSE cast(cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) as char(7)) END "
					
						zMoreSelect =  " ,'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)  as numeric(5,1)) as char(7)) END, " & _ 
				   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					 " '% No WSAS' = CASE WHEN PCTNotTested < 0 THEN 'N/A' WHEN Excused < 0 THEN cast(PCTNotTested as char(6)) WHEN Enrolled = 0 THEN '0' ELSE cast(cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1)) as char(7)) END "
					ColumnFormatArray((zStartPos+2)) = "DEC1"
			'end if
		else
		''mar27/03 conmented out by HT so that District spending, size will be at the left, not after Eligible-But-Not-Tested column
			'If zGroup2 = "None" THEN
				zMoreSelect =  ", 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) as numeric(5,1)) as char(7)) END, " & _ 
				   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
					" '% No WSAS' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
				ColumnFormatArray((zStartPos+2)) = "DEC1"
			'else
				'zMoreSelect =  ", 'Excused-By-Parent' = CASE WHEN Excused is null THEN 'N/A' WHEN Excused = -10 THEN '*' WHEN Excused = -20 THEN 'N/A' WHEN Excused = -30 THEN 'All' WHEN Enrolled = 0 THEN '0' ELSE cast(cast(((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100) as numeric(5,1)) as char(7)) END, " & _ 
				'   " 'Eligible-But-Not-Tested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END, " & _ 
				'	 zDem2 & " as '" & zDisplay2 & "', " & " '% No WSAS' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
				'ColumnFormatArray((zStartPos+2)) = "DEC1"
			'end if
		end if
		''''''''''''''''''''''''''''''''''''''''''''''''''''''
	CASE "M-NT"
		if zYearCompare <= 1999 then
				zMoreSelect = ",'% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN Excused < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded + cast((PCTNotTested + ((cast(Excused as numeric(18,0))/cast(Enrolled as numeric(18,0)))*100)) as numeric(18,1))) END "
		else
				zMoreSelect = " , '% Minimum + NotTested' = CASE WHEN PCTNotTested < 0 THEN -20 WHEN PCTMIN < 0 THEN -20 WHEN PCTExcluded < 0 THEN -20 WHEN Enrolled = 0 THEN 0 ELSE (PCTMin + PCTExcluded+ PCTNotTested) END"
		end if
	CASE "B-M"
			zMoreSelect = ", '% Basic + Minimum' = CASE PCTBas WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas + PCTMin as char(6)) END "
	CASE "NT"
		 	zMoreSelect =  ", '% NotTested' = CASE PCTNotTested WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested as char(6)) END "
	END SELECT
ELSE
	Select Case zLevel
	Case "ADV"
		 	zMoreSelect =  ", '% Advanced' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E as char(6)) END "
	CASE "PRF"
		 	zMoreSelect =  ", '% Proficient' = CASE PCTPRF_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTPRF_E as char(6)) END "
	CASE "BAS"
			zMoreSelect =  ", '% Basic' = CASE PCTBas_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTBas_E as char(6)) END "
	CASE "MIN"
			 zMoreSelect =  ", '% Minimum' = CASE PCTMin_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTMin_E as char(6)) END "
	CASE "A-P"
			zMoreSelect =  ", '% Advanced + Proficient' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTAdv_E + PCTPrf_E) as char(6)) END "
	CASE "B-M"
		 	zMoreSelect =  ", '% Basic + Min' = CASE PCTBas_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTBas_E + PCTMin_E) as char(6)) END "
	CASE "NT"
		 	zMoreSelect =  ",  '% NotTested' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
	CASE "A-P-B"
			zMoreSelect =  ", '% Advanced + Proficient + Basic' = CASE PCTAdv_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTAdv_E + PCTPrf_E + PCTBas_E as char(6)) END "
	CASE "P-RS"
			zMoreSelect =  ", '% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END "
	CASE "No-W"
			zMoreSelect =  ", '% Pre Reg Skills' = CASE (0) WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((0) as char(6)) END , 'No WSAS' = CASE PCTNotTested_E WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast(PCTNotTested_E as char(6)) END "
	CASE "M-NT"
			zMoreSelect =  ", '% Min + NotTested' = CASE PCTMin_E  WHEN NULL THEN 'N/A' WHEN -10 THEN '*' WHEN -20 THEN 'N/A' WHEN -30 THEN 'ALL' ELSE cast((PCTMin_E + PCTNotTested_E) as char(6)) END "
	END SELECT
END IF
'if zLevel <> "No-W" then
		if zRel="Spending" and zgroup2<>"Spending" and zgroup2<>"Size" then
				If zGroup2 = "None" THEN
				zMoreSelect =  zDem1 & " as '" & zDisplay & "' " & "," & zSelEnroll & zMoreSelect
				else
				zMoreSelect =  zDem1 & " as '" & zDisplay & "'," & zSelEnroll & ", " & zDem2 & " as '" & zDisplay2 & "' " & zMoreSelect
				end if
		elseif zRel="Size" and zgroup2<>"Spending" and zgroup2<>"Size"  then
				If zGroup2 = "None" THEN
				zMoreSelect =  zDem1 & " as '" & zDisplay & "'," & zSelEnroll & zMoreSelect
				else
				zMoreSelect =  zDem1 & " as '" & zDisplay & "'," & zSelEnroll & ", " & zDem2 & " as '" & zDisplay2 & "' " & zMoreSelect
				end if
		'elseif zGroup2="Spending" and zrel<>"Spending" and zrel<>"Size" then
				'zMoreSelect =  zDem2 & " as '" & zDisplay2 & "', " & zSelEnroll  & zMoreSelect
		'elseif zgroup2="Size" and zrel<>"Spending" and zrel<>"Size"  then
				'zMoreSelect =  zDem2 & " as '" & zDisplay2 & "' , " & zSelEnroll & zMoreSelect
		'test ht mar 27/03
		elseif  zrel<>"Spending" and zrel<>"Size" then
				if zGroup2="Spending" then
					zMoreSelect =  zDem2 & " as '" & zDisplay2 & "', " & zSelEnroll & ", " & zDem1 & " as '" & zDisplay & "'" & zMoreSelect
				elseif zgroup2="Size"  then
					zMoreSelect =  zDem2 & " as '" & zDisplay2 & "'," & zSelEnroll & ", " & zDem1 & " as '" & zDisplay & "'" & zMoreSelect
				elseif zgroup2="None"  then
					zMoreSelect = zSelEnroll & ", " & zDem1 & " as '" & zDisplay & "'" & zMoreSelect
				elseif zgroup2=zrel  then
					zMoreSelect =  zSelEnroll& "," & zDem1 & " as '" & zDisplay & "'" & zMoreSelect
				else
					zMoreSelect =  SelectListFields2(zStartPosition,zGroup2,zDem2,zDisplay2)
				end if
		elseif zRel=zgroup2 then
			if zRel="Size" or zRel="Spending" then
				zMoreSelect =  zDem1 & " as '" & zDisplay & "'," & zSelEnroll & zMoreSelect
			else  
				zMoreSelect =  zSelEnroll& "," & zDem1 & " as '" & zDisplay & "'" & zMoreSelect
			end if
		elseif zRel="Spending" and zgroup2="Size" then
				zMoreSelect =  zDem1  & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "' , " & zSelEnroll & zMoreSelect
		elseif zgroup2="Spending" and zrel="Size" then
				zMoreSelect =  zDem1  & " as '" & zDisplay & "'," & zDem2 & " as '" & zDisplay2 & "' , " & zSelEnroll & zMoreSelect
		else
				zMoreSelect =  SelectListFields2(zStartPosition,zGroup2,zDem2,zDisplay2)
		end if
		SelectListFields3 = zMoreSelect 
'else
	'if zRel=zgroup2 then 
		'if zRel="Size" or zRel="Spending" then
		'SelectListFields3 = zSelEnroll & zMoreSelect 
		'else
		'SelectListFields3 = zSelEnroll & zMoreSelect 
		'end if
	'else
	
	'end if
'end if
End Function

'''''''''''''''''''''''''''''''''''''''''''''''

Function CheckforErrors(objConn, zCurrentPage)
Dim ObjError 	'Error object
Dim zError
CheckForErrors = False
' start it out false

' Errors means the count will be greater than 0
IF ObjConn.Errors.Count > 0 THEN

	'loop through the errors
	FOR EACH objError in objConn.Errors
	
		'errors with number 0 are informational
		if objError.Number <> 0  THEN
			zError = zError & "Error Number:  " & objError.Number & chr(10) & chr(13) & _ 
							"Native Error: " & objError.NativeError & chr(10) & chr(13) & _ 
							"SQLState: " & objError.SQLState & chr(10) & chr(13) & _ 							
							"Source: " & objError.Source & chr(10) & chr(13) & _ 		
							"Description: " & objError.Description & chr(10) & chr(13) & chr(10) & chr(13)
			zError = zError & " User was viewing Fullkey: " & Session("FullKey") & " Year : " & Application("WKCEYEAR")
			zError = zError & chr(10) & chr(13) & chr(10) & chr(13)
			zError = zError & "SQL: " & SQL 
			zError = zError & chr(10) & chr(13) & chr(10) & chr(13)
			zError = zError & "Querystring: " & chr(10) & chr(13)
			' jdj: adding querystring and session and request variables to error message
			For Each Item In Request.QueryString
							zError = zError & Item & " = " & Request.QueryString(Item) & chr(10) & chr(13)
			Next 
			zError = zError & chr(10) & chr(13) & chr(10) & chr(13)
			zError = zError & "Session: " & chr(10) & chr(13)
			For Each Item In Session.Contents
							zError = zError & Item & " = " & Session.Contents(Item) & chr(10) & chr(13)
			Next 
			zError = zError & chr(10) & chr(13) & chr(10) & chr(13)
			zError = zError & "Request: " & chr(10) & chr(13)
			For Each Item In Request.ServerVariables
							zError = zError & Item & " = " & Request.ServerVariables(Item) & chr(10) & chr(13)
			Next 
			CheckForErrors = True
		END IF

	NEXT
	If CheckForErrors = True THEN
		response.write("<P>Your request has resulted in a server error and an error message is being mailed to the webmaster.  Please try your request again.  If you continue to receive this message please close your browser and try again.")
		''' now using AspEmail.dll
		Set Mail = Server.CreateObject("Persits.MailSender")
		With Mail
			.Host = "mail.sligowebworks.com"
			.From = "bill@sligowebworks.com" 
			.FromName = "Web Site Visitor Error"
			.Subject = "Wisconsin Error message"
			.AddAddress "bill@sligowebworks.com", "Sligo Staff"
			.AddAddress "jdj@sligowebworks.com", "Sligo Staff"
			.AddAddress "dan@sligowebworks.com", "Sligo Staff"
			'.AddAddress "omni@sligowebworks.com", "Sligo Staff"
			.AddReplyTo "omni@sligowebworks.com"
			.Body = "Page requested from: " & zReferer & chr(10) & chr(13) & "Current Page is: " & zCurrentPage & chr(10) & chr(13) & zError
			.Send
		End With


		'Set objSendMail = Server.CreateObject("CDONTS.NewMail")
		'zReferer = Request.ServerVariables("HTTP_Referer")
		'With objSendMail
		'	.From = "bill@sligowebworks.com"
		'	.To = "bill@sligowebworks.com"
		'	.Subject = "Wisconsin Error message!"
		'	.Body = 
		'	.Send
		'End With
		'Set ObjSendMail = nothing
		nodata = true
		Set Mail = Nothing
	END IF
END IF
End Function

''''''''''''''''''''''''''''''''''''''''
Sub DetailRow(zWhichRow, zRecordset)
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("zDenom")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("zDenom") & " "
		Else
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("zDenom"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTNotTested")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTNotTested") & "%"
		Else
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTNotTested"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTMin")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTMin") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTMin"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD> " & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTBas")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTBas") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTBas"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTPrf")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTprf") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTPrf"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("PCTAdv")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTadv") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTAdv"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD></TR>" 
END SUB

Function SelSchoolName(zFullkey)
'	IF trim(zFullkey) = Session("Fullkey") THEN
	IF trim(zFullkey) = strFullKeySQL THEN
		SelSchoolName = "Current " & IncludeIfMatchElse(strOrgLevel, "DI", "District", "School")
	ELSE
		If trim(zFullkey) = Session("sSchool1ID") THEN
			SelSchoolName = Session("sSchool1Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", Session("sCounty1Name"))
		ELSEIF trim(zFullkey) = Session("sSchool2ID") THEN
			SelSchoolName = Session("sSchool2Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", Session("sCounty1Name"))
		ELSEIF trim(zFullkey) = Session("sSchool3ID") THEN
			SelSchoolName = Session("sSchool3Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", Session("sCounty1Name"))
		ELSEIF trim(zFullkey) = Session("sSchool4ID") THEN
			SelSchoolName = Session("sSchool4Name") & IncludeIfMatchElse(strOrgLevel, "DI", "", Session("sCounty1Name"))
		END IF
	END IF 
END Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function DistStateName(zFullkey, zGraderange)
	IF trim(zFullkey) = Session("Fullkey") THEN
		if strOrgLevel="SC" then
			DistStateName = "Current School"
		elseif strOrgLevel="DI" then
			IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
				DistStateName = "District" 
			else
				DistStateName = "District" & SchoolTypeName(strTypecode, zGradeRange) 
			end if
		else
			IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
				DistStateName = "Entire State"  
			else 
				DistStateName = "Entire State"  &  SchoolTypeName(strTypecode, zGradeRange)
			end if
		end if
	ELSEIF right(zFullkey,6) = "03XXXX" THEN
		IF cINT(zGraderange) > 64 THEN
			If zGroup = "Grade" THEN
				DistStateName = Session("DistrictName")
			ELSE
				IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
					DistStateName = Session("DistrictName")
				ELSE
					DistStateName = Session("DistrictName") &  SchoolTypeName(strTypecode, zGradeRange) 
				END IF
			END IF
		ELSE
			DistStateName = Session("DistrictName")
		END IF
	ELSEIF trim(zFullkey) = "XXXXXXXXXXXX" THEN
		IF cINT(zGraderange) > 64 THEN
			If zgroup <> "Grade" THEN
				' fixing table title for ggradrate
				IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
					DistStateName = "State"
				ELSE
					DistStateName = "State"  &  SchoolTypeName(strTypecode, zGradeRange)
				END IF
			ELSE
				DistStateName = "State"
			END IF
		ELSE
			DistStateName = "State"
		END IF
	END IF
END Function
''''''''''''''''''''''''''''''''''''''''
Sub DetailWKCERowNTVar(zWhichRow, zRecordset)
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF WKCESuppressed(zRecordset("Enrolled")) = "NO" THEN
			zDetailTable = ZDetailTable & FormatNumber(zRecordset("Enrolled"),0) & " "
		Else
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("Enrolled"))
		END IF
		zDetailTable = ZDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		Select Case zNTVar
		Case "EXCLUDED"
			IF WKCESuppressed(zRecordset("Excluded")) = "NO" THEN
				zDetailTable = zDetailTable & FormatNumber(cDBL(zRecordset("PCTNotTested"))+cDBL(zRecordset("PCTExcluded")),1) & "</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & FormatNumber(((zRecordset("Excluded")/zRecordset("Enrolled")) * 100),1)
			ELSE
				' brb weird data with 'NO' in column... NotTested not suppressed by excluded is... Almond-Bancroft
				' zDetailTable = zDetailTable & WKCESuppressed(zRecordset("PCTNotTested")) & "</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & WKCESuppressed(zRecordset("Excluded"))
				zDetailTable = zDetailTable & "*</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & WKCESuppressed(zRecordset("Excluded"))
			END IF
		Case "EXCUSED"
			IF WKCESuppressed(zRecordset("Excused")) = "NO" THEN
				zDetailTable = zDetailTable & FormatNumber(cDBL(zRecordset("PCTNotTested"))+cDBL(zRecordset("PCTExcluded")),1) & "</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & FormatNumber(((zRecordset("Excused")/zRecordset("Enrolled")) * 100),1)
			ELSE
				' brb weird data with 'NO' in column... NotTested not suppressed by Excused is... Almond-Bancroft
				zDetailTable = zDetailTable & "*</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & WKCESuppressed(zRecordset("Excused"))
			END IF
		Case "ELIGNT"
			IF WKCESuppressed(zRecordset("PCTNotTested")) = "NO" and  WKCESuppressed(zRecordset("Excused")) = "NO" and WKCESuppressed(zRecordset("Excluded")) = "NO" THEN
				IF  cDBL(RS("PCTNotTested")) + cDBL(RS("PCTExcluded")) - ((RS("Excluded")/RS("Enrolled")) * 100) - ((RS("Excused")/RS("Enrolled")) * 100) < 0 THEN
					zDetailTable = zDetailTable & FormatNumber(cDBL(zRecordset("PCTNotTested"))+cDBL(zRecordset("PCTExcluded")),1) & " </TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>0.0"
				ELSE
					zDetailTable = zDetailTable & FormatNumber(cDBL(zRecordset("PCTNotTested"))+cDBL(zRecordset("PCTExcluded")),1) & " </TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & FormatNumber(cDBL(zRecordset("PCTNotTested")) + cDBL(RS("PCTExcluded")) - ((zRecordset("Excluded")/zRecordset("Enrolled")) * 100) - ((zRecordset("Excused")/zRecordset("Enrolled")) * 100),1)
				END IF
			ELSE
				' brb weird data with 'NO' in column... NotTested not suppressed by Excused is... Almond-Bancroft
				zDetailTable = zDetailTable & "*</TD><TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>*" 
			END IF
		End Select
		zDetailTable = ZDetailTable & "</span></TD></TR>" 
END SUB
''''''''''''''''''''''''''''''''''''''''
Function formatyear(zRSYear)
Select CASE cstr(zRSYear)
	Case "1998"
		FormatYear = "Oct. 1997"
	Case "2003"
		FormatYear = "Nov. 2002*"
	case else
		FormatYear = "Feb. " & zRSYear
End Select
end function
''''''''''''''''''''''''''''''''''''''''
' jdj: 20040514 - legend fix for prior years WSAS 
Function fncFormatYearWSASPriorYears(zRSYear)
Select CASE cInt(zRSYear)
	Case 1998
		fncFormatYearWSASPriorYears = "Oct. 1997"
	Case 1999,2000,2001,2002
		fncFormatYearWSASPriorYears = "Feb. " & zRSYear
	Case 2003
		fncFormatYearWSASPriorYears = "Nov. 2002*"
	case else
		fncFormatYearWSASPriorYears = "Nov. " & cStr(cInt(zRSYear) -1)
End Select
end function
''''''''''''''''''''''''''''''''''''
Function WRCTFormatYear(zRSYear)
'ht sept 30/02: used in gwrctprior.inc
			WRCTFormatYear = "March " + zRSYear
END Function

Function GetDistrictSchoolTypeGrade(zCurrSchoolType,zSubjGradeRange)
GetDistrictSchoolTypeGrade = ""
if zCurrSchoolType = "9" then
	' 9 is state or district summary type so the grade is the same as the one passed
	GetDistrictSchoolTypeGrade = zSubjGradeRange
ELSE
	Select Case cSTR(zSubjGradeRange)
	Case "99"
		' prek-12
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "70"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "71"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "72"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "73"
		End Select 
	case "98"
		' k - 12
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "74"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "75"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "76"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "77"
		End Select
	case "97"
		' Grades 10-12 Combined
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "86"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "87"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "88"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "89"
		End Select
	Case "96"
		' Grades 9-12 Combined 
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "82"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "83"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "84"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "85"
		End Select
		
	Case "95"
		' Grades 7-12 Combined 
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "78"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "79"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "80"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "81"
		End Select
	Case "94"
		' Grades 6-12 Combined 
		Select Case cSTR(zCurrSchoolType)
		Case "6"
			' elem
			GetDistrictSchoolTypeGrade = "90"
		Case "4", "5"
			' middle/junior high
			GetDistrictSchoolTypeGrade = "91"
		Case "3"
			' high
			GetDistrictSchoolTypeGrade = "92"
		Case "7"
			' combined elem/secondary
			GetDistrictSchoolTypeGrade = "93"
		End Select
	End Select
END IF
If GetDistrictSchoolTypeGrade = "" THEN
	' ????
	' nothing found school type must be odd 
	' set to same grade as school level data?
	' ????
	GetDistrictSchoolTypeGrade = zSubjGradeRange
END IF
END FUNCTION
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function SchoolTypeName(zTypeCode, zGradeRange)
'ht Jan 29/02:  took out () around schooltypename 
Select Case cSTR(zTypeCode)
Case "6"
	SchoolTypeName = ": Elem. Schools"
Case "4", "5"
	SchoolTypeName = ": Mid/Jr Hi Schools"
Case "3"
	SchoolTypeName = ": High Schools"
Case "7"
	SchoolTypeName = ": El/Sec Combined Schls"
Case "9"
	SchoolTypeName = " Summary "
Case "1"
	SchoolTypeName = ": (All School Types)"
End Select
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function GradeName(zInputGrade)
Select Case cSTR(zInputGrade)
Case "12"
	GradeName = "Pre-K"
Case "16"
	GradeName = "K"
Case "20"
	GradeName = "1"
Case "24"
	GradeName = "2"
Case "28"
	GradeName = "3"
Case "32"
	GradeName = "4"
Case "36"
	GradeName = "5"
Case "40"
	GradeName = "6"
Case "44"
	GradeName = "7"
Case "48"
	GradeName = "8"
Case "52"
	GradeName = "9"
Case "56"
	GradeName = "10"
Case "60"
	GradeName = "11"
Case "64"
	GradeName = "12"
Case "94"
	GradeName = "6-12"
Case "95"
	GradeName = "7-12"
Case "96"
	GradeName = "9-12"
Case "97"
	GradeName = "10-12"
Case "98"
	GradeName = "K-12"
Case "99"
	GradeName = "Prek-12"
End Select
End Function

Sub ChartYAxisFay()
	If zEligibleOnly = "YES" THEN
		Chart.Axis(AXIS_Y).Title = "Percent of Eligible Students Only"
	ELSEIf zEligibleOnly = "NO" THEN
		If StrOrgLevel <> "ST" THEN
			Chart.Axis(AXIS_Y).Title = "Percent of Students Enrolled FAY"
		ELSE
			Chart.Axis(AXIS_Y).Title = "Percent of Students Enrolled"
		END IF
	END IF
End Sub
Function EligibleOnlyName()
	If zEligibleOnly = "YES" THEN
		EligibleOnlyName= "Eligible Students Only"
	ELSEIf zEligibleOnly = "NO" THEN
		EligibleOnlyName= "All Students Enrolled FAY"
	ElseIf zEligibleOnly = "SS" THEN
		EligibleOnlyName= "Students Enrolled Single School FAY"
	END IF
End Function

''''''''''''''''''''''''''''''''''''''''
Function DropOutGradeLinks(ZQueryString)
DropOutGradeLinks = DropOutGradeLinks & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
If zGroup <> "Grade" THEN
	IF Session("TypeCode") = "3" THEN
		IF zGrade = "96" THEN
			DropOutGradeLinks = DropOutGradeLinks & "<font color='" & zActiveLinkColor & "'>Grades 9-12</A>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & "<A HREF='graphshell.asp?Grade=96&" & zQueryString & "'>Grades 9-12</A>"
		END IF
	END IF
	IF Session("TypeCode") = "4" or Session("TypeCode") = "5" or Session("TypeCode") = "7" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		IF zGrade = "95" THEN
			DropOutGradeLinks = DropOutGradeLinks & "<font color='" & zActiveLinkColor & "'>Grades 7-12</A>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & "<A HREF='graphshell.asp?Grade=95&" & zQueryString & "'>Grades 7-12</A>"
		END IF
	END IF
	IF Session("HasG7") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		IF zGrade = "44" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 7</FONT>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=44&" & zQueryString & "'>Grade 7</A>"
		END IF
	END IF
	IF Session("HasG8") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		If zGrade = "48" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 8</FONT>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=48&" & zQueryString & "'>Grade 8</A>"
		END IF
	END IF
	IF Session("HasG9") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		If zGrade = "52" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 9</FONT>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=52&" & zQueryString & "'>Grade 9</A>"
		END IF
	END IF
	IF Session("HasG10") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		If zGrade = "56" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 10</FONT>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=56&" & zQueryString & "'>Grade 10</A>"
		END IF
	END IF
	IF Session("HasG11") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		If zGrade = "60" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 11</FONT>"
		Else
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=60&" & zQueryString & "'>Grade 11</A>"
		END IF
	END IF
	IF Session("HasG12") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		If zGrade = "64" THEN
			DropOutGradeLinks = DropOutGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 12</FONT>"
		ELSE
			DropOutGradeLinks = DropOutGradeLinks & " <A HREF='graphshell.asp?Grade=64&" & zQueryString & "'>Grade 12</A>"
		END IF
	END IF
ELSE
	IF Session("TypeCode") = "3" THEN
		DropOutGradeLinks = DropOutGradeLinks & "<font color='#bcbcbc'>Grades 9-12</A>"
	END IF
	IF Session("TypeCode") = "4" or Session("TypeCode") = "5" or Session("TypeCode") = "7" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & "<font color='#bcbcbc'>Grades 7-12</A>"
	END IF
	IF Session("HasG7") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 7</FONT>"
	END IF
	IF Session("HasG8") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 8</FONT>"
	END IF
	IF Session("HasG9") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 9</FONT>"
	END IF
	IF Session("HasG10") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 10</FONT>"
	END IF
	IF Session("HasG11") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 11</FONT>"
	END IF
	IF Session("HasG12") = "T" THEN
		DropOutGradeLinks = DropOutGradeLinks & AddBullet(DropOutGradeLinks)
		DropOutGradeLinks = DropOutGradeLinks & " <font color='#bcbcbc'>Grade 12</FONT>"
END IF
END IF
DropOutGradeLinks = DropOutGradeLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function AddBullet(zToWhat)
	If zToWhat <> "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>" THEN
		AddBullet =  " &#149;"
	END IF
End Function
''''''''''''''''''''''''''''''''''''''''
Function AddBulletCourse(zToWhat)
	If zToWhat <> "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Grades:</TD><td class='text'>" THEN
		AddBulletCourse =  " &#149;"
	END IF
End Function
Function DropOutGradename(zGradeIn)

DropOutGradename = "Grade"
Select Case zGradeIN
Case "44"
	DropOutGradename = DropOutGradename &  " 7"
Case "48"
	DropOutGradename = DropOutGradename &  " 8"
Case "52"
	DropOutGradename = DropOutGradename &  " 9"
Case "56"
	DropOutGradename = DropOutGradename &  " 10"
Case "60"
	DropOutGradename = DropOutGradename &  " 11"
Case "64"
	DropOutGradename = DropOutGradename &  " 12"
Case "95"
	DropOutGradename = DropOutGradename &  "s 7-12"
Case "96"
	DropOutGradename = DropOutGradename &  "s 9-12"
Case "97"
	DropOutGradename = DropOutGradename &  "s 10-12"
Case "98"
	DropOutGradename = DropOutGradename &  "s K-12"
Case "99"
	DropOutGradename = DropOutGradename &  "s Prek-12"
End Select
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''
Function GenCompareToLinksGrad(zQueryString)
	GenCompareToLinksGrad = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
'	IF zCompareTo = "PRIORYEARS" THEN
		GenCompareToLinksGrad = GenCompareToLinksGrad & "Prior Years"
	GenCompareToLinksGrad = GenCompareToLinksGrad & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Sub BarGraphBlackBox()
	' this black box needs these values set for it:
	' zNumPoints (number of groups of bars), zNumSets (number of sets in legend - e.g. how many years), 
	' zDecimals (Y axis and Label decimal places), zYTitle (left title)
	' zGraphTitle (duh), zLegBox (true or false (1/0) - show legend?)
	' zFieldPosLegend (which column contains the legend text? usually 0 )
	' zLabelPos (which column - if any contains the X axis Label text - e.g. the groups)
	' zLabelOverRide (set to a string to override the zLabelPos - e.g. "All Students"
	' zFieldPosPerformance (recordset Ordinal reference - column containing data to be graphed, e.g. 1 = column 2 in recordset - 0 based)
	' zYaxisMax (optional- default to 100) sets Y axis max

	'jdj: new debug code
	if not isempty(request.querystring("DEBUG")) and cInt(request.querystring("DEBUG")) > 2 then 
		response.write "<br>"
		response.write "zNumPoints: " & zNumPoints & "<br>"
		response.write "zNumSets: " &  zNumSets & "<br>"
		response.write "zDecimals: " &  zDecimals & "<br>"
		response.write "zYTitle: " &  zYTitle & "<br>"
		response.write "zGraphTitle: " &  zGraphTitle & "<br>"
		response.write "zLegBox: " &  zLegBox & "<br>"
		response.write "zFieldPosLegend: " &  zFieldPosLegend & "<br>"
		response.write "zLabelPos: " &  zLabelPos & "<br>"
		response.write "zLabelOverRide: " &  zLabelOverRide & "<br>"
		response.write "zFieldPosPerformance: " &  zFieldPosPerformance & "<br>"
		response.write "zYaxisMax: " &  zYaxisMax & "<br>"
	end if	
	
	Chart.Axis(AXIS_Y).Min = 0
	' this if statement is overridden by the setting of Chart.Axis(AXIS_Y).Max below
	If zYaxisMax <> ""  then
		Chart.Axis(AXIS_Y).Max = zYaxisMax
	else
		Chart.Axis(AXIS_Y).Max = 100
	end if

	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	if zGraphInclude = "ACT" then
		Chart.Axis(AXIS_X).Style = Chart.Axis(AXIS_X).Style or AS_2LEVELS
	end if
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_Y).Title = zYTitle
	Chart.SerLegBox = zLegBox
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumSets, zNumPoints
	zLabelHold = ""
	zMax = 0 
	RS.movefirst
	FOR zSetNum = 0 to (cDBL(zNumSets) -1)
		'response.write("zsetnum" & zSetnum & "<BR>")
		If not RS.EOF THEN
			if zGraphInclude = "GGRADPLAN" and zplan = "All" and zGroup = "AllStudentsFAY" then
				'Chart.SerLeg(zSetNum) = " All Students" ????
			else	
				Chart.SerLeg(zSetNum) = trim(RS.Fields(zFieldPosLegend).Value)	
			end if
			'response.write("Numpoints" & zNumPoints & "<BR>")
			FOR zPointNum = 0 to (cDBL(zNumPoints)-1)
				'response.write("zPointNum" & zPointNum& "<BR>")
				if not RS.eof then
				    If zLabelOverRide = "" THEN
						Chart.Axis(AXIS_X).Label(zPointNum) = trim(RS.Fields(zLabelPos).Value)
					ELSE
						Chart.Axis(AXIS_X).Label(zPointNum) = zLabelOverRide
					END IF
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset

					' jdj: must use trim below or graph fails on some numbers in grad reqs
					'IF isnumeric(RS.Fields(zFieldPosPerformance).Value) THEN
					IF isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						IF cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zSetNum, zPointNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
						If zMax < cDBL(RS.Fields(zFieldPosPerformance).Value) THEN
							zMax = cDBL(RS.Fields(zFieldPosPerformance).Value)
						END IF

					ELSE
						Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
					END IF
					nodata = false
					RS.movenext
				else
					Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
	NEXT
	If zMax >= cDBL(Chart.Axis(AXIS_Y).Max) THEN
		If zMax > 0 and zMax < 10 THEN
			Chart.Axis(AXIS_Y).Max = 10
		ElseIf zMax >= 10 and zMax < 25 THEN
			Chart.Axis(AXIS_Y).Max = 25
		ElseIf zMax >= 25 and zMax < 50 THEN
			Chart.Axis(AXIS_Y).Max = 50
		ElseIf zMax >= 50 and zMax < 75 THEN
			Chart.Axis(AXIS_Y).Max = 75
		' note - if any value in the chart equals 100, the Y Axis goes to 150.....
		ElseIf zMax >= 75 and zMax < 100 THEN
			Chart.Axis(AXIS_Y).Max = 100
		ElseIf zMax >= 100 and zMax < 150 THEN
			Chart.Axis(AXIS_Y).Max = 150
		ElseIf zMax >= 150 and zMax < 200 THEN
			Chart.Axis(AXIS_Y).Max = 200
		ElseIf zMax >= 200 and zMax < 300 THEN
			Chart.Axis(AXIS_Y).Max = 300
		ElseIf zMax >= 300 and zMax < 500 THEN
			Chart.Axis(AXIS_Y).Max = 500
		ElseIf zMax >= 500 and zMax < 750 THEN
			Chart.Axis(AXIS_Y).Max = 750
		ElseIf zMax >= 750 and zMax < 1000 THEN
			Chart.Axis(AXIS_Y).Max = 1000
		ElseIf zMax >= 1000 and zMax < 1500 THEN
			Chart.Axis(AXIS_Y).Max = 1500
		Else
			Chart.Axis(AXIS_Y).Max = zMax
		END IF
	END IF
	Chart.CloseData COD_VALUES
	call ChartColorSeries(zNumSets)
End Sub
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Sub StackeDHorizontalBarGraphBlackBox()
	' depends on variables 
	' zFieldPosPerformance, zSuperLabelPos, zLabelPos
	' zGraphTitle, zDecimals, zYTitle, zNumPoints, zNumSets
	' brb added back to make graphs for post grad and suspension incidents HORIZONTAL!
	Chart.Gallery = GANTT
	' end brb
	Chart.Stacked = CHART_STACKED100
	Chart.Axis(AXIS_X).Step = 1
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 100
	'Chart.Axis(AXIS_X).Style = Chart.Axis(AXIS_X).Style or AS_2LEVELS
	'Chart.Axis(AXIS_X).LabelAngle = 50
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_X).Title = zYTitle
	Chart.SerLegBox = True
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumPoints, zNumSets
	zPosHold = zFieldPosPerformance
	' add one set of numpoints for blanks between sets
	zSuperLabelHold = ""
	zCount = 0
	FOR zSetNum = (zNumSets -1) to 0 step -1
		zFieldPosPerformance = zPosHold
		If not RS.EOF THEN
			If trim(RS.Fields(zSuperLabelPos).Value) <> zSuperLabelHold THEN
				if 	zSuperLabelPos <> zLabelPos then
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value) & "            " &  trim(RS.Fields(zLabelPos).Value)
				else
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value)
				end if
				zSuperLabelHold = trim(RS.Fields(zSuperLabelPos).Value)
			ELSE
				Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zLabelPos).Value)
			END IF
			FOR zPointNum = 0 to (zNumPoints-1)
				if not RS.eof then
					If zNumPoints > 1 THEN
						Chart.SerLeg(zPointNum) = trim(RS.Fields(zFieldPosPerformance).name)
					END IF
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					If isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						If cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							' hide it so no weird lines show on the axis...
							Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zPointNum, zSetNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
					ELSE
						Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
					END IF
					nodata = false
					zFieldPosPerformance = zFieldPosPerformance +1
					'increment which field gets graphed 
					'they MUST be in right column order in the recordset
				else
					Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
		RS.movenext
	NEXT
	Chart.CloseData COD_VALUES
	zFieldPosPerformance = zPosHold
	call ChartColorSeries(zNumPoints)
End Sub
''''''''''''''''''''''''''''''''''''''''
FUNCTION DisabilOrLepLinks(ZQueryString)
	DisabilOrLepLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	IF zDisabilOrLep = "Disabil" THEN
		DisabilOrLepLinks = DisabilOrLepLinks & "Disabilities &#149; " & _ 
			"<A HREF='graphshell.asp?DisabilOrLep=Lep&" & zQueryString & "'>Limited English proficiency</A>"
	ELSE
		DisabilOrLepLinks = DisabilOrLepLinks & "<A HREF='graphshell.asp?DisabilOrLep=Disabil&" & zQueryString & "'>Disabilities</A> &#149; " & _ 
			"<FONT COLOR='" & zActiveLinkColor & "'>Limited English Proficiency</FONT>"
	END IF
	DisabilOrLepLinks = DisabilOrLepLinks & "</TD></TABLE>"
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetDisabilOrLep()
	If not isempty(Request.QueryString("DisabilOrLep")) THEN
		GetDisabilOrLep = Request.QueryString("DisabilOrLep")
	ELSE
		'default to rate
		GetDisabilOrLep = "DISABIL"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksDisabilLep(zQueryString)
	GenGroupLinksDisabilLep = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class=text>View By:</TD><TD class=text>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & " &#149; "
	If zGroup = "Gender" THEN
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
	ELSE
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
	END IF
	GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & " &#149; "
	If zGroup = "Race/Ethnicity" THEN
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
	ELSE
		GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
	END IF
	GenGroupLinksDisabilLep = GenGroupLinksDisabilLep & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksGroups(zQueryString)
	GenGroupLinksGroups = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "Gender" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
	ELSEIF strTypeCode = "1" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>Gender</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "Race/Ethnicity" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
	ELSEIF strTypeCode = "1" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "Disability" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
	' per WINSS_checking_1208051.doc, 17b
	'ELSEIF strTypeCode = "1" THEN
	ELSEIF strTypeCode = "1" or strTypeCode = "9" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>Disability</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "EconomicStatus"  THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>Economic Status</FONT> "
	ELSEIF strTypeCode = "1" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>Economic Status</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=EconomicStatus&" & zQueryString & "'>Economic Status</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "EnglishProficiency" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>English Proficiency</FONT> "
	ELSEIF strTypeCode = "1" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>English Proficiency</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=EnglishProficiency&" & zQueryString & "'>English Proficiency</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & " &#149; "
	If zGroup = "Grade" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
	ELSEIF strTypeCode = "1" THEN
		GenGroupLinksGroups = GenGroupLinksGroups & "<font color='#bcbcbc'>Grade</FONT> "
	ELSE
		GenGroupLinksGroups = GenGroupLinksGroups & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
	END IF
	GenGroupLinksGroups = GenGroupLinksGroups & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenLEPShow(zQueryString)
	GenLEPShow = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>" 
	If zLEPShow = "ELP" THEN
		GenLEPShow = GenLEPShow & "<font color='" & zActiveLinkColor & "'>English Language Proficiency Levels</FONT> "
	ELSE
		GenLEPShow = GenLEPShow & "<A HREF='graphshell.asp?Show=ELP&" & zQueryString & "'>English Language Proficiency Levels</A> "
	END IF
	GenLEPShow = GenLEPShow & " &#149; "
	If zLEPShow = "RaceEth" THEN
		'GenLEPShow = GenLEPShow & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
		GenLEPShow = GenLEPShow & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
	ELSE
		'GenLEPShow = GenLEPShow & "<A HREF='graphshell.asp?Show=RaceEth&" & zQueryString & "'>Race/Ethnicity</A> "
		GenLEPShow = GenLEPShow & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
	END IF 
	GenLEPShow = GenLEPShow & "</TD></TR></TABLE>" 
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksLEP(zQueryString)
	GenGroupLinksLEP = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksLEP = GenGroupLinksLEP & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksLEP = GenGroupLinksLEP & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksLEP = GenGroupLinksLEP & " &#149; "
	If zGroup = "Gender" THEN
		GenGroupLinksLEP = GenGroupLinksLEP & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
	ELSE
		'If zLEPShow = "ELP" THEN
			GenGroupLinksLEP = GenGroupLinksLEP & "<font color='#bcbcbc'>Gender</FONT> "
		'ELSE
			'GenGroupLinksLEP = GenGroupLinksLEP & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		'endif
	END IF
	GenGroupLinksLEP = GenGroupLinksLEP & " &#149; "
	If zGroup = "Grade" THEN
		GenGroupLinksLEP = GenGroupLinksLEP & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
	ELSE
		GenGroupLinksLEP = GenGroupLinksLEP & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
	END IF
	GenGroupLinksLEP = GenGroupLinksLEP & " &#149; "
	If zGroup = "LanguageGroup" THEN
		GenGroupLinksLEP = GenGroupLinksLEP & "<font color='" & zActiveLinkColor & "'>Language Group</FONT> "
	ELSE
		GenGroupLinksLEP = GenGroupLinksLEP & "<A HREF='graphshell.asp?Group=LanguageGroup&" & zQueryString & "'>Language Group</A> "
	END IF
	GenGroupLinksLEP = GenGroupLinksLEP & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GetGroupSel()
	If not isempty(Request.QueryString("Groups")) THEN
		GetGroupSel = Request.QueryString("Groups")
	ELSE
		'default to AllStudentsFAY
		GetGroupSel = "AllStudentsFAYx"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Sub BarGraphBlackBoxGroups()
	' this black box needs these values set for it:
	' zNumPoints, zNumSets, zDecimals, zYTitle, zGraphTitle, zLegBox
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 10
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	'Chart.Axis(AXIS_X).Style = Chart.Axis(AXIS_X).Style or AS_2LEVELS
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_Y).Title = zYTitle
	Chart.SerLegBox = zLegBox
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumSets, zNumPoints
	Chart.Axis(AXIS_X).Label(zPointNum) = zXLabelGroups
	zLabelHold = ""
	zMax = 0 
	FOR zSetNum = 0 to (zNumSets -1)
		If not RS.EOF THEN
			Chart.SerLeg(zSetNum) = trim(RS.Fields(zFieldPosLegend).Value)		
			FOR zPointNum = 0 to (zNumPoints-1)
				if not RS.eof then
					' chopping below to fix X Label 
					' Chart.Axis(AXIS_X).Label(zPointNum) = trim(RS.Fields(zLabelPos).Value)
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					IF isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						IF cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zSetNum, zPointNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
						If zMax < cDBL(RS.Fields(zFieldPosPerformance).Value) THEN
							zMax = cDBL(RS.Fields(zFieldPosPerformance).Value)
						END IF
					ELSE
						Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
					END IF
					nodata = false
					RS.movenext
				else
					Chart.ValueEx(zSetNum, zPointNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
	NEXT
	If zMax >= cDBL(Chart.Axis(AXIS_Y).Max) THEN
		If zMax > 0 and zMax < 10 THEN
			Chart.Axis(AXIS_Y).Max = 10
		ElseIf zMax >= 10 and zMax < 25 THEN
			Chart.Axis(AXIS_Y).Max = 25
		ElseIf zMax >= 25 and zMax < 50 THEN
			Chart.Axis(AXIS_Y).Max = 50
		ElseIf zMax >= 50 and zMax < 75 THEN
			Chart.Axis(AXIS_Y).Max = 75
		ElseIf zMax >= 75 and zMax < 100 THEN
			Chart.Axis(AXIS_Y).Max = 100
		ElseIf zMax >= 100 and zMax < 150 THEN
			Chart.Axis(AXIS_Y).Max = 150
		ElseIf zMax >= 150 and zMax < 200 THEN
			Chart.Axis(AXIS_Y).Max = 200
		ElseIf zMax >= 200 and zMax < 300 THEN
			Chart.Axis(AXIS_Y).Max = 300
		ElseIf zMax >= 300 and zMax < 500 THEN
			Chart.Axis(AXIS_Y).Max = 500
		ElseIf zMax >= 500 and zMax < 750 THEN
			Chart.Axis(AXIS_Y).Max = 750
		ElseIf zMax >= 750 and zMax < 1000 THEN
			Chart.Axis(AXIS_Y).Max = 1000
		ElseIf zMax >= 1000 and zMax < 1500 THEN
			Chart.Axis(AXIS_Y).Max = 1500
		Else
			Chart.Axis(AXIS_Y).Max = zMax
		END IF
	END IF
	Chart.CloseData COD_VALUES
	call ChartColorSeries(zNumSets)
End Sub
''''''''''''''''''''''''''''''''''''''''
Sub StackeDHorizontalBarGraphBlackBoxGroups()
Chart.Stacked = CHART_STACKED
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.Gallery = GANTT
	Chart.Stacked = CHART_STACKED100
	Chart.Axis(AXIS_X).Step = 1
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 100
	'Chart.Axis(AXIS_X).Style = Chart.Axis(AXIS_X).Style or AS_2LEVELS
	'Chart.Axis(AXIS_X).LabelAngle = 50
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_X).Title = zYTitle
	Chart.SerLegBox = True
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumPoints, zNumSets
	zPosHold = zFieldPosPerformance
	' add one set of numpoints for blanks between sets
	zSuperLabelHold = ""
	zCount = 0

' 2005-11-16 - adding 1 to zNumSets/zNumPoints to diagnose problem

'zNumPoints = zNumPoints - 1
'zNumSets = zNumSets + 1

'response.write "<br>zNumPoints:" & zNumPoints & "<br>"
'response.write "zNumSets:" & zNumSets & "<br>"
'response.write "zLowGrade: " & zLowGrade & "<br>"
'response.write "zHighGrade: " & zHighGrade & "<br>"
'response.write "zLowGradePoint: " & zLowGradePoint & "<br>"
'response.write "zHighGradePoint: " & zHighGradePoint & "<br>"
'response.write "zFieldPosPerformance: " & zFieldPosPerformance & "<br>"

	FOR zSetNum = (zNumSets -1) to 0 step -1
		zFieldPosPerformance = zPosHold
		If not RS.EOF THEN
			If trim(RS.Fields(zSuperLabelPos).Value) <> zSuperLabelHold THEN
'				if 	zSuperLabelPos <> zLabelPos then
'					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value) & "            " &  trim(RS.Fields(zLabelPos).Value)
'				else
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value)
'				end if
				zSuperLabelHold = trim(RS.Fields(zSuperLabelPos).Value)
			ELSE
				Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zLabelPos).Value)
			END IF
			FOR zPointNum = 0 to (zNumPoints-1)
				if not RS.eof then
' jdj 2006-09-01 - Milwaukee Learning Lab, with just one grade, Grade 9, was failing to show the grade label on the graph - presumably because it gets zNumPoints = 0 
' changing this test from 1 to 0 
					'If zNumPoints > 1 THEN
					If zNumPoints > 0 THEN

'response.write "zPointNum: " & zPointNum & "<br>"
'response.write "zFieldPosPerformance: " & zFieldPosPerformance & "<br>"
'response.write trim(RS.Fields(zFieldPosPerformance).name) & "<br>"

						Chart.SerLeg(zPointNum) = trim(RS.Fields(zFieldPosPerformance).name)
					END IF
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					If isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						If cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							' hide it so no weird lines show on the axis...
							Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zPointNum, zSetNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
					ELSE
						Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
					END IF
					nodata = false
					zFieldPosPerformance = zFieldPosPerformance +1
					'increment which field gets graphed 
					'they MUST be in right column order in the recordset
				else
					Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
		RS.movenext
	NEXT
	Chart.CloseData COD_VALUES
	zFieldPosPerformance = zPosHold
	call ChartColorSeries(zNumPoints)
End Sub
''''''''''''''''''''''''''''''''''''''''
Sub BarGraphBlackBoxReversePointsSets()
	' this black box needs these values set for it:
	' zNumPoints, zNumSets, zDecimals, zYTitle, zGraphTitle, zLegBox
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 10
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	'Chart.Axis(AXIS_X).Style = Chart.Axis(AXIS_X).Style or AS_2LEVELS
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_Y).Title = zYTitle
	Chart.SerLegBox = zLegBox
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	'Chart.OpenDataEx COD_VALUES, zNumSets, zNumPoints
	Chart.OpenDataEx COD_VALUES, zNumPoints, zNumSets
	zLabelHold = ""
	zMax = 0 
	FOR zSetNum = 0 to (zNumSets -1)
		If not RS.EOF THEN
			If zLabelOverRide = "" THEN
				Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zLabelPos).Value)
			ELSE
				Chart.Axis(AXIS_X).Label(zSetNum) = zLabelOverRide
			END IF
			FOR zPointNum = 0 to (zNumPoints-1)
				if not RS.eof then
					Chart.SerLeg(zPointNum) = trim(RS.Fields(zFieldPosLegend).Value) 
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					IF isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						IF cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zPointNum,zSetNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
						If zMax < cDBL(RS.Fields(zFieldPosPerformance).Value) THEN
							zMax = cDBL(RS.Fields(zFieldPosPerformance).Value)
						END IF
					ELSE
						Chart.ValueEx(zPointNum,zSetNum) = CHART_HIDDEN
					END IF
					nodata = false
					RS.movenext
				else
					Chart.ValueEx(zPointNum,zSetNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
	NEXT
	If zMax >= cDBL(Chart.Axis(AXIS_Y).Max) THEN
		If zMax > 0 and zMax < 10 THEN
			Chart.Axis(AXIS_Y).Max = 10
		ElseIf zMax >= 10 and zMax < 25 THEN
			Chart.Axis(AXIS_Y).Max = 25
		ElseIf zMax >= 25 and zMax < 50 THEN
			Chart.Axis(AXIS_Y).Max = 50
		ElseIf zMax >= 50 and zMax < 75 THEN
			Chart.Axis(AXIS_Y).Max = 75
		ElseIf zMax >= 75 and zMax < 100 THEN
			Chart.Axis(AXIS_Y).Max = 100
		ElseIf zMax >= 100 and zMax < 150 THEN
			Chart.Axis(AXIS_Y).Max = 150
		ElseIf zMax >= 150 and zMax < 200 THEN
			Chart.Axis(AXIS_Y).Max = 200
		ElseIf zMax >= 200 and zMax < 300 THEN
			Chart.Axis(AXIS_Y).Max = 300
		ElseIf zMax >= 300 and zMax < 500 THEN
			Chart.Axis(AXIS_Y).Max = 500
		ElseIf zMax >= 500 and zMax < 750 THEN
			Chart.Axis(AXIS_Y).Max = 750
		ElseIf zMax >= 750 and zMax < 1000 THEN
			Chart.Axis(AXIS_Y).Max = 1000
		ElseIf zMax >= 1000 and zMax < 1500 THEN
			Chart.Axis(AXIS_Y).Max = 1500
		Else
			Chart.Axis(AXIS_Y).Max = zMax
		END IF
	END IF
	Chart.CloseData COD_VALUES
    ' start of 11/2001 code
        if zCompareTo = "DISTSTATE" and zGraphInclude = "SSACTIVITIES" then 
            if strOrgLevel = "SC" then
                strBarColorOrgLevel = zNumPoints
            elseif strOrgLevel = "DI" then
                strBarColorOrgLevel = 21
            else
                strBarColorOrgLevel = 22
            end if 
        else 
            strBarColorOrgLevel = zNumPoints
        end if
        ' end of 11/2001 code
        call ChartColorSeries(strBarColorOrgLevel)
End Sub
''''''''''''''''''''''''''''''''''''''''
Sub StackeDHorizontalBarGraphBlackBoxFloat()
	Chart.Gallery = BAR
	Chart.Stacked = CHART_STACKED
	Chart.Axis(AXIS_X).Step = 1
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_X).Title = zYTitle
	Chart.SerLegBox = True
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumPoints, zNumSets
	zPosHold = zFieldPosPerformance
	' add one set of numpoints for blanks between sets
	zSuperLabelHold = ""
	zCount = 0
	' variable for setting Y Axis max below
	zMax = 0
	'FOR zSetNum = (zNumSets -1) to 0 step -1
	FOR zSetNum = 0 to (zNumSets -1) 
		zFieldPosPerformance = zPosHold
		If not RS.EOF THEN
			If trim(RS.Fields(zSuperLabelPos).Value) <> zSuperLabelHold THEN
				if 	zSuperLabelPos <> zLabelPos then
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value) & "            " &  trim(RS.Fields(zLabelPos).Value)
				else
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value) 
				end if
				zSuperLabelHold = trim(RS.Fields(zSuperLabelPos).Value)
			ELSE
				Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zLabelPos).Value)
			END IF
			'brb trying to edit length for those which are too long..
			if instr(Chart.Axis(AXIS_X).Label(zSetNum),"(") > 0 THEN
				Chart.Axis(AXIS_X).Label(zSetNum) = mid(Chart.Axis(AXIS_X).Label(zSetNum),1,(instr(Chart.Axis(AXIS_X).Label(zSetNum),"(")-1))
			END IF
			'FOR zPointNum = 0 to (zNumPoints-1)
			' brb playing with order of bars...
			' variable for getting the total value of the stacks (points) in a bar, so we can set the Y Axis
			zMaxBar = 0
			FOR zPointNum = (zNumPoints-1) to 0 step -1
				if not RS.eof then
					If zNumPoints > 1 THEN
						Chart.SerLeg(zPointNum) = trim(RS.Fields(zFieldPosPerformance).name)
					END IF
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					If isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						If cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							' hide it so no weird lines show on the axis...
							Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zPointNum, zSetNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
						' add the values of the stacks together, to set Y Axis
						zMaxBar = zMaxBar + cDBL(RS.Fields(zFieldPosPerformance).Value) 
					ELSE
						Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
					END IF
					nodata = false
					zFieldPosPerformance = zFieldPosPerformance + 1
					'increment which field gets graphed 
					'they MUST be in right column order in the recordset
				else
					Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
		' set the Y-axis-setting-variable to the highest total of stacks of all the bars
		If zMax < zMaxBar THEN
			zMax = zMaxBar
		END IF
		if RS.recordcount>1 then
		RS.movenext
		end if
	NEXT
	' set the Y axis to a nice round number a little higher than the total of the values in the stacked bar
	If zMax >= cDBL(Chart.Axis(AXIS_Y).Max) THEN
		If zMax > 0 and zMax < 10 THEN
			Chart.Axis(AXIS_Y).Max = 10
		ElseIf zMax >= 10 and zMax < 25 THEN
			Chart.Axis(AXIS_Y).Max = 25
		ElseIf zMax >= 25 and zMax < 50 THEN
			Chart.Axis(AXIS_Y).Max = 50
		ElseIf zMax >= 50 and zMax < 75 THEN
			Chart.Axis(AXIS_Y).Max = 75
		ElseIf zMax >= 75 and zMax < 100 THEN
			Chart.Axis(AXIS_Y).Max = 100
		ElseIf zMax >= 100 and zMax < 150 THEN
			Chart.Axis(AXIS_Y).Max = 150
		ElseIf zMax >= 150 and zMax < 200 THEN
			Chart.Axis(AXIS_Y).Max = 200
		ElseIf zMax >= 200 and zMax < 300 THEN
			Chart.Axis(AXIS_Y).Max = 300
		ElseIf zMax >= 300 and zMax < 500 THEN
			Chart.Axis(AXIS_Y).Max = 500
		ElseIf zMax >= 500 and zMax < 750 THEN
			Chart.Axis(AXIS_Y).Max = 750
		ElseIf zMax >= 750 and zMax < 1000 THEN
			Chart.Axis(AXIS_Y).Max = 1000
		ElseIf zMax >= 1000 and zMax < 1500 THEN
			Chart.Axis(AXIS_Y).Max = 1500
		Else
			Chart.Axis(AXIS_Y).Max = 1.5 * zMax
		END IF
	END IF
	Chart.CloseData COD_VALUES
	zFieldPosPerformance = zPosHold
	call ChartColorSeries(zNumPoints)
End Sub
''''''''''''''''''''''''''''''''''''''''
Sub StackedHorizontalBarGraphNot100BlackBox()
	Chart.Stacked = CHART_STACKED
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.Gallery = GANTT
	Chart.Stacked = CHART_STACKED
	Chart.Axis(AXIS_X).Step = 1
	Chart.Axis(AXIS_Y).Min = 0
	Chart.Axis(AXIS_Y).Max = 100
	'Chart.Axis(AXIS_Y).AdjustScale
	Chart.Title(CHART_TOPTIT) = zGraphTitle
	Chart.Axis(AXIS_Y).Decimals = zDecimals
	Chart.Axis(AXIS_Y).Grid = TRUE
	Chart.RgbBk = RGB(255,255,255)
	Chart.Chart3D = FALSE
	Chart.Axis(AXIS_X).Title = zYTitle
	Chart.SerLegBox = True
	Chart.SerLegBoxObj.Docked = TGFP_BOTTOM
	Chart.Fonts(CHART_TOPFT) = CF_BOLD Or 10
	Chart.OpenDataEx COD_VALUES, zNumPoints, zNumSets
	zPosHold = zFieldPosPerformance
	' add one set of numpoints for blanks between sets
	zSuperLabelHold = ""
	zCount = 0
	FOR zSetNum = (zNumSets -1) to 0 step -1
		zFieldPosPerformance = zPosHold
		If not RS.EOF THEN
			If trim(RS.Fields(zSuperLabelPos).Value) <> zSuperLabelHold THEN
				if 	zSuperLabelPos <> zLabelPos then
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value) & "            " &  trim(RS.Fields(zLabelPos).Value)
				else
					Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zSuperLabelPos).Value)
				end if
				zSuperLabelHold = trim(RS.Fields(zSuperLabelPos).Value)
			ELSE
				Chart.Axis(AXIS_X).Label(zSetNum) = trim(RS.Fields(zLabelPos).Value)
			END IF
			FOR zPointNum = 0 to (zNumPoints-1)
				if not RS.eof then
					If zNumPoints > 1 THEN
						Chart.SerLeg(zPointNum) = trim(RS.Fields(zFieldPosPerformance).name)
					END IF
					' Use non specific ordinal reference to access field in RS used for performance value
					' i.e. RS.Fields(0).Value, means data in the first column of recordset
					If isnumeric(trim(RS.Fields(zFieldPosPerformance).Value)) THEN
						If cDBL(RS.Fields(zFieldPosPerformance).Value) = 0 THEN
							' hide it so no weird lines show on the axis...
							Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
						ELSE
							Chart.ValueEx(zPointNum, zSetNum) = FormatNumber(RS.Fields(zFieldPosPerformance).Value, zDecimals)
						END IF
					ELSE
						Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
					END IF
					nodata = false
					zFieldPosPerformance = zFieldPosPerformance +1
					'increment which field gets graphed 
					'they MUST be in right column order in the recordset
				else
					Chart.ValueEx(zPointNum, zSetNum) = CHART_HIDDEN
				end if
			NEXT
		END IF
		RS.movenext
	NEXT
	Chart.CloseData COD_VALUES
	zFieldPosPerformance = zPosHold
	call ChartColorSeries(zNumPoints)
	
if cInt(request.querystring("dbg")) = 2 then
	response.write("zLEPMax = " & zLEPMax)
end if
End Sub
''''''''''''''''''''''''''''''''''''''''
FUNCTION ParseQS(strQS, strValue)
    For Each Item In Request.QueryString
        if LCase(item) <> LCase(strQS) then 
    		ParseQS = ParseQS & (Item & "=" & Server.URLEncode(Request.QueryString(Item)) & "&")
        end if
    Next 
    ParseQS = ParseQS & (UCase(strQS) & "=" & UCase(strValue))
	' chop trailing ampersand
	if right(ParseQS,1) = "&" then 
		ParseQS = mid(ParseQS, 1, (len(ParseQS)-1))
	end if
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
' jdj: doesn't UCase output
FUNCTION ParseQS2(strQS, strValue)
    For Each Item In Request.QueryString
        if LCase(item) <> LCase(strQS) then 
    		ParseQS2 = ParseQS2 & (Item & "=" & Server.URLEncode(Request.QueryString(Item)) & "&")
        end if
    Next 
    ParseQS2 = ParseQS2 & (strQS & "=" & strValue)
	' chop trailing ampersand
	if right(ParseQS2,1) = "&" then 
		ParseQS2 = mid(ParseQS2, 1, (len(ParseQS2)-1))
	end if
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GetFullkeyListSelected()
	GetFullkeyListSelected = "'" & Session("Fullkey") & "'"
	If not isempty(trim(Session("sSchool4ID"))) and Session("sSchool4ID") <> "zz" THEN
		GetFullkeyListSelected = GetFullkeyListSelected & ",'" & Session("sSchool4ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool3ID"))) and Session("sSchool3ID") <> "zz"  THEN
		GetFullkeyListSelected = GetFullkeyListSelected & ",'" & Session("sSchool3ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool2ID"))) and Session("sSchool2ID") <> "zz" THEN
		GetFullkeyListSelected = GetFullkeyListSelected & ",'" & Session("sSchool2ID") & "'"
	END IF
	If not isempty(trim(Session("sSchool1ID"))) and Session("sSchool1ID") <> "zz"  THEN
		GetFullkeyListSelected = GetFullkeyListSelected & ",'" & Session("sSchool1ID") & "'"
	END IF
End Function
''''''''''''''''''''''''''''''''''''''''
Function IncludeIfOrgLevel(strOrgLevelName, strOrgLevelVar, strTextToInclude)
if strOrgLevelName = strOrgLevelVar then
    IncludeIfOrgLevel = strTextToInclude
else 
    IncludeIfOrgLevel = ""
end if
End Function
''''''''''''''''''''''''''''''''''''''''
Function ExcludeIfOrgLevel(strOrgLevelName, strOrgLevelVar, strTextToExclude)
if strOrgLevelName =  strOrgLevelVar then
    ExcludeIfOrgLevel = ""
else 
    ExcludeIfOrgLevel = strTextToExclude
end if
End Function
''''''''''''''''''''''''''''''''''''''''
Function IncludeIfMatch(strMatch1, strMatch2, strTextToInclude)
if strMatch1 = strMatch2 then
    IncludeIfMatch = strTextToInclude
else 
    IncludeIfMatch = ""
end if
End Function
''''''''''''''''''''''''''''''''''''''''
Function ExcludeIfMatch(strMatch1, strMatch2, strTextToExclude)
if strMatch1 = strMatch2 then
    ExcludeIfMatch = ""
else 
    ExcludeIfMatch = strTextToExclude
end if
End Function
''''''''''''''''''''''''''''''''''''''''
Function IncludeIfMatchElse(strMatch1, strMatch2, strTextToInclude1, strTextToInclude2)
if strMatch1 = strMatch2 then
    IncludeIfMatchElse = strTextToInclude1
else 
    IncludeIfMatchElse = strTextToInclude2
end if
End Function
''''''''''''''''''''''''''''''''''''''''
Function ExcludeIfMatchElse(strMatch1, strMatch2, strTextToExclude1, strTextToExclude2)
if strMatch1 = strMatch2 then
    ExcludeIfMatchElse = strTextToExclude2
else 
    ExcludeIfMatchElse = strTextToExclude1
end if
End Function
''''''''''''''''''''''''''''''''''''''''
FUNCTION PassQS()
    For Each Item In Request.QueryString
   		PassQS = PassQS & (Item & "=" & Server.URLEncode(Request.QueryString(Item)) & "&")
    Next 
    ' chop the trailing ampersand
    intLengthMinus1 = (len(PassQS)-1)
    if intLengthMinus1 > 0 then 
        PassQS = left(PassQS,intLengthMinus1)
    end if
END FUNCTION 
''''''''''''''''''''''''''''''''''''''''
function SetQSVars()
     if isempty(request.QueryString("Fullkey")) then 
        strFullkey = "XXXXXXXXXXXX"
    else 
        strFullkey = request.QueryString("Fullkey")
    end if 
    
    if isempty(request.QueryString("SN")) then 
        strSchoolName = "None Chosen"
    else 
        strSchoolName = request.QueryString("SN")
    end if 
    
    if isempty(request.QueryString("DN")) then 
        strDistrictName = "None Chosen"
    else 
        strDistrictName = request("DN")
    end if 
end function 
''''''''''''''''''''''''''''''''''''''''
Sub AddWhereHighLowGrade()
	If strOrgLevel = "SC" THEN
		' school level is based on high low grades
		 zWhere = zWhere & " and (V_enrollment.Grade >= " & zLowgrade & " and v_enrollment.Grade < = " & zHighGrade & ") "
	END IF
End Sub
''''''''''''''''''''''''''''''''''''''''
Function AddWhereHighLowGradeV(zColumnPrefix)
	If strOrgLevel = "SC" THEN
		' school level is based on high low grades
		 zWhereV = zWhereV & " and (" & zColumnPrefix & ".Grade >= " & zLowgrade & " and " & zColumnPrefix & ".Grade < = " & zHighGrade & ") "
	END IF
End Function
''''''''''''''''''''''''''''''''''''''''
Function DistStateSchoolTypeLinks(zQueryString)
	DistStateSchoolTypeLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>School Type:</TD><td class='text'>"
	If zgroup = "Grade" Then
		' only summary option is available
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>All Types</FONT> &#149; "
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>Elem</FONT> &#149; "
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>Mid/Jr Hi</FONT> &#149; "
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>High</FONT> &#149; "
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>El/Sec</FONT> &#149; "
	Else
		IF zGraphInclude = "SSACTIVITIES" THEN
			' all types not available
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>All Types</FONT> &#149; "
		elseif strTypeCode = "1" Then
			' all types chosen
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>All Types</FONT> &#149; "
		else
			' all types hot
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=1&" & zQueryString & "'>All Types</A> &#149; "
		end if
		IF strTypeCode = "6" THEN
			' Elem
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>Elem</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=6&" & zQueryString & "'>Elem</A> &#149; "
		END IF
		IF strTypeCode = "5" or strTypeCode = "4" THEN
			' Middle/ Junior High
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>Mid/Jr Hi</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=5&" & zQueryString & "'>Mid/Jr Hi</A> &#149; "
		END IF
		IF strTypeCode = "3" THEN
			' high
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>High</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=3&" & zQueryString & "'>High</A> &#149; "
		END IF
		IF strTypeCode = "7" THEN
			' Elem
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>El/Sec</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=7&" & zQueryString & "'>El/Sec</A>  &#149; "
		END IF
	End IF
	IF strOrgLevel = "DI" THEN
		zOrgLabel = "District"
	ELSEIF strOrgLevel = "ST" THEN
		zOrgLabel = "State"
	END IF
	IF strTypeCode = "9" THEN
		' State or District Summary
		DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='" & zActiveLinkColor & "'>" & zOrgLabel & " Summary</FONT>"
	ELSE
'		'jdj - this link graying out when it shouldn't, I think 
'		'If strOrgLevel = "DI" and (zGroup <> "AllStudentsFAY" and zGroup <> "Grade") THEN
''		If strOrgLevel = "DI" and (zGroup <> "AllStudentsFAY" and zGroup <> "Grade") THEN
'			' only allow for district if all students is selected
''			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>" & zOrgLabel & " Summary</FONT>"		
''		Else
'			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=9&" & zQueryString & "'>" & zOrgLabel & " Summary</A>"
''		END IF

		' per WINSS_checking_1208051.doc, 17b
		' I assume this is graying for a good reason - building in exception for attendance - make sure don't break it elsewhere 
		if zGraphinclude = "ATTENDANCE" or zGraphinclude = "DROPOUTS" then 
			DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=9&" & zQueryString & "'>" & zOrgLabel & " Summary</A>"
		else 
			If zGroup = "Disability" THEN
				DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<font color='#bcbcbc'>" & zOrgLabel & " Summary</FONT>"		
			Else
				DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "<A HREF='graphshell.asp?STYP=9&" & zQueryString & "'>" & zOrgLabel & " Summary</A>"
			END IF
		end if 

	END IF
	DistStateSchoolTypeLinks = DistStateSchoolTypeLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Sub ChartSTypeLabels()
		Chart.Axis(AXIS_X).Label(0) = "Elem"
		Chart.Axis(AXIS_X).Label(1) = "Mid/Jr Hi"
		Chart.Axis(AXIS_X).Label(2) = "High"
		Chart.Axis(AXIS_X).Label(3) = "El/Sec"
End Sub
'''''''''''''
function ViewAllLink(zQueryString)
'ht dec13/02, scatterplot view all in table.
ViewAllLink="<TABLE><TR><TD VALIGN='TOP' class='text'>"
ViewAllLink=ViewAllLink & "<A HREF='graphshell.asp?LF=ST&" & zQueryString & "'>View All Schools' Data in Scatterplot (Text Only).</A></TD></tr></table>"
ViewAllLink=ViewAllLink & "</TD></TR></TABLE>"
end function
''''''''''''''''''''''''''''''''''''''''
Function LocationFilterLinks(zQueryString)
	LocationFilterLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Location:</TD><td class='text'>"
	If strLocation = "ST" THEN
		LocationFilterLinks = LocationFilterLinks & "<font color='" & zActiveLinkColor & "'>Entire State</FONT> &#149; "
	ELSE
		LocationFilterLinks = LocationFilterLinks & "<A HREF='graphshell.asp?LF=ST&" & zQueryString & "'>Entire State</A> &#149; "
	END IF
	If strLocation = "CE" THEN
		LocationFilterLinks = LocationFilterLinks & "<font color='" & zActiveLinkColor & "'>My CESA</FONT> &#149; "
	Else
		LocationFilterLinks = LocationFilterLinks & "<A HREF='graphshell.asp?LF=CE&" & zQueryString & "'>My CESA</A> &#149; "
	END IF
	If strLocation = "CT" THEN
		LocationFilterLinks = LocationFilterLinks & "<font color='" & zActiveLinkColor & "'>My County</FONT>"
	Else
		LocationFilterLinks = LocationFilterLinks & "<A HREF='graphshell.asp?LF=CT&" & zQueryString & "'>My County</A>"
	END IF
	LocationFilterLinks = LocationFilterLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GetLocation()
	If not isempty(Request.QueryString("LF")) THEN
		GetLocation = Request.QueryString("LF")
	ELSE
		'default to entire state
		GetLocation = "ST"
	END IF
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Function ScatterGroup2Links(zQueryString)
	ScatterGroup2Links = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show Differences In:</TD><td class='text'>" 
	If zGroup2 = "Spending" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>District Spending</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Spending&" & zQueryString & "'>District Spending</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Size" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>District Size</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Size&" & zQueryString & "'>District Size</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "EconomicStatus" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Economically Disadvantaged</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=EconomicStatus&" & zQueryString & "'>% Economically Disadvantaged</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "EnglishProficiency" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Limited English Proficient</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=EnglishProficiency&" & zQueryString & "'>% Limited English Proficient</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Disability" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Students with Disabilities</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Disability&" & zQueryString & "'>% Students with Disabilities</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Native" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Am Indian</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Native&" & zQueryString & "'>% Am Indian</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Asian" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Asian</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Asian&" & zQueryString & "'>% Asian</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Black" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Black</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Black&" & zQueryString & "'>% Black</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "Hispanic" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% Hispanic</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=Hispanic&" & zQueryString & "'>% Hispanic</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "White" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>% White</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=White&" & zQueryString & "'>% White</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & " &#149; "
	If zGroup2 = "None" THEN
		ScatterGroup2Links = ScatterGroup2Links & "<font color='" & zActiveLinkColor & "'>No option selected</FONT> "
	ELSE
		ScatterGroup2Links = ScatterGroup2Links & "<A HREF='graphshell.asp?Group2=None&" & zQueryString & "'>No option selected</A> "
	END IF
	ScatterGroup2Links = ScatterGroup2Links & "</TD></TR></TABLE>"
End Function
Public Sub HighLowMakerSim(zCurrEcon, zCurrSdis, zCurrLEP, zCurrSize, zCurrSpend)
	If cDBL(zCurrEcon) >= 0 and cDBL(zCurrEcon) <= 10 THEN
		zLowEcon = 0
		zHighEcon = 1600
	ELSEIf cDBL(zCurrEcon) > 10 and cDBL(zCurrEcon) <= 25 THEN
		zLowEcon = 10.01
		zHighEcon = 1600
	ELSEIf cDBL(zCurrEcon) > 25 and cDBL(zCurrEcon) <= 50 THEN
		zLowEcon = 25.01
		zHighEcon = 1600
	ELSEIf cDBL(zCurrEcon) > 50 and cDBL(zCurrEcon) <= 75 THEN
		zLowEcon = 50.01
		zHighEcon = 1600
	ELSEIf cDBL(zCurrEcon) > 75 THEN
		zLowEcon = 75.01
		zHighEcon = 1600
	End IF
	If cDBL(zCurrSdis) >= 0 and cDBL(zCurrSdis) <= 10 THEN
		zLowDisability = 0
		zHighDisability = 1600
	Elseif cDBL(zCurrSdis) > 10 and cDBL(zCurrSdis) <= 25 THEN
		zLowDisability = 10.01
		zHighDisability = 1600
	Elseif cDBL(zCurrSdis) > 25 and cDBL(zCurrSdis) <= 50 THEN
		zLowDisability = 25.01
		zHighDisability = 1600
	Elseif cDBL(zCurrSdis) > 50 THEN
		zLowDisability = 50.01
		zHighDisability = 1600
	End IF
	IF cDBL(zCurrLEP) >= 0 and cDBL(zCurrLEP) <= 10 THEN
		zLowLEP = 0
		zHighLEP = 1600
	ELSEIF cDBL(zCurrLEP) > 10 and cDBL(zCurrLEP)  <= 25 THEN
		zLowLEP = 10.01
		zHighLEP = 1600
	ELSEIF cDBL(zCurrLEP) > 25 and cDBL(zCurrLEP) <= 50 THEN
		zLowLEP = 25.01
		zHighLEP = 1600
	ELSEIF cDBL(zCurrLEP) > 50 THEN
		zLowLEP = 50.01
		zHighLEP = 1600
	End IF
	IF cDBL(zCurrSize) >= 0 and cDBL(zCurrSize) <= 500 THEN
		zLowSize = 0
		zHighSize = 500
	ELSEIF cDBL(zCurrSize) > 500 and cDBL(zCurrSize)  <= 1000 THEN
		zLowSize = 501
		zHighSize = 1000
	ELSEIF cDBL(zCurrSize) > 1000 and cDBL(zCurrSize) <= 2000 THEN
		zLowSize = 1001
		zHighSize = 2000
	ELSEIF cDBL(zCurrSize) > 2000 and cDBL(zCurrSize) <= 10000 THEN
		zLowSize = 2001
		zHighSize = 10000
	ELSEIF cDBL(zCurrSize) > 10000 THEN
		zLowSize = 10001
		zHighSize = 1000000
	End IF

	IF cDBL(zCurrSpend) >= 0 and cDBL(zCurrSpend) <= 7000 THEN
		zLowSpend = 0
		zHighSpend = 7000
	ELSEIF cDBL(zCurrSpend) > 7000 and cDBL(zCurrSpend)  <= 8000 THEN
		zLowSpend = 0
		zHighSpend = 8000
	ELSEIF cDBL(zCurrSpend) > 8000 and cDBL(zCurrSpend) <= 10000 THEN
		zLowSpend = 0
		zHighSpend = 10000
	ELSEIF cDBL(zCurrSpend) > 10000 THEN
		zLowSpend = 0
		zHighSpend = 1000000
	End IF

End Sub
''''''''''''''''''''''''''''''''''''''''
Sub DetailSimilarWKCERowviaView(zWhichRow, zRecordset)
	zDetailTable = zDetailTable & _ 
		"<TR><TD VALIGN='TOP'><span class='text'>"  & zWhichRow &  "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		If lSpend = "Y" THEN
			zTempSpend = FormatCurrency(zRecordset("Cost per Member"),0)
			zDetailTable = zDetailTable & zTempSpend
			zDetailTable = zDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		END IF
		If lSize = "Y" THEN
			zTempDistSize = FormatNumber(zRecordset("District Size"),0)
			zDetailTable = zDetailTable & zTempDistSize
			zDetailTable = zDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		END IF
		IF WKCESuppressed(zRecordset("Enrolled")) = "NO" THEN
			zDetailTable = zDetailTable & zRecordset("Enrolled") & " "
		Else
			zDetailTable = zDetailTable & WKCESuppressed(zRecordset("Enrolled"))
		END IF
		zDetailTable = zDetailTable & "</span></TD>" & _ 
		"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		IF lEcon = "Y" THEN
			zEconPCT = FormatNumber(zRecordset("PCTECON"),1)
			zDetailTable = zDetailTable & zEconPCT
			zDetailTable = zDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		END IF
		IF lDisability = "Y" THEN
			zDisabilityPCT = FormatNumber(zRecordset("PctDisabled"),1)
			zDetailTable = zDetailTable & zDisabilityPCT
			zDetailTable = zDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		END IF
		IF lLEP = "Y" THEN
			zLEPPCT = FormatNumber(zRecordset("PctLEP"),1)
			zDetailTable = zDetailTable & zLEPPCT
			zDetailTable = zDetailTable & "</span></TD>" & _ 
			"<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>"
		END IF
' jdj: start of advanced + proficient column
Select Case zSortBy
Case "AP"
		IF WKCESuppressed(zRecordset("PCTAdv")) = "NO" or WKCESuppressed(zRecordset("PCTprf")) = "NO" THEN
			zAddedValue = (cLng(zRecordSet("PCTprf")) + cLng(zRecordset("PCTadv"))) 
			If zAddedValue > 100 THEN
				zAddedValue = "100"
			END IF
			zDetailTable = ZDetailTable & zAddedValue & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressedAdded((cLng(zRecordSet("PCTprf")) + cLng(zRecordset("PCTadv"))))
		END IF
CASe "A"
		IF WKCESuppressed(zRecordset("PCTAdv")) = "NO" THEN
			zDetailTable = ZDetailTable & zRecordset("PCTadv") & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressed(zRecordset("PCTAdv"))
		END IF
CASE "APB"
		IF WKCESuppressed(zRecordset("PCTAdv")) = "NO" or WKCESuppressed(zRecordset("PCTprf")) = "NO" or WKCESuppressed(zRecordset("PCTbas")) = "NO" THEN
			zAddedValue = (cLng(zRecordSet("PCTprf")) + cLng(zRecordset("PCTadv"))+ cLng(zRecordset("PCTbas"))) 
			If zAddedValue > 100 THEN
				zAddedValue = "100"
			END IF
			zDetailTable = ZDetailTable & zAddedValue & "%"
		ELSE
			zDetailTable = ZDetailTable & WKCESuppressedAdded((cLng(zRecordSet("PCTprf")) + cLng(zRecordset("PCTadv")) + cLng(zRecordset("PCTbas")) ))
		END IF
END SELECT
		zDetailTable = ZDetailTable & "</span></TD></TR>" 
END SUB
Public Sub HighLowMakerSimwithFilter(zCurrEcon, zCurrSdis, zCurrLEP, zCurrSize, zCurrSpend)
	If cDBL(zCurrEcon) >= 0 and cDBL(zCurrEcon) <= 10 THEN
		zLowEcon = 0
		zHighEcon = 10
	ELSEIf cDBL(zCurrEcon) > 10 and cDBL(zCurrEcon) <= 25 THEN
		zLowEcon = 10.01
		zHighEcon = 25
	ELSEIf cDBL(zCurrEcon) > 25 and cDBL(zCurrEcon) <= 50 THEN
		zLowEcon = 25.01
		zHighEcon = 50
	ELSEIf cDBL(zCurrEcon) > 50 and cDBL(zCurrEcon) <= 75 THEN
		zLowEcon = 50.01
		zHighEcon = 75
	ELSEIf cDBL(zCurrEcon) > 75 THEN
		zLowEcon = 75.01
		zHighEcon = 100
	End IF
	If cDBL(zCurrSdis) >= 0 and cDBL(zCurrSdis) <= 10 THEN
		zLowDisability = 0
		zHighDisability = 10
	Elseif cDBL(zCurrSdis) > 10 and cDBL(zCurrSdis) <= 25 THEN
		zLowDisability = 10.01
		zHighDisability = 25
	Elseif cDBL(zCurrSdis) > 25 and cDBL(zCurrSdis) <= 50 THEN
		zLowDisability = 25.01
		zHighDisability = 50
	Elseif cDBL(zCurrSdis) > 50 THEN
		zLowDisability = 50.01
		zHighDisability = 100
	End IF
	IF cDBL(zCurrLEP) >= 0 and cDBL(zCurrLEP) <= 10 THEN
		zLowLEP = 0
		zHighLEP = 10
	ELSEIF cDBL(zCurrLEP) > 10 and cDBL(zCurrLEP)  <= 25 THEN
		zLowLEP = 10.01
		zHighLEP = 25
	ELSEIF cDBL(zCurrLEP) > 25 and cDBL(zCurrLEP) <= 50 THEN
		zLowLEP = 25.01
		zHighLEP = 50
	ELSEIF cDBL(zCurrLEP) > 50 THEN
		zLowLEP = 50.01
		zHighLEP = 100
	End IF
	IF cDBL(zCurrSize) >= 0 and cDBL(zCurrSize) <= 500 THEN
		zLowSize = 0
		zHighSize = 500
	ELSEIF cDBL(zCurrSize) > 500 and cDBL(zCurrSize)  <= 1000 THEN
		zLowSize = 501
		zHighSize = 1000
	ELSEIF cDBL(zCurrSize) > 1000 and cDBL(zCurrSize) <= 2000 THEN
		zLowSize = 1001
		zHighSize = 2000
	ELSEIF cDBL(zCurrSize) > 2000 and cDBL(zCurrSize) <= 10000 THEN
		zLowSize = 2001
		zHighSize = 10000
	ELSEIF cDBL(zCurrSize) > 10000 THEN
		zLowSize = 10001
		zHighSize = 1000000
	End IF

	IF cDBL(zCurrSpend) >= 0 and cDBL(zCurrSpend) <= 7000 THEN
		zLowSpend = 0
		zHighSpend = 7000
	ELSEIF cDBL(zCurrSpend) > 7000 and cDBL(zCurrSpend)  <= 8000 THEN
		zLowSpend = 7000.01
		zHighSpend = 8000
	ELSEIF cDBL(zCurrSpend) > 8000 and cDBL(zCurrSpend) <= 10000 THEN
		zLowSpend = 8000.01
		zHighSpend = 10000
	ELSEIF cDBL(zCurrSpend) > 10000 THEN
		zLowSpend = 10000.01
		zHighSpend = 10000000
	End IF

End Sub
''''''''''''''''''''''''''''''''''''''''
FUNCTION ParseTempQS(zInputString, strQS, strValue)
	lfound = false
	do while inSTR(zInputString,"=") > 0
		zItem = mid(zInputString,1,InSTR(zInputString,"=")-1)
		''response.write(zItem & "<BR>")
		zInputString = mid(zInputString,(InSTR(zInputString,"=") + 1))
		If inSTR(zInputString,"&") > 0 THEN
			zCurrentVal = mid(zInputString,1,InSTR(zInputString,"&")-1)
		Else
			zCurrentVal = mid(zInputString,1)
		END IF
		if LCase(zItem) <> LCase(strQS) then
			' don't change it...
	   		ParseTempQS = ParseTempQS & (zItem & "=" & zCurrentVal & "&")
		Else
			' replace with the new value
			lfound = true
	    	ParseTempQS = ParseTempQS & (UCase(strQS) & "=" & UCase(strValue) & "&")
		End IF
		zInputString = mid(zInputString,(InSTR(zInputString,"&") + 1))
	loop
	If not lfound then
		ParseTempQS = ParseTempQS & (UCase(strQS) & "=" & UCase(strValue) & "&")
	END IF
	' chop trailing ampersand
	if right(ParseTempQS,1) = "&" then 
		ParseTempQS = mid(ParseTempQS, 1, (len(ParseTempQS)-1))
	end if
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function GenCompareToLinksNew(zQueryString)
	GenCompareToLinksNew = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
	IF zCompareTo = "PRIORYEARS" THEN
		GenCompareToLinksNew = GenCompareToLinksNew & "<font color='" & zActiveLinkColor & "'>Prior Years</FONT> &#149; "
	ELSE
		GenCompareToLinksNew = GenCompareToLinksNew & "<A HREF='graphshell.asp?CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A> &#149; "
	END IF
	'IF zCompareTo = "DISTSTATE" THEN
		'if strOrgLevel<>"ST" then
		'GenCompareToLinksNew = GenCompareToLinksNew & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
		'else
		'GenCompareToLinksNew = GenCompareToLinksNew & "<font color='" & zActiveLinkColor & "'>Current State Data </FONT> &#149; "
		'end if
	'ELSE
		'ht Feb 5/02: changed wording from District/State to Current Data Only
		'if strOrgLevel<>"ST" then
		'GenCompareToLinksNew = GenCompareToLinksNew & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
		'else
		'GenCompareToLinksNew = GenCompareToLinksNew & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>Current State Data</A> &#149; "
		'end if
	'END IF
	IF zCompareTo = "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
		GenCompareToLinksNew = GenCompareToLinksNew & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
	ELSEIF zCompareTo <> "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
		GenCompareToLinksNew = GenCompareToLinksNew & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
	END IF
    ' adding Orglevel test for 11/2001
	If zGroup = "Disability" Then
		GenCompareToLinksNew = GenCompareToLinksNew & "<font color='#bcbcbc'>Selected Schools</FONT>"
	Elseif strOrgLevel = "ST" THEN
		GenCompareToLinksNew = GenCompareToLinksNew & "<font color='#bcbcbc'>Selected Districts</FONT>&#149;"&"<font color='#bcbcbc'>Selected Schools</FONT>"
	ELSE
		IF zCompareTo = "SELSCHOOLS" THEN
			GenCompareToLinksNew = GenCompareToLinksNew & "<font color='" & zActiveLinkColor & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</FONT> "
		ELSE
			IF zGraphInclude <> "STAFF" and zGraphInclude <> "MONEY" and zGraphInclude <> "LEP" THEN
				GenCompareToLinksNew = GenCompareToLinksNew & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
			ELSEif zGraphInclude = "MONEY" THEN
				GenCompareToLinksNew = GenCompareToLinksNew & "<font color='#bcbcbc'>Selected Districts</FONT>"
			Else
				GenCompareToLinksNew = GenCompareToLinksNew & "<font color='#bcbcbc'>Selected Schools</FONT>"
			END IF
		END IF
	END IF
	if strOrgLevel <> "ST" then 
		IF zCompareTo <> "CURRENTONLY" then 
			GenCompareToLinksNew = GenCompareToLinksNew & " &#149; <A HREF='graphshell.asp?CompareTo=CURRENTONLY&" & zQueryString & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data</a>"
		else 
			GenCompareToLinksNew = GenCompareToLinksNew & " &#149; <font color='" & zActiveLinkColor & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
		end if
	else 
		GenCompareToLinksNew = GenCompareToLinksNew & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	end if
'	GenCompareToLinksNew = GenCompareToLinksNew & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	GenCompareToLinksNew = GenCompareToLinksNew & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function DIGroup5Suppressed()
	Set CheckRS = Conn.Execute("Select PCTAdv from WKCE where Year = '" & Application("WkceYear") & "' and Fullkey = '" & strFullkeySQL & "' and Grade = '" & zGrade & "' and GroupNum = '5' and SubjectID = '" & zSubjectID & "';" )
	If not CheckRS.EOF THEN
		If cDBL(CheckRS("PCTADV")) < 0 THEN
			DIGroup5Suppressed = true
		Else
			DIGroup5Suppressed = false
		END IF
	Else
		DIGroup5Suppressed = true
	END IF
	CheckRS.close
	Set CheckRS = nothing
END Function
''''''''''''''''''''''''''''''''''''''''
Sub RounditUp(zRS, zChartSeries)
	zAddit = 0
	'No WSAS bar
	IF cDBL(zRS("PCTNotTested")) >= 0 THEN
		If cINT(zRS("Year")) <= 1999 THEN
			IF zEligibleOnly = "NO" THEN
				zAddit = zAddit + cDBL(zRS("PCTNotTested")) + cDBL(zRS("PctExcluded"))
			ELSE
				zAddit = zAddit + cDBL(zRS("PCTNotTested"))
			END IF
		ELSE
			zAddit = zAddit + cDBL(zRS("PCTNotTested"))
		END IF
	END IF
	'Bar for Pre-Req skill/Eng
	IF zEligibleOnly = "NO" and cINT(zRS("year")) >= 2000 THEN
		IF WKCESuppressed(zRS("PctExcluded")) = "NO" THEN
			IF cDBL(zRS("PCTExcluded")) >= 0 THEN
				zAddit = zAddit + cDBL(zRS("PCTExcluded"))
			END IF
		END IF
	END IF
	IF cDBL(zRS("PCTMin")) >= 0 THEN
		zAddit = zAddit + cDBL(zRS("PCTMin"))
	END IF
	IF cDBL(zRS("PCTBas")) >= 0 THEN
		zAddit = zAddit + cDBL(zRS("PCTBas"))
	END IF
	IF cDBL(zRS("PCTPrf")) >= 0 THEN
		zAddit = zAddit + cDBL(zRS("PCTPrf"))
	END IF
	IF cDBL(zRS("PCTAdv")) >= 0 THEN
		zAddit = zAddit + cDBL(zRS("PCTAdv"))
	END IF
	If cDBL(zAddit) <> 100 THEN
		IF cDBL(zRS("PCTNotTested")) > 0 THEN
			WKCERoundError = "NT"
		ElseIF cDBL(zRS("PCTExcluded")) > 0 THEN
			' is it excluded?
			IF zEligibleOnly = "NO" and cINT(zRS("year")) >= 2000 THEN
				IF WKCESuppressed(zRS("PctExcluded")) = "NO" THEN
					WKCERoundError = "EXC"
				END IF
			ELSE
				' EXCLUDED Was included with Not Tested then
				WKCERoundError = "NT"
			END IF
		ELSEIF cDBL(zRS("PCTMin")) > 0 THEN
			WKCERoundError = "MIN"
		ELSEIF cDBL(zRS("PCTBas")) > 0 THEN
			WKCERoundError = "BAS"
		ELSEIF cDBL(zRS("PCTPrf")) > 0 THEN
			WKCERoundError = "PRF"
		ELSEIF cDBL(zRS("PCTAdv")) > 0 THEN
			WKCERoundError = "ADV"
		END IF
	ELSE
		WKCERoundError = "NONE"
	END IF
	If WKCERounderror <> "NONE" THEN
		If cDBL(zAddit) = 101 THEN
			zAdd = -1
		ELSEIf cDBL(zAddit) >= 99 THEN
			zAdd = 1
		ELSEIF cDBL(zAddit) >= 98 THEN
			zAdd = 2
		ELSEIF cDBL(zAddit) >= 97 THEN
			zAdd = 3
		ELSEIF cDBL(zAddit) >= 96 THEN
			zAdd = 4
		ELSEIF cDBL(zAddit) >= 95 THEN
			zAdd = 5
		END IF		
		Select Case WKCERoundError
		Case "EXC"
			Chart.ValueEx(4, zChartSeries) = (cDBL(zRS("PCTExcluded")) + zAdd)
		Case "NT"
			IF zEligibleOnly = "NO" and cint(zRS("year")) >= 2000 THEN
				Chart.ValueEx(5, zChartSeries) = (cDBL(zRS("PCTNotTested")) + cDBL(zRS("PCTExcluded")) + zAdd)			
			ELSE
				Chart.ValueEx(5, zChartSeries) = (cDBL(zRS("PCTNotTested")) + zAdd)
			END IF
		Case "ADV"
			Chart.ValueEx(0, zChartSeries) = (cDBL(zRS("PCTAdv")) + zAdd)
		Case "MIN"
			Chart.ValueEx(3, zChartSeries) = (cDBL(zRS("PCTMin")) + zAdd)
		Case "BAS"
			Chart.ValueEx(2, zChartSeries) = (cDBL(zRS("PCTBas")) + zAdd)
		CASE "PRF"
			Chart.ValueEx(1, zChartSeries) = (cDBL(zRS("PCTPrf")) + zAdd)
		END Select
	END IF
End Sub
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function GetFullkeyDISTRICTList()
' 11/2001 code
	GetFullkeyDISTRICTList = "'" & left(strFullKeySQL,6) & "03XXXX'"
	If not isempty(trim(Session("sSchool4ID"))) and Session("sSchool4ID") <> "zz" THEN
		GetFullkeyDISTRICTList = GetFullkeyDISTRICTList & ",'" & left(Session("sSchool4ID"),6) & "03XXXX'"
	END IF
	If not isempty(trim(Session("sSchool3ID"))) and Session("sSchool3ID") <> "zz"  THEN
		GetFullkeyDISTRICTList = GetFullkeyDISTRICTList & ",'" & left(Session("sSchool3ID"),6) & "03XXXX'"
	END IF
	If not isempty(trim(Session("sSchool2ID"))) and Session("sSchool2ID") <> "zz" THEN
		GetFullkeyDISTRICTList = GetFullkeyDISTRICTList & ",'" & left(Session("sSchool2ID"),6) & "03XXXX'"
	END IF
	If not isempty(trim(Session("sSchool1ID"))) and Session("sSchool1ID") <> "zz"  THEN
		GetFullkeyDISTRICTList = GetFullkeyDISTRICTList & ",'" & left(Session("sSchool1ID"),6) & "03XXXX'"
	END IF
End Function
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function DistStateNameGrad(zFullkey, zGraderange)
	IF trim(zFullkey) = Session("Fullkey") THEN
		if strOrgLevel="SC" then
			DistStateNameGrad = "Current School"
		elseif strOrgLevel="DI" then
			DistStateNameGrad = "District" & SchoolTypeName(strTypecode, zGradeRange)
		else
		
			DistStateNameGrad = "Entire State"  &  SchoolTypeName(strTypecode, zGradeRange)
		end if
	ELSEIF right(zFullkey,6) = "03XXXX" THEN
		IF cINT(zGraderange) > 64 THEN
			If zGroup = "Grade" THEN
				DistStateNameGrade = Session("DistrictName")
			ELSE
				IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
					DistStateNameGrade = Session("DistrictName")
				ELSE
					DistStateNameGrade = Session("DistrictName") &  SchoolTypeName(strTypecode, zGradeRange)
				END IF
			END IF
		ELSE
			DistStateNameGrade = Session("DistrictName")
		END IF
	ELSEIF trim(zFullkey) = "XXXXXXXXXXXX" THEN
		IF cINT(zGraderange) > 64 THEN
			If zgroup <> "Grade" THEN
				' fixing table title for ggradrate
				IF Request.QueryString("Graphfile") = "GGRADRATE" and zCompareTO = "DISTSTATE" THEN
					DistStateNameGrade = "State"
				ELSE
					DistStateNameGrade = "State"  &  SchoolTypeName(strTypecode, zGradeRange)
				END IF
			ELSE
				DistStateNameGrade = "State"
			END IF
		ELSE
			DistStateNameGrade = "State"
		END IF
	END IF
END Function
''''''''''''''''''''''''''''''''''''''''
FUNCTION ACT_APlinks(ZQueryString)
	ACT_APlinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	' jdj: graying out ACT links until data is right
	' also changed question on performance.asp to default to AP
		'If zGraphinclude = "ACT" THEN
			'ACT_APlinks = ACT_APlinks & "<FONT COLOR='" & zActiveLinkColor & "'>ACT</FONT> &#149; " & _ 
				'"<A HREF='graphshell.asp?GRAPHFILE=AP&" & zQueryString & "'>Advanced Placement Exam</A>"
		'ELSEIF zGraphinclude = "AP" THEN
			'ACT_APlinks = ACT_APlinks & "<A HREF='graphshell.asp?GRAPHFILE=ACT&" & zQueryString & "'>ACT</A> &#149; " & _ 
				'"<font color='" & zActiveLinkColor & "'>Advanced Placement Exam</FONT>"
		'END IF
		'test
		If zGraphinclude = "ACT" THEN
			ACT_APlinks = ACT_APlinks & "<FONT COLOR='" & zActiveLinkColor & "'>ACT</FONT> " 
		ELSE
			ACT_APlinks = ACT_APlinks  &  "<A HREF='graphshell.asp?GRAPHFILE=ACT&" & zQueryString & "'>ACT</A>"
		END IF
		ACT_APlinks = ACT_APlinks & " &#149; "
		IF zGraphinclude = "AP" THEN
			ACT_APlinks = ACT_APlinks & "<FONT COLOR='" & zActiveLinkColor & "'>Advanced Placement Program&reg; Exams</FONT>" 
		else
			ACT_APlinks = ACT_APlinks  &  "<A HREF='graphshell.asp?GRAPHFILE=AP&" & zQueryString & "'>Advanced Placement Program&reg; Exams</A>"
		end if
	ACT_APlinks = ACT_APlinks & "</TD></tr></TABLE>"
END FUNCTION
''''''''''''''''''''''''''''''''''''''''
Function CourseGradeLinks(ZQueryString)
CourseGradeLinks = CourseGradeLinks & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Grades:</TD><td class='text'>"

	IF Session("HasG6") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		IF zGrade = "40" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 6</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=40&" & zQueryString & "'>Grade 6</A>"
		END IF
	END IF
	IF Session("HasG7") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		IF zGrade = "44" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 7</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=44&" & zQueryString & "'>Grade 7</A>"
		END IF
	END IF
	IF Session("HasG8") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		If zGrade = "48" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 8</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=48&" & zQueryString & "'>Grade 8</A>"
		END IF
	END IF
	IF Session("HasG9") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		If zGrade = "52" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 9</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=52&" & zQueryString & "'>Grade 9</A>"
		END IF
	END IF
	IF Session("HasG10") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		If zGrade = "56" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 10</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=56&" & zQueryString & "'>Grade 10</A>"
		END IF
	END IF
	IF Session("HasG11") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		If zGrade = "60" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 11</FONT>"
		Else
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=60&" & zQueryString & "'>Grade 11</A>"
		END IF
	END IF
	IF Session("HasG12") = "T" THEN
		CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
		If zGrade = "64" THEN
			CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Grade 12</FONT>"
		ELSE
			CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=64&" & zQueryString & "'>Grade 12</A>"
		END IF
	END IF
	CourseGradeLinks = CourseGradeLinks & AddBulletCourse(CourseGradeLinks)
	IF zGrade = "94" THEN
		CourseGradeLinks = CourseGradeLinks & " <font color='" & zActiveLinkColor & "'>Summary Grades 6-12</A>"
	ELSE
		CourseGradeLinks = CourseGradeLinks & " <A HREF='graphshell.asp?Grade=94&" & zQueryString & "'>Summary Grades 6-12</A>"
	END IF
	CourseGradeLinks = CourseGradeLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Sub TableFromSQL2Rowspans(zRS, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	If nodata = false then
		zRS.movefirst
		zDetailTable = "<table width='460' border='1' cellpadding='2'><TR>"
		zDetailTable = zDetailTable & "<TD colspan='" & zRS.Fields.Count & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & BrMaker(zGraphTitle) & "</span></TD></TR><TR>"
		MaxColumn = zRS.Fields.Count - 1
		For i = 0 To MaxColumn
		  	zDetailTable = zDetailTable & "<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & zRS.Fields(i).name & "</span></TD>"
		Next
		zDetailTable = zDetailTable & "</TR>"
		zFirstColHold = trim(zRS.Fields(0).Value)
		zSecondColumnHold = trim(trim(zRS.Fields(1).Value))
		zSpanRow = 0 
		zSpanRow2 = 0
		Do while Not zRS.EOF
			If trim(zFirstColHold) = trim(zRS.Fields(0).Value) THEN
				zSpanRow = zSpanRow + 1
				zFirstColHold = trim(zRS.Fields(0).Value)
			Else
				exit do
			END IF
			zRS.movenext
		Loop
		zRS.movefirst
		Do while Not zRS.EOF
			If trim(zSecondColumnHold) = trim(zRS.Fields(1).Value) THEN
				zSpanRow2 = zSpanRow2 + 1
				zSecondColumnHold = trim(zRS.Fields(1).Value)
			Else
				exit do
			END IF
			zRS.movenext
		Loop
		zRS.movefirst
		' jdj: client wants repeating data in second column to get a superlabel, to match the superlabel in the first column
		' but superlabel can break the table if data in second column repeats across more rows than does the superlabel in the first column
		' zFirstColIsNewCell (below) forces creation of a new cell in the second column if there's a new cell in the first column 
		' repeating cells in second column will get a superlabel, but no bigger than the superlabel to the left of it 
		' zSpanRow2 = zSpanRow (below) gives rowspan support for this
		if cInt(zSpanRow2) > cInt(zSpanRow) then
			zSpanRow2 = zSpanRow
		end if 

		zFirstColHold = ""
		zSecondColHold = ""
		Do While Not zRS.EOF
	    	zDetailTable = zDetailTable & "<TR>"
			zFirstColIsNewCell = "false"
			For i = 0 To MaxColumn
				zDisplayMe = "<span class='text'>" & FormatTableCol(zRS, i, ColumnFormatArray(i)) & "</span>"
				' jdj - adding switch to turn off superlabel
				If i = 0 and zSuperLabelTable1 <> "false" THEN
					If trim(zFirstColHold) <> trim(zRS.Fields(0).Value) THEN
					    zDetailTable = zDetailTable & "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>"
						zFirstColIsNewCell = "true"
					END IF
					zFirstColHold = trim(zRS.Fields(0).Value)
				' jdj - adding switch to turn off superlabel
				ELSEIF i = 1 and zSuperLabelTable2 <> "false" THEN
					If (trim(zSecondColHold) <> trim(zRS.Fields(1).Value)) or zFirstColIsNewCell = "true" THEN
					    zDetailTable = zDetailTable & "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow2 & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>"
					END IF
					zSecondColHold = trim(zRS.Fields(1).Value)
				ELSE
				    zDetailTable = zDetailTable & "<TD ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>"
				END IF
			Next
		    zDetailTable = zDetailTable & "</TR>"
			zRS.MoveNext
		Loop
	    zDetailTable = zDetailTable & "</TABLE>"
	END IF
END SUB
''''''''''''''''''''''''''''''''''''''''
Function CourseShowLinks(ZQueryString)
	CourseShowLinks = CourseShowLinks & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	if zGraphfile = "GCOURSEOFFER" THEN
		IF zCourseType = "5" THEN
			CourseShowLinks = CourseShowLinks & " <font color='" & zActiveLinkColor & "'>Advanced Courses by Type</FONT>"
		ELSE
			CourseShowLinks = CourseShowLinks & " <!--A HREF='graphshell.asp?COURSETYPE=1&" & zQueryString & "'>Advanced Courses by Type<!--/A>"
		END IF
	END IF
	CourseShowLinks = CourseShowLinks & AddBullet(CourseShowLinks)
	IF zCourseType = "1" THEN
		CourseShowLinks = CourseShowLinks & " <font color='" & zActiveLinkColor & "'>Advanced Placement Program&reg;</FONT>"
	ELSE
		CourseShowLinks = CourseShowLinks & " <A HREF='graphshell.asp?COURSETYPE=1&" & zQueryString & "'>Advanced Placement Program&reg;</A>"
	END IF
	CourseShowLinks = CourseShowLinks & AddBullet(CourseShowLinks)
	IF zCourseType = "2" THEN
		CourseShowLinks = CourseShowLinks & " <font color='" & zActiveLinkColor & "'>CAPP</FONT>"
	ELSE
		CourseShowLinks = CourseShowLinks & " <A HREF='graphshell.asp?COURSETYPE=2&" & zQueryString & "'>CAPP</A>"
	END IF
	CourseShowLinks = CourseShowLinks & AddBullet(CourseShowLinks)
'	IF zCourseType = "3" THEN
'		CourseShowLinks = CourseShowLinks & " <font color='" & zActiveLinkColor & "'>DPI-Defined Advanced Coursework</FONT>"
'	ELSE
'		CourseShowLinks = CourseShowLinks & " <A HREF='graphshell.asp?COURSETYPE=3&" & zQueryString & "'>DPI-Defined Advanced Coursework</A>"
'	END IF
'	CourseShowLinks = CourseShowLinks & AddBullet(CourseShowLinks)
	IF zCourseType = "6" THEN
		CourseShowLinks = CourseShowLinks & " <font color='" & zActiveLinkColor & "'>International Baccalaureate</FONT>"
	ELSE
		CourseShowLinks = CourseShowLinks & " <A HREF='graphshell.asp?COURSETYPE=6&" & zQueryString & "'>International Baccalaureate</A>"
	END IF
	CourseShowLinks = CourseShowLinks 
	CourseShowLinks = CourseShowLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function CourseShowLinksTake(ZQueryString)
	CourseShowLinksTake = CourseShowLinksTake & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Show:</TD><td class='text'>"
	if zGraphfile = "GCOURSEOFFER" THEN
		IF zCourseType = "5" THEN
			CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>Advanced Courses by Type</FONT>"
		ELSE
			CourseShowLinksTake = CourseShowLinksTake & " <!--A HREF='graphshell.asp?COURSETYPE=1&" & zQueryString & "'>Advanced Courses by Type<!--/A>"
		END IF
	END IF
	CourseShowLinksTake = CourseShowLinksTake & AddBullet(CourseShowLinksTake)
	IF zCourseType = "1" THEN
		CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>Advanced Placement Program&reg;</FONT>"
	ELSE
		CourseShowLinksTake = CourseShowLinksTake & " <A HREF='graphshell.asp?COURSETYPE=1&" & zQueryString & "'>Advanced Placement Program&reg;</A>"
	END IF
	CourseShowLinksTake = CourseShowLinksTake & AddBullet(CourseShowLinksTake)
	IF zCourseType = "2" THEN
		CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>CAPP</FONT>"
	ELSE
		CourseShowLinksTake = CourseShowLinksTake & " <A HREF='graphshell.asp?COURSETYPE=2&" & zQueryString & "'>CAPP</A>"
	END IF
	CourseShowLinksTake = CourseShowLinksTake & AddBullet(CourseShowLinksTake)
'	IF zCourseType = "3" THEN
'		CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>DPI-Defined Advanced Coursework</FONT>"
'	ELSE
'		CourseShowLinksTake = CourseShowLinksTake & " <A HREF='graphshell.asp?COURSETYPE=3&" & zQueryString & "'>DPI-Defined Advanced Coursework</A>"
'	END IF
	IF zCourseType = "6" THEN
		CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>International Baccalaureate</FONT>"
	ELSE
		CourseShowLinksTake = CourseShowLinksTake & " <A HREF='graphshell.asp?COURSETYPE=6&" & zQueryString & "'>International Baccalaureate</A>"
	END IF
	CourseShowLinksTake = CourseShowLinksTake & AddBullet(CourseShowLinksTake)
	IF zCourseType = "4" THEN
		CourseShowLinksTake = CourseShowLinksTake & " <font color='" & zActiveLinkColor & "'>Other</FONT>"
	ELSE
		CourseShowLinksTake = CourseShowLinksTake & " <A HREF='graphshell.asp?COURSETYPE=4&" & zQueryString & "'>Other</A>"
	END IF
'	CourseShowLinksTake = CourseShowLinksTake & AddBullet(CourseShowLinksTake)
'	CourseShowLinksTake = CourseShowLinksTake & " <font color='#bcbcbc'>Selected Courses (coming soon)</FONT>"
	CourseShowLinksTake = CourseShowLinksTake & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function CourseSubjLinks(ZQueryString)
'1           Agricultural Education
'2           Art and Design
'3           Business
'4           English Language Arts
'5           Family and Consumer Ed
'6           Foreign Languages
'7           Marketing Education
'8           Mathematics
'9           Music
'10          Science
'11          Social Studies
'12          Technology Education
'13          Other
	CourseSubjLinks = CourseSubjLinks & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Subject:</TD><td class='text'>"
	IF zWMAS = "4" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>English Language Arts</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=4&" & zQueryString & "'>English Language Arts</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "8" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Mathematics</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=8&" & zQueryString & "'>Mathematics</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "10" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Science</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=10&" & zQueryString & "'>Science</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "11" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Social Studies</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=11&" & zQueryString & "'>Social Studies</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "1" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Agricultural Education</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=1&" & zQueryString & "'>Agricultural Education</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "2" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Art and Design</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=2&" & zQueryString & "'>Art and Design</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "3" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Business</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=3&" & zQueryString & "'>Business</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "5" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Family and Consumer Ed</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=5&" & zQueryString & "'>Family and Consumer Ed</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "6" THEN
'		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Foreign Languages</FONT>"
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>World Languages</FONT>"
	ELSE
'		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=6&" & zQueryString & "'>Foreign Languages</A>"
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=6&" & zQueryString & "'>World Languages</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "7" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Marketing Education</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=7&" & zQueryString & "'>Marketing Education</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "9" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Music</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=9&" & zQueryString & "'>Music</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "12" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Technology Education</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=12&" & zQueryString & "'>Technology Education</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & " &#149; "
	IF zWMAS = "13" THEN
		CourseSubjLinks = CourseSubjLinks & " <font color='" & zActiveLinkColor & "'>Other</FONT>"
	ELSE
		CourseSubjLinks = CourseSubjLinks & " <A HREF='graphshell.asp?WMAS=13&" & zQueryString & "'>Other</A>"
	END IF
	CourseSubjLinks = CourseSubjLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function CourseSubjLinksOffer(ZQueryString)
'1           Agricultural Education
'2           Art and Design
'3           Business
'4           English Language Arts
'5           Family and Consumer Ed
'6           Foreign Languages
'7           Marketing Education
'8           Mathematics
'9           Music
'10          Science
'11          Social Studies
'12          Technology Education
'13          Other
	CourseSubjLinksOffer = CourseSubjLinksOffer & "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Subject:</TD><td class='text'>"
	IF zWMAS = "4" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>English Language Arts</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=4&" & zQueryString & "'>English Language Arts</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "8" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Mathematics</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=8&" & zQueryString & "'>Mathematics</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "10" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Science</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=10&" & zQueryString & "'>Science</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "11" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Social Studies</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=11&" & zQueryString & "'>Social Studies</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "2" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Art and Design</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=2&" & zQueryString & "'>Art and Design</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "6" THEN
'		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Foreign Languages</FONT>"
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>World Languages</FONT>"
	ELSE
'		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=6&" & zQueryString & "'>Foreign Languages</A>"
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=6&" & zQueryString & "'>World Languages</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "9" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Music</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=9&" & zQueryString & "'>Music</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & " &#149; "
	IF zWMAS = "13" THEN
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <font color='" & zActiveLinkColor & "'>Other</FONT>"
	ELSE
		CourseSubjLinksOffer = CourseSubjLinksOffer & " <A HREF='graphshell.asp?WMAS=13&" & zQueryString & "'>Other</A>"
	END IF
	CourseSubjLinksOffer = CourseSubjLinksOffer & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function CourseTypeName(CourseTypeID)
	Select Case CourseTypeID
	Case "0"
		CourseTypeName = "Advanced Courses By Type"
	Case "1"
		CourseTypeName = "Advanced Placement Program&reg; Courses"
	Case "2"
		CourseTypeName = "CAPP Courses"
	Case "3"
		CourseTypeName = "DPI-Defined Advanced Courses"
	Case "4"
		CourseTypeName = "Other Courses"
	Case "6"
		CourseTypeName = "International Baccalaureate Courses"
	End Select
End function
''''''''''''''''''''''''''''''''''''
Function WMASName(WMASID)
	Set WMASRS = CONN.Execute("Select Description from COURSES_WMAS_SUBJ where WMASID = '" & WMASID & "';")
	If not WMASRS.EOF THEN
		WMASName = trim(WMASRS("Description"))
	ELSE
		WMASName = "Unknown"
	END IF
	WMASRS.CLOSE
	Set WMASRS = nothing
End function
Function WRCTSelectListFields()
	Select Case zLevel
	Case "ADV"
		 WRCTSelectListFields = " [Percent Advanced] "
	CASE "PRF"
		 WRCTSelectListFields = " [Percent Proficient] "
	CASE "BAS"
		 WRCTSelectListFields = "  [Percent Basic] "
	CASE "MIN"
		 WRCTSelectListFields = " [Percent Minimal Performance]"
	CASE "A-P"
		 WRCTSelectListFields = " [Advanced + Proficient Total] "
	CASE "A-P-B"
		WRCTSelectListFields = "  [Advanced + Proficient + Basic Total] "
	CASE "NT"
		 WRCTSelectListFields = " [Percent Not Tested]"
	CASE "M-NT-wrct"
		WRCTSelectListFields = "  [Minimal Performance + Not Tested on WRCT Total]"
	CASE "NT-wrct"
		 WRCTSelectListFields = " [Percent Not Tested]"
	END SELECT
End Function
'''''''''''''''''''''''''''''''''''''''''''''''
Function WRCTProLevelsLinks(zQueryString)
	WRCTProLevelsLinks = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>Level:</TD><td class='text'>"
	IF zLevel = "ADV" THEN
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced</FONT>"
	ELSE
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=ADV&" & zQueryString & "'>Advanced</A>"
	END IF
	WRCTProLevelsLinks = WRCTProLevelsLinks & " &#149; "
	IF zLevel = "A-P" THEN
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced + Proficient</FONT>"
	ELSE
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=A-P&" & zQueryString & "'>Advanced + Proficient</A>" 
	END IF
	WRCTProLevelsLinks = WRCTProLevelsLinks & " &#149; "
	'huong: put in new link Advanced + Prof + Basic
	IF zLevel = "A-P-B" THEN
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Advanced + Proficient + Basic</FONT>"
	ELSE
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=A-P-B&" & zQueryString & "'>Advanced + Proficient + Basic</A>" 
	END IF
	WRCTProLevelsLinks = WRCTProLevelsLinks & " &#149; "
	
	' 2nd new link  / HT:comm. out 9/27/02
	IF zLevel = "M-NT-wrct" THEN
		'WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Min Perf + Pre-Req Skills/Eng + No WSAS</FONT>"
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Min Perf + Not Tested on WRCT</FONT>"
	ELSE
		'WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=M-NT&" & zQueryString & "'>Min Perf + Pre-Req Skills/Eng + No WSAS</A>" 
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=M-NT-wrct&" & zQueryString & "'>Min Perf + Not Tested on WRCT</A>" 
	END IF
	'end-HT  try 
	WRCTProLevelsLinks = WRCTProLevelsLinks & " &#149; "
	IF zLevel = "MIN" THEN
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Min Perf</FONT>"
	ELSE
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=MIN&" & zQueryString & "'>Min Perf</A>"
	END IF
	WRCTProLevelsLinks = WRCTProLevelsLinks & " &#149; "
	IF zLevel = "NT-wrct" THEN
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<FONT Color='" & zActiveLinkColor & "'>Not Tested on WRCT</FONT>"
	ELSE
		WRCTProLevelsLinks = WRCTProLevelsLinks & "<A HREF='graphshell.asp?LEVEL=NT-wrct&" & zQueryString & "'>Not Tested on WRCT</A>"
	END IF
	WRCTProLevelsLinks = WRCTProLevelsLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function ThisDistrictName(zGraphinclude)
If not isempty(Request.QueryString("zDistID")) THEN
	if zGraphinclude = "GWRCTPRIOR" THEN
		zSqlYear = Application("WRCTYear")
	else
		zSqlYear = Application("WKCEYear")
	end if
	SQL= "Select * from districts where district = '" & Request.QueryString("zDistID") & "' and year = '" & zSqlYear & "';"
	Set TempRS = conn.execute(SQL)
	IF not TempRS.EOF THEN
		ThisDistrictName = TRIM(TempRS("Name"))
	ELSE
		ThisDistrictName = "unknown"
	END IF
ELSE
	ThisDistrictName = "unknown"
END IF
End Function
'''''''''''''''''''''''''''''''''''''''
'ht 3/4/03 built only for the table in gscattertableonly.inc 
	Sub TableFromArrayScatterTable(zRS, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	zDetailTable = ""
	zRS.cachesize = 3000
	intRecordCount = zRS.RecordCount     ' set global
    intFieldCount = zRS.Fields.Count       ' set global
    'ReDim RSArray((intFieldCount - 1), (intRecordCount - 1))   ' set global
	RSArray = zRS.GetRows(zRS.RecordCount)
	Dim intMetaMax
    ' determine size of array
    intMetaMax = intFieldCount - 1 - intKeyFieldCount
    ReDim RSMetaArray(intMetaMax)  ' set global array of Data column names
    Dim i   'recordset field counter
    Dim j   'array row counter
	j=0
	For i = (intKeyFieldCount) To (intFieldCount - 1)
        'retrieve data column names and put in array
		RSMetaArray(j) = zRS.Fields(i).Name
		'ht 9/14/06
		If zGrade="99" and trim(zRS.Fields(i).Name) = "# Enrolled" Then
		  RSMetaArray(j) = " Enrolled in Tested Grade(s)"
		End If
		'end ht 9/14/06 
		j = j + 1 
    Next
  '  zRS.Close
   ' Set zRS = Nothing
	If nodata = false then
		response.write("<table width='460' border='1' cellpadding='2'>")
		response.write("<TR><TD colspan='" & (intFieldCount+1) & "'  ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & BrMaker(zGraphTitle) & " </span></TD></TR>")
		if zGraphinclude="SCATTERTABLEONLY" and zEligibleOnly="no" then
			'zBanner= "WKCE -- All Students Eligibles FAY  Grade " & zgrade 'hard code for grade 10 now. May have to use zGrade later
			zBanner= zWKCEOrWSAS & " -- All Students Eligibles FAY " '& zgrade 'hard code for grade 10 now. May have to use zGrade later
			
		else
			'zBanner= "WKCE -- All Students Enrolled FAY Grade " & zgrade
			zBanner= zTableSubtitle & " -- All Students Enrolled FAY " '& zgrade
		end if
        If zGrade="99" Then 'ht 9/14/06
		    zBanner = zBanner & " Tested Grades Combined "
		Else
		    zBanner = zBanner & " Grade " & zgrade
		End If
			' brb correcting logic here for all possible combinations 4/03
			intDistrictLevelColumns = 0 
			response.write("<TR><TD>&nbsp;</TD>")
			if zRel="Spending" or zgroup2 = "Spending" then
				intDistrictLevelColumns = intDistrictLevelColumns + 1
				response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'> District Spending</span></TD>")
				ColumnFormatArray(1)="CUR"
			END IF
			if zRel="Size" or zgroup2 = "Size"  then
				intDistrictLevelColumns = intDistrictLevelColumns + 1
				response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>District Size</span></TD>")
				ColumnFormatArray(intDistrictLevelColumns +1)="NUM"
			END IF

			ColumnFormatArray(intDistrictLevelColumns +1)="NUM"
			ColumnFormatArray(intDistrictLevelColumns +2)="PERC"

			response.write("<TD colspan='" & ((intFieldCount-1)-cINT(intDistrictLevelColumns)) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR>")
			' end brb corrections
			' keeping the section below to show what was changed above
			'if zRel="Spending" and zgroup2<>"Spending" and zgroup2<>"Size" then
			'	response.write("<TD>&nbsp;</TD><TD><span class='text'> District " &zrel& " </span></TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="CUR"
			'	ColumnFormatArray(2)="NUM"
			'elseif zRel="Size" and zgroup2<>"Spending" and zgroup2<>"Size"  then
			'	response.write("<TD>&nbsp;</TD><TD><span class='text'>District " &zrel& "</span></TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="NUM"
			'	ColumnFormatArray(2)="NUM"
			'elseif  zRel<>"Spending" and zRel<>"Size" then
			'	if zGroup2="Spending" then
			'		response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'		ColumnFormatArray(1)="CUR"
			'		ColumnFormatArray(2)="NUM"
			'	elseif zGroup2="Size" then 'ht mar 30/03
			'		response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'		ColumnFormatArray(1)="NUM"
			'		ColumnFormatArray(2)="NUM"
			'	elseif  zGroup2<>"Spending" and zgroup2<>"Size" then 'ht mar 30/03
			'		response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'		ColumnFormatArray(1)="NUM"
			'	end if
			'elseif  zRel="Spending" and zGroup2="Spending" then
			'	response.write("<TD>&nbsp;</TD><TD><span class='text'>District " &zrel& "</span></TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="CUR"
			'	ColumnFormatArray(2)="NUM"
			'elseif zRel=zgroup2 then
			'	if zRel="Size" or zRel="Spending" then
			'		response.write("<TD>&nbsp;</TD><TD><span class='text'>District " &zrel& "</span></TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	else
			'		response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	end if
			'	if zRel="Spending" then
			'		ColumnFormatArray(1)="CUR"
			'	else
			'		ColumnFormatArray(1)="NUM"
			'	end if
			'elseif zRel="Spending" and zgroup2="Size" then
			'	response.write("<TD>&nbsp;</TD><TD><span class='text'>District " &zrel& "</span></TD><TD><span class='text'>District " &zgroup2& "</span></TD><TD colspan='" & (intFieldCount-2) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="CUR"
			'	ColumnFormatArray(2)="NUM"
			'elseif zgroup2="Spending" and zrel="Size" then
			'	response.write("<TD>&nbsp;</TD><TD><span class='text'>District " &zrel& "</span></TD><TD><span class='text'>District " &zgroup2& "</span></TD><TD colspan='" & (intFieldCount-2) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="NUM"
			'	ColumnFormatArray(2)="CUR"
			'else
			'	response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
			'	ColumnFormatArray(1)="NUM"
			'	ColumnFormatArray(2)="NUM"
			'end if
			' end brb corrections
		'end ht mar4/03
		For i = 0 To intFieldCount-1
		  	response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & RSMetaArray(i) & "</span></TD>")
		Next
		response.write("</TR>")
		zFirstColHold = trim(RSArray(0,0))
		zSpanRow = 0
		For i = 0 to (intRecordCount - 1)
			If trim(zFirstColHold) = trim(RSArray(i,0)) THEN
				zSpanRow = zSpanRow + 1
				zFirstColHold = trim(RSArray(i,0))
			Else
				exit for
			END IF
		Next
		zFirstColHold = ""
		For r = 0 to (intRecordCount - 1)
	    	response.write( "<TR>")
			For i = 0 To intFieldCount-1
				'jdj: -10 showing in table - must double-check for suppression here
				if i > 1 and left(cStr(FormatTableColfromArray(RSArray, i, r, ColumnFormatArray(i))),3) = "-10" then 
					zDisplayMe = "<span class='text'>*</span>"
				else
'					' jdj: overzealous formatting routine is adding % to enrollment column - arbitrarily overriding based on the fact that it's the third column 
'					if i = 2 then 
'						zDisplayMe = "<span class='text'>" & FormatTableColfromArray(RSArray, i, r, "NUM") & "</span>"
'					else 
						zDisplayMe = "<span class='text'>" & FormatTableColfromArray(RSArray, i, r, ColumnFormatArray(i)) & "</span>"
'					end if 
				end if 

				If i = 0 THEN
					If trim(zFirstColHold) <> trim(RSArray(i,r)) THEN
						    response.write( "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
					END IF
					zFirstColHold = trim(RSArray(i,r))
				ELSE
					    response.write( "<TD ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
				END IF
			Next
		    response.write( "</TR>")
		NEXT
	    response.write( "</TABLE>")
	END IF
END SUB

'''''''''''''''''''''
Sub TableFromArray(zRS, HeadBGcolor, ColumnAlignArray, ColumnFormatArray)
	zDetailTable = ""
	zRS.cachesize = 3000
	intRecordCount = zRS.RecordCount     ' set global
    intFieldCount = zRS.Fields.Count       ' set global
    'ReDim RSArray((intFieldCount - 1), (intRecordCount - 1))   ' set global
    RSArray = zRS.GetRows(zRS.RecordCount)
	Dim intMetaMax
    ' determine size of array
    intMetaMax = intFieldCount - 1 - intKeyFieldCount
    ReDim RSMetaArray(intMetaMax)  ' set global array of Data column names
    Dim i   'recordset field counter
    Dim j   'array row counter
    j = 0
    For i = (intKeyFieldCount) To (intFieldCount - 1)
        'retrieve data column names and put in array
        RSMetaArray(j) = zRS.Fields(i).Name
        j = j + 1
    Next
	If nodata = false then
		response.write("<table width='460' border='1' cellpadding='2'><TR>")
		response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & BrMaker(zGraphTitle) & "</span></TD></TR><TR>")
		'ht mar 06/03 
		if zGraphinclude="SCATTERTABLEONLY" and zEligibleOnly="no" then
			zBanner= "WKCE -- All Students Eligibles FAY  Grade " & zGrade 'hard code for grade 10 now. May have to use zGrade later
		else
			zBanner= "WKCE -- All Students Enrolled FAY Grade " & zGrade
		end if
		if zGraphinclude="SCATTERTABLEONLY" then
			if zRel="Spending" and zgroup2<>"Spending" and zgroup2<>"Size" then
				response.write("<TD colspan=2 >&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="CUR"
				ColumnFormatArray(2)="NUM"
			elseif zRel="Size" and zgroup2<>"Spending" and zgroup2<>"Size"  then
				response.write("<TD colspan=2 >&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="NUM"
				ColumnFormatArray(2)="NUM"
			elseif  zRel<>"Spending" and zRel<>"Size" and zGroup2="Spending" then
				response.write("<TD colspan=2>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="CUR"
			elseif  zRel="Spending" and zGroup2="Spending" then
				response.write("<TD colspan=2>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="CUR"
			elseif  zrel<>"Spending" and zrel<>"Size" and zgroup2="Size" then
				response.write("<TD colspan=2>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="NUM"
				ColumnFormatArray(2)="NUM"
			elseif zRel=zgroup2 then
				if zRel="Size" or zRel="Spending" then
					response.write("<TD colspan=2>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				end if
				if zRel="Spending" then
					ColumnFormatArray(1)="CUR"
				else
					ColumnFormatArray(1)="NUM"
				end if
			elseif zRel="Spending" and zgroup2="Size" then
				response.write("<TD colspan = 3 >&nbsp;</TD><TD colspan='" & (intFieldCount-2) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="CUR"
				ColumnFormatArray(2)="NUM"
			elseif  zrel="Size" and zgroup2="Spending" then
				response.write("<TD colspan=3>&nbsp;</TD><TD colspan='" & (intFieldCount-2) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="NUM"
				ColumnFormatArray(2)="CUR"
			else
				response.write("<TD>&nbsp;</TD><TD colspan='" & (intFieldCount-1) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR><TR>")
				ColumnFormatArray(1)="NUM"
				ColumnFormatArray(2)="NUM"
			end if
		end if

		'end ht code for table in gscattertableonly.inc
		For i = 0 To intFieldCount-1
		  	response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & RSMetaArray(i) & "</span></TD>")
		Next
		response.write("</TR>")
		zFirstColHold = trim(RSArray(0,0))
		zSpanRow = 0
		For i = 0 to (intRecordCount - 1)
			If trim(zFirstColHold) = trim(RSArray(i,0)) THEN
				zSpanRow = zSpanRow + 1
				zFirstColHold = trim(RSArray(i,0))
			Else
				exit for
			END IF
		Next
		zFirstColHold = ""
		For r = 0 to (intRecordCount - 1)
	    	response.write( "<TR>")
			For i = 0 To intFieldCount-1
				zDisplayMe = "<span class='text'>" & FormatTableColfromArray(RSArray, i, r, ColumnFormatArray(i)) & "</span>"
				If i = 0 THEN
					If trim(zFirstColHold) <> trim(RSArray(i,r)) THEN
					    response.write( "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
					END IF
					zFirstColHold = trim(RSArray(i,r))
				ELSE
				    response.write( "<TD ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
				END IF
			Next
		    response.write( "</TR>")
		NEXT
	    response.write( "</TABLE>")
	END IF
END SUB
''''''''''''''''''''''''''
Function FormatTableColfromArray(zArray, zWhichRow, zWhichCol, zEvalString)
	Select Case zEvalString
	Case "STR"
		FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
	Case "DEC1"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),1)
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "NUM"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),0)
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "PERC"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			' jdj: below erroneously adds % to enrollment column - trying to fix
			FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),0) + "%"
			'FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),0) 
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "DEC2"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),2)
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "CUR"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray = FormatCurrency(zArray(zWhichRow, zWhichCol),0)
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "DEC1PERC"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray = FormatNumber(zArray(zWhichRow, zWhichCol),1) + "%"
		ELSE
			FormatTableColfromArray = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	End Select
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function CourseCompareToLinks(zQueryString)
	CourseCompareToLinks = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
	IF zCompareTo = "PRIORYEARS" THEN
		CourseCompareToLinks = CourseCompareToLinks & "<font color='" & zActiveLinkColor & "'>Prior Years</FONT> &#149; "
	ELSE
		CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A> &#149; "
	END IF
'	IF zCompareTo = "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
'		CourseCompareToLinks = CourseCompareToLinks & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
'	ELSEIF zCompareTo <> "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
'		CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
'	END IF
	CourseCompareToLinks = CourseCompareToLinks & "<font color='#bcbcbc'>District/State</FONT> &#149; "
    ' adding Orglevel test for 11/2001
	If zGroup = "Disability"  THEN
		CourseCompareToLinks = CourseCompareToLinks & "<font color='#bcbcbc'>Selected Schools</FONT>"
	elseif strOrgLevel = "ST" then
		CourseCompareToLinks = CourseCompareToLinks& "<font color='#bcbcbc'>Selected Districts</font> &#149; <font color='#bcbcbc'>Selected Schools</FONT>"
	ELSE
		IF zCompareTo = "SELSCHOOLS" and zGraphInclude <> "MONEY" and zGraphInclude <> "AP" THEN
			CourseCompareToLinks = CourseCompareToLinks & "<font color='" & zActiveLinkColor & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</FONT>"
		ELSEIF zCompareTo = "SELSCHOOLS" and (zGraphInclude = "MONEY" or zGraphInclude = "AP") THEN
			CourseCompareToLinks = CourseCompareToLinks & "<font color='" & zActiveLinkColor & "'>Selected Districts</FONT>"
		ELSE
			IF zGraphInclude <> "MONEY" and zGraphInclude <> "AP" and zGraphInclude <> "LEP" THEN
				'ht to delete this commemt:CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
				CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
			ELSEif zGraphInclude = "MONEY" or zGraphInclude = "AP" THEN
				'ht to delete this commemt: CourseCompareToLinks = CourseCompareToLinks & "<font color='#bcbcbc'>Selected Districts</FONT>"
				CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</a>"
			Else
				'ht to delete this commemt: CourseCompareToLinks = CourseCompareToLinks & "<font color='#bcbcbc'>Selected Schools</FONT>"
				CourseCompareToLinks = CourseCompareToLinks & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</a>"
			END IF
		END IF
	END IF
	if (zGraphInclude = "GROUPS" or zGraphInclude = "SSACTIVITIES" or zGraphInclude = "GGRADREQS" or zGraphInclude = "GCOURSEOFFER") and strOrgLevel <> "ST" then 
		IF zCompareTo <> "CURRENTONLY" then 
			CourseCompareToLinks = CourseCompareToLinks & " &#149; <A HREF='graphshell.asp?CompareTo=CURRENTONLY&" & zQueryString & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </a>"
		else 
			CourseCompareToLinks = CourseCompareToLinks & " &#149; <font color='" & zActiveLinkColor & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
		end if
	else 
		CourseCompareToLinks = CourseCompareToLinks & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	end if
	CourseCompareToLinks = CourseCompareToLinks & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function QSMorphedFromObjLinkStateAndLinkArray(objLinkStateLocal,strLinkArrayKey,strLinkArrayValue)
	QSMorphedFromObjLinkStateAndLinkArray = ""
	For Each item in objLinkStateLocal
		if lcase(cStr(item)) = lcase(strLinkArrayKey) then 
			QSMorphedFromObjLinkStateAndLinkArray = QSMorphedFromObjLinkStateAndLinkArray & item & "=" & strLinkArrayValue & "&"
		else
			QSMorphedFromObjLinkStateAndLinkArray = QSMorphedFromObjLinkStateAndLinkArray & item & "=" & objLinkStateLocal(Item) & "&"
		end if
	Next 
	' chop trailing ampersand
	if right(QSMorphedFromObjLinkStateAndLinkArray,1) = "&" then 
		QSMorphedFromObjLinkStateAndLinkArray = left(QSMorphedFromObjLinkStateAndLinkArray,len(QSMorphedFromObjLinkStateAndLinkArray)-1)
	end if
end function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function fncWrapLine(strStringToWrap,intDesiredWrapLength,strWrapType)
	' jdj 20040113: better for wrapping titles - will do VB or HTML - needs code to support multi-line wraps - now just splits one line into two 
	strWrappedString = strStringToWrap
	intDesiredWrapLengthLocal = intDesiredWrapLength
	intPositionOfSpaceAfterWrap = 1
	' should be able to do multi-line break with loop code - haven't got it yet
	'do while inStr((intDesiredWrapLengthLocal + intPositionOfSpaceAfterWrap), strWrappedString, chr(32)) > 0
	' must test if the desired wrap length is short of the last space in the string - otherwise replace() will choke
	if intDesiredWrapLength < InStrRev(zYTitle,chr(32)) then 
			if strWrapType = "VB" then
				' below is for VB break
				strWrappedString = left(strWrappedString,(inStr((intDesiredWrapLengthLocal + intPositionOfSpaceAfterWrap - 1), strWrappedString, chr(32)))) & replace(strWrappedString,chr(32),(chr(32) & vbCrLf),(inStr(intDesiredWrapLengthLocal, strWrappedString, chr(32))),1,1)
			else 
				' below is for HTML break
				strWrappedString = left(strWrappedString,(inStr((intDesiredWrapLengthLocal + intPositionOfSpaceAfterWrap - 1), strWrappedString, chr(32)))) & replace(strWrappedString,chr(32),(chr(32) & "<br>"),(inStr(intDesiredWrapLengthLocal, strWrappedString, chr(32))),1,1)
			end if 
	end if
	'	intPositionOfSpaceAfterWrap = inStr((intDesiredWrapLengthLocal + intPositionOfSpaceAfterWrap), strWrappedString, chr(32)) 
	'loop
	fncWrapLine = strWrappedString 
end function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub TableFromArrayScatterTableColumnRangeSubheaderRow(zRS, intNumColumn, HeadBGcolor, ColumnAlignArray, ColumnFormatArray, strSubHeaderRow)
	zDetailTable = ""
	zRS.MoveFirst
	zRS.cachesize = 3000
	intRecordCount = zRS.RecordCount     ' set global
    'intFieldCount = zRS.Fields.Count       ' set global
    intFieldCount = intNumColumn
    'ReDim RSArray((intFieldCount - 1), (intRecordCount - 1))   ' set global
	RSArray = zRS.GetRows(zRS.RecordCount)
	Dim intMetaMax
    ' determine size of array
    intMetaMax = intFieldCount - 1 - intKeyFieldCount
    ReDim RSMetaArray(intMetaMax)  ' set global array of Data column names
    Dim i   'recordset field counter
    Dim j   'array row counter
	j=0
	For i = (intKeyFieldCount) To (intFieldCount - 1)
        'retrieve data column names and put in array
		RSMetaArray(j) = zRS.Fields(i).Name
        j = j + 1    
    Next
  '  zRS.Close
   ' Set zRS = Nothing
	If nodata = false then
		response.write("<table width='460' border='1' cellpadding='2'>")
		response.write("<TR><TD colspan='" & (intFieldCount+1) & "'  ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & BrMaker(zGraphTitle) & " </span></TD></TR>")
'		if zGraphinclude="SCATTERTABLEONLY" and zEligibleOnly="no" then
'			'zBanner= "WKCE -- All Students Eligibles FAY  Grade " & zgrade 'hard code for grade 10 now. May have to use zGrade later
'			zBanner= zWKCEOrWSAS & " -- All Students Eligibles FAY  Grade " & zgrade 'hard code for grade 10 now. May have to use zGrade later
'		else
'			'zBanner= "WKCE -- All Students Enrolled FAY Grade " & zgrade
'			zBanner= zTableSubtitle & " -- All Students Enrolled FAY Grade " & zgrade
'		end if

			' brb correcting logic here for all possible combinations 4/03
			intDistrictLevelColumns = 0 
			'response.write("<TR><TD>&nbsp;</TD>")
			if zRel="Spending" or zgroup2 = "Spending" then
				intDistrictLevelColumns = intDistrictLevelColumns + 1
				'response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'> District Spending</span></TD>")
'				ColumnFormatArray(1)="CUR"
			END IF
			if zRel="Size" or zgroup2 = "Size"  then
				intDistrictLevelColumns = intDistrictLevelColumns + 1
				'response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>District Size</span></TD>")
'				ColumnFormatArray(intDistrictLevelColumns +1)="NUM"
			END IF

'			ColumnFormatArray(intDistrictLevelColumns +1)="NUM"
'			ColumnFormatArray(intDistrictLevelColumns +2)="PERC"

'			response.write("<TD colspan='" & ((intFieldCount-1)-cINT(intDistrictLevelColumns)) & "' ALIGN='CENTER' VALIGN='TOP' BGCOLOR='" & HeadBGColor & "'><span class='text'>" & zBanner & "</span></TD></TR>")
response.write(strSubHeaderRow)

		For i = 0 To intFieldCount-1
		  	response.write("<TD ALIGN='CENTER' VALIGN='TOP'><span class='text'>" & RSMetaArray(i) & "</span></TD>")
		Next
		response.write("</TR>")
		zFirstColHold = trim(RSArray(0,0))
		zSpanRow = 0
		For i = 0 to (intRecordCount - 1)
			If trim(zFirstColHold) = trim(RSArray(i,0)) THEN
				zSpanRow = zSpanRow + 1
				zFirstColHold = trim(RSArray(i,0))
			Else
				exit for
			END IF
		Next
		zFirstColHold = ""
		For r = 0 to (intRecordCount - 1)
	    	response.write( "<TR>")
			For i = 0 To intFieldCount-1
				'jdj: -10 showing in table - must double-check for suppression here
				' jdj: using for TQ - suppression not necessary - null is breaking things - leaving out -10 trap
'				if i > 1 and left(cStr(FormatTableColfromArray2(RSArray, i, r, ColumnFormatArray(i))),3) = "-10" then 
'					zDisplayMe = "<span class='text'>*</span>"
'				elseif isnull(RSArray(i,r)) then 
				if isnull(RSArray(i,r)) then 
					zDisplayMe = "<span class='text'>n/a</span>"
				elseif RSArray(i,r) = "--" then 
					zDisplayMe = "<span class='text'>--</span>"
				else
'					' jdj: overzealous formatting routine is adding % to enrollment column - arbitrarily overriding based on the fact that it's the third column 
'					if i = 2 then 
'						zDisplayMe = "<span class='text'>" & FormatTableColfromArray(RSArray, i, r, "NUM") & "</span>"
'					else 
						zDisplayMe = "<span class='text'>" & FormatTableColfromArray2(RSArray, i, r, ColumnFormatArray(i)) & "</span>"
'						zDisplayMe = "<span class='text'>" & RSArray(i,r) & "</span>"
'					end if 

				end if 

				If i = 0 THEN
					If trim(zFirstColHold) <> trim(RSArray(i,r)) THEN
						    response.write( "<TD VALIGN='TOP' ROWSPAN='" & zSpanRow & "' ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
					END IF
					zFirstColHold = trim(RSArray(i,r))
				ELSE
					    response.write( "<TD ALIGN='" & ColumnAlignArray(i) & "'>" & zDisplayMe & "</TD>")
				END IF
			Next
		    response.write( "</TR>")
		NEXT
	    response.write( "</TABLE>")
	END IF
END SUB

'''''''''''''''''''''
Function FormatTableColfromArray2(zArray, zWhichRow, zWhichCol, zEvalString)
	Select Case zEvalString
	Case "STR"
		FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
	Case "DEC1"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),1)
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "NUM"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),0)
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "PERC"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			' jdj: below erroneously adds % to enrollment column - trying to fix
			FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),0) + "%"
			'FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),0) 
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "DEC2"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),2)
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "CUR"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray2 = FormatCurrency(zArray(zWhichRow, zWhichCol),0)
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	CASE "DEC1PERC"
		If isnumeric(trim(zArray(zWhichRow, zWhichCol))) THEN
			FormatTableColfromArray2 = FormatNumber(zArray(zWhichRow, zWhichCol),1) + "%"
		ELSE
			FormatTableColfromArray2 = trim(cSTR(zArray(zWhichRow, zWhichCol)))
		END IF
	End Select
End Function
'***************************************************************************
Function RaceNameAbbrPoints(zWhich)
	Select Case trim(zWhich)
	Case "1"
		RaceNameAbbrPoints = "Am. Ind."
	Case "2"
		RaceNameAbbrPoints = "Asian"
	Case "3"
		RaceNameAbbrPoints = "Black"
	Case "4"
		RaceNameAbbrPoints = "Hispanic"
	Case "5"
		RaceNameAbbrPoints = "White"
	Case "6"
		RaceNameAbbrPoints =  "Comb."		
	Case "8"
		RaceNameAbbrPoints =  "Missing"
	Case else
		RaceNameAbbrPoints = trim(zWhich)
	End Select
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function RaceNameAbbr(zWhich)
	Select Case trim(zWhich)
		Case "American Indian/Alaskan Native"
			RaceNameAbbr = "Am. Ind."
		Case "Asian/Pacific Islander"
			RaceNameAbbr = "Asian"
		Case "Black"
			RaceNameAbbr = "Black"
		Case "Hispanic"
			RaceNameAbbr = "Hisp."
		Case "White"
			RaceNameAbbr = "White"
		Case "Combined Groups/Small Number"
			RaceNameAbbr = "Comb."
		Case else
			RaceNameAbbr = trim(zWhich)
	End Select
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' jdj 2005-05-30 - had to create three new session variables that check WSAS for grades instead of enrollment 
Sub SetHasGxEDISASessionVariables()
	' jdj: must substitute X or recordset comes back empty
	' brb: adding variables for grades 3,5,6,7,9 

	SQL = " select 'HasG3EDISA' = isnull(max(HasG3EDISA),'F'), " & _ 
	" 'HasG4EDISA' = isnull(max(HasG4EDISA),'F'),  " & _ 
	" 'HasG5EDISA' = isnull(max(HasG5EDISA),'F'),  " & _ 
	" 'HasG6EDISA' = isnull(max(HasG6EDISA),'F'),  " & _ 
	" 'HasG7EDISA' = isnull(max(HasG7EDISA),'F'),  " & _ 
	" 'HasG8EDISA' = isnull(max(HasG8EDISA),'F'),  " & _ 
	" 'HasG9EDISA' = isnull(max(HasG9EDISA),'F'),  " & _ 
	" 'HasG10EDISA' = isnull(max(HasG10EDISA),'F') " & _ 
	" from (select 'HasG3EDISA' = max(case ltrim(rtrim(grade)) when '3' then 'T' else 'F' end),  " & _ 
	" 'HasG4EDISA' = max(case ltrim(rtrim(grade)) when '4' then 'T' else 'F' end),  " & _ 
	" 'HasG5EDISA' = max(case ltrim(rtrim(grade)) when '5' then 'T' else 'F' end), " & _ 
	" 'HasG6EDISA' = max(case ltrim(rtrim(grade)) when '6' then 'T' else 'F' end), " & _ 
	" 'HasG7EDISA' = max(case ltrim(rtrim(grade)) when '7' then 'T' else 'F' end), " & _ 
	" 'HasG8EDISA' = max(case ltrim(rtrim(grade)) when '8' then 'T' else 'F' end), " & _ 
	" 'HasG9EDISA' = max(case ltrim(rtrim(grade)) when '9' then 'T' else 'F' end), " & _ 
	" 'HasG10EDISA' = max(case ltrim(rtrim(grade)) when '10' then 'T' else 'F' end) " & _ 
	" from tblWSASWithCountsEnrollmentDenominator where fullkey = '" & replace(Session("Fullkey"),"Z","X") & "' and year = '" & Application("WKCEYear") & "' " & _ 
	" and ([Total Enrollment-PI 1290 definition] <> '0' or [Enrolled] <> '0' or [Included] <> '0') group by grade) x  " 

'	" and ([Total Enrollment-PI 1290 definition] <> '0' or [Total Enrollment-WSAS] <> '0' or [Enrollment included in %s and other WSAS results] <> '0') group by grade) x  " 
	
	Set EDISAGradeRS = Server.CreateObject("ADODB.Recordset")
	EDISAGradeRS.Open SQL, Conn, ADOpenKeyset, ADLockReadOnly
	If not EDISAGradeRS.eof then
		EDISAGradeRS.movefirst
		' brb add additional graes 5/16/06
		Session("HasG3EDISA") = EDISAGradeRS("HasG3EDISA")
		Session("HasG5EDISA") = EDISAGradeRS("HasG5EDISA")
		Session("HasG6EDISA") = EDISAGradeRS("HasG6EDISA")
		Session("HasG7EDISA") = EDISAGradeRS("HasG7EDISA")
		Session("HasG9EDISA") = EDISAGradeRS("HasG9EDISA")
		' end brb add
		Session("HasG4EDISA") = EDISAGradeRS("HasG4EDISA")
		Session("HasG8EDISA") = EDISAGradeRS("HasG8EDISA")
		Session("HasG10EDISA") = EDISAGradeRS("HasG10EDISA")
	ELSE
	' eof
	' brb add like above
	Session("HasG3EDISA") = EDISAGradeRS("HasG3EDISA")
		Session("HasG5EDISA") = "F"
		Session("HasG6EDISA") = "F"
		Session("HasG7EDISA") = "F"
		Session("HasG9EDISA") = "F"
		' end brb add
		Session("HasG4EDISA") = "F"
		Session("HasG8EDISA") = "F"
		Session("HasG10EDISA") = "F"
	END IF
	EDISAGradeRS.close
	Set EDISAGradeRS = nothing
END Sub
''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksCSWWoDis(zQueryString)
	GenGroupLinksCSWWoDis = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
	' jdj: includes test for currentonly
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zCompareTo <> "CURRENTONLY" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Grade</FONT> "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Disability</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
				IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Grade</FONT> "
				ELSE
					IF zCompareTo  = "SELSCHOOLS"  THEN
					' brb remove for now so that grade shows for current only...
					' or zCompareTo  = "CURRENTONLY"
						GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
						GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Grade</FONT> "
						' brb leaving the link off for selected schools option...
						' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
						'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
						' brb adding susp_exp by grade back in 
					ELSEIF zGraphInclude = "GGRADRATE" THEN
						GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Grade</FONT> "
						END IF
					ELSE
						GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
						END IF
					END IF
				END IF
				GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
'				IF zGraphInclude = "ACT" THEN 'this is redundant at the moment but will be necessary when Disability is activated
'					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Disability</FONT> "
'				Else
'					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='#bcbcbc'>Disability</FONT> "
'				End IF
				If zGroup = "Disability" THEN
					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
				ELSE
					GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
				END IF
			END IF
			'GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & " &#149; "
				'If zGroup = "Migrant" THEN
					'GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<font color='" & zActiveLinkColor & "'>Migrant</FONT> "
				'ELSE
					'GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "<A HREF='graphshell.asp?Group=Migrant&" & zQueryString & "'>Migrant</A> "
				'END IF
		END IF
GenGroupLinksCSWWoDis = GenGroupLinksCSWWoDis & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenCompareToLinksWWoDis(zQueryString)
	GenCompareToLinksWWoDis = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
	' brb adding if here to capture stacked graphs which have to be limited when All School Types is chosen
	' force to Current Data Only on include page and grey out options here:
	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and (zGraphInclude = "SUSPEXPINCIDENTS" and zINCIDENT = "CONS")THEN
		GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>Prior Years</FONT> &#149; "
		GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>District/State</FONT> &#149; "
		GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>Selected Districts</FONT>  "
	ELSE 
	' end brb add
		IF zCompareTo = "PRIORYEARS" THEN
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='" & zActiveLinkColor & "'>Prior Years</FONT> &#149; "
		ELSE
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A> &#149; "
		END IF
		IF zCompareTo = "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
		ELSEIF zCompareTo <> "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
		END IF
	    ' adding Orglevel test for 11/2001
' disability changes
'		If zGroup = "Disability"  THEN
'			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>Selected Schools</FONT>"
'		elseif strOrgLevel = "ST" then
		If strOrgLevel = "ST" then
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis& "<font color='#bcbcbc'>Selected Districts</font> &#149; <font color='#bcbcbc'>Selected Schools</FONT>"
		ELSE
			IF zCompareTo = "SELSCHOOLS" and zGraphInclude <> "MONEY" and zGraphInclude <> "AP" THEN
				GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='" & zActiveLinkColor & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</FONT>"
			ELSEIF zCompareTo = "SELSCHOOLS" and (zGraphInclude = "MONEY" or zGraphInclude = "AP") THEN
				GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='" & zActiveLinkColor & "'>Selected Districts</FONT>"
			ELSE
				IF zGraphInclude <> "MONEY" and zGraphInclude <> "AP" and zGraphInclude <> "LEP" THEN
					'ht to delete this commemt:GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
					GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
				ELSEif zGraphInclude = "MONEY" or zGraphInclude = "AP" THEN
					'ht to delete this commemt: GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>Selected Districts</FONT>"
					GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Districts</a>"
				Else
					'ht to delete this commemt: GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<font color='#bcbcbc'>Selected Schools</FONT>"
					GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected Schools</a>"
				END IF
			END IF
		END IF
	END IF
	if strOrgLevel <> "ST" then 
		IF zCompareTo <> "CURRENTONLY" then 
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & " &#149; <A HREF='graphshell.asp?CompareTo=CURRENTONLY&" & zQueryString & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </a>"
		else 
			GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & " &#149; <font color='" & zActiveLinkColor & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
		end if
	else 
		GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	end if
	GenCompareToLinksWWoDis = GenCompareToLinksWWoDis & "</TD></TR></TABLE>"
End Function

''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksDis(zQueryString)
	GenGroupLinksDis = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksDis = GenGroupLinksDis & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksDis = GenGroupLinksDis & " &#149; "
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinksDis = GenGroupLinksDis & " &#149; "
		GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinksDis = GenGroupLinksDis & " &#149; "
		GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Grade</FONT> "
		GenGroupLinksDis = GenGroupLinksDis & " &#149; "
		GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Disability</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinksDis = GenGroupLinksDis & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinksDis = GenGroupLinksDis & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinksDis = GenGroupLinksDis & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
				IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
					GenGroupLinksDis = GenGroupLinksDis & " &#149; "
					GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Grade</FONT> "
				ELSE
'					IF zCompareTo  = "SELSCHOOLS"  THEN
					' brb remove for now so that grade shows for current only...
					' or zCompareTo  = "CURRENTONLY"
'						GenGroupLinksDis = GenGroupLinksDis & " &#149; "
'						GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Grade</FONT> "
						' brb leaving the link off for selected schools option...
						' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
						'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
						' brb adding susp_exp by grade back in 
'					ELSEIF zGraphInclude = "GGRADRATE" THEN
					IF zGraphInclude = "GGRADRATE" THEN
						GenGroupLinksDis = GenGroupLinksDis & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksDis = GenGroupLinksDis & "<font color='#bcbcbc'>Grade</FONT> "
						END IF
					ELSE
						GenGroupLinksDis = GenGroupLinksDis & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksDis = GenGroupLinksDis & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
						END IF
					END IF
				END IF
				GenGroupLinksDis = GenGroupLinksDis & " &#149; "
				If zGroup = "Disability" THEN
					GenGroupLinksDis = GenGroupLinksDis & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
				ELSE
					GenGroupLinksDis = GenGroupLinksDis & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
				END IF
			END IF
		END IF
GenGroupLinksDis = GenGroupLinksDis & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function DistStateSchoolTypeLinksDis(zQueryString)
	DistStateSchoolTypeLinksDis = "<table cellpadding=3 cellspacing=0 border=0><tr valign='top'><td width=60 class='text'>School Type:</TD><td class='text'>"
	If zgroup = "Grade" Then
		' only summary option is available
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>All Types</FONT> &#149; "
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>Elem</FONT> &#149; "
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>Mid/Jr Hi</FONT> &#149; "
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>High</FONT> &#149; "
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>El/Sec</FONT> &#149; "
	Else
		IF zGraphInclude = "SSACTIVITIES" THEN
			' all types not available
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>All Types</FONT> &#149; "
		elseif strTypeCode = "1" Then
			' all types chosen
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>All Types</FONT> &#149; "
		else
			' all types hot
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=1&" & zQueryString & "'>All Types</A> &#149; "
		end if
		IF strTypeCode = "6" THEN
			' Elem
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>Elem</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=6&" & zQueryString & "'>Elem</A> &#149; "
		END IF
		IF strTypeCode = "5" or strTypeCode = "4" THEN
			' Middle/ Junior High
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>Mid/Jr Hi</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=5&" & zQueryString & "'>Mid/Jr Hi</A> &#149; "
		END IF
		IF strTypeCode = "3" THEN
			' high
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>High</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=3&" & zQueryString & "'>High</A> &#149; "
		END IF
		IF strTypeCode = "7" THEN
			' Elem
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>El/Sec</FONT> &#149; "
		ELSE
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=7&" & zQueryString & "'>El/Sec</A>  &#149; "
		END IF
	End IF
	IF strOrgLevel = "DI" THEN
		zOrgLabel = "District"
	ELSEIF strOrgLevel = "ST" THEN
		zOrgLabel = "State"
	END IF
	IF strTypeCode = "9" THEN
		' State or District Summary
		DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='" & zActiveLinkColor & "'>" & zOrgLabel & " Summary</FONT>"
	ELSE
'		'jdj - this link graying out when it shouldn't, I think 
'		'If strOrgLevel = "DI" and (zGroup <> "AllStudentsFAY" and zGroup <> "Grade") THEN
''		If strOrgLevel = "DI" and (zGroup <> "AllStudentsFAY" and zGroup <> "Grade") THEN
'			' only allow for district if all students is selected
''			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>" & zOrgLabel & " Summary</FONT>"		
''		Else
'			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=9&" & zQueryString & "'>" & zOrgLabel & " Summary</A>"
''		END IF

		' per WINSS_checking_1208051.doc, 17b
'		If zGroup = "Disability" THEN
'			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<font color='#bcbcbc'>" & zOrgLabel & " Summary</FONT>"		
'		Else
			DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "<A HREF='graphshell.asp?STYP=9&" & zQueryString & "'>" & zOrgLabel & " Summary</A>"
'		END IF
	END IF
	DistStateSchoolTypeLinksDis = DistStateSchoolTypeLinksDis & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenCompareToLinksNewDis(zQueryString)
	GenCompareToLinksNewDis = "<TABLE cellpadding=3 cellspacing=0 border=0><TR valign='top'><TD WIDTH=60 class='text'>Compare To:</TD><TD class='text'>"
	IF zCompareTo = "PRIORYEARS" THEN
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='" & zActiveLinkColor & "'>Prior Years</FONT> &#149; "
	ELSE
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<A HREF='graphshell.asp?CompareTo=PRIORYEARS&" & zQueryString & "'>Prior Years</A> &#149; "
	END IF
	'IF zCompareTo = "DISTSTATE" THEN
		'if strOrgLevel<>"ST" then
		'GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
		'else
		'GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='" & zActiveLinkColor & "'>Current State Data </FONT> &#149; "
		'end if
	'ELSE
		'ht Feb 5/02: changed wording from District/State to Current Data Only
		'if strOrgLevel<>"ST" then
		'GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
		'else
		'GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>Current State Data</A> &#149; "
		'end if
	'END IF
	IF zCompareTo = "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='" & zActiveLinkColor & "'>District/State</FONT> &#149; "
	ELSEIF zCompareTo <> "DISTSTATE" and (strOrgLevel="SC" or strOrgLevel="DI") THEN
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<A HREF='graphshell.asp?CompareTo=DISTSTATE&" & zQueryString & "'>District/State</A> &#149; "
	END IF
    ' adding Orglevel test for 11/2001
'	If zGroup = "Disability" Then
'		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='#bcbcbc'>Selected Schools</FONT>"
'	Elseif strOrgLevel = "ST" THEN
	If strOrgLevel = "ST" THEN
		'GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='#bcbcbc'>Selected Districts</FONT>&#149;"&"<font color='#bcbcbc'>Selected Schools</FONT>"
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='#bcbcbc'>District/State</FONT> &#149; "&"<font color='#bcbcbc'>Selected Schools</FONT>"
	ELSE
		IF zCompareTo = "SELSCHOOLS" THEN
			GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='" & zActiveLinkColor & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</FONT> "
		ELSE
			IF zGraphInclude <> "STAFF" and zGraphInclude <> "MONEY" and zGraphInclude <> "LEP" THEN
				GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<A HREF='graphshell.asp?CompareTo=SELSCHOOLS&" & zQueryString & "'>Selected " & OrgLevelText("Schools", "Districts", "Schools") & "</A>"
			ELSEif zGraphInclude = "MONEY" THEN
				GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='#bcbcbc'>Selected Districts</FONT>"
			Else
				GenCompareToLinksNewDis = GenCompareToLinksNewDis & "<font color='#bcbcbc'>Selected Schools</FONT>"
			END IF
		END IF
	END IF
	if strOrgLevel <> "ST" then 
		IF zCompareTo <> "CURRENTONLY" then 
			GenCompareToLinksNewDis = GenCompareToLinksNewDis & " &#149; <A HREF='graphshell.asp?CompareTo=CURRENTONLY&" & zQueryString & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data</a>"
		else 
			GenCompareToLinksNewDis = GenCompareToLinksNewDis & " &#149; <font color='" & zActiveLinkColor & "'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
		end if
	else 
		GenCompareToLinksNewDis = GenCompareToLinksNewDis & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	end if
'	GenCompareToLinksNewDis = GenCompareToLinksNewDis & " &#149; <font color='#bcbcbc'>Current " & IncludeIfmatchElse(strOrgLevel, "SC","School",IncludeIfmatchElse(strOrgLevel, "DI","District","State")) & " Data </FONT>"
	GenCompareToLinksNewDis = GenCompareToLinksNewDis & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksCSEconStatELP(zQueryString)
	GenGroupLinksCSEconStatELP = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
	' jdj: includes test for currentonly
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zCompareTo <> "CURRENTONLY" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Grade</FONT> "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Disability</FONT> "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Economic Status</FONT> "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>English Language Proficiency</FONT> "				
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
			IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Grade</FONT> "
			ELSE
				IF zCompareTo  = "SELSCHOOLS"  THEN
				' brb remove for now so that grade shows for current only...
				' or zCompareTo  = "CURRENTONLY"
					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Grade</FONT> "
					' brb leaving the link off for selected schools option...
					' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
					'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
					' brb adding susp_exp by grade back in 
				ELSEIF zGraphInclude = "GGRADRATE" THEN
					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
					If zGroup = "Grade" THEN
						GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
					ELSE
						GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Grade</FONT> "
					END IF
				ELSE
					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
					If zGroup = "Grade" THEN
						GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
					ELSE
						GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
					END IF
				END IF  'zCompareTo  = "SELSCHOOLS"
			END IF  'zGraphInclude = "ACT" or zGraphInclude = "AP"
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "
'				IF zGraphInclude = "ACT" THEN 'this is redundant at the moment but will be necessary when Disability is activated
'					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Disability</FONT> "
'				Else
'					GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='#bcbcbc'>Disability</FONT> "
'				End IF
			If zGroup = "Disability" THEN
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Disability</FONT> "
			ELSE
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=Disability&" & zQueryString & "'>Disability</A> "
			END IF
			
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "	
			If zGroup = "EconomicStatus" THEN
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Economic Status</FONT> "
			ELSE
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=EconomicStatus&" & zQueryString & "'>Economic Status</A> "
			END IF	
		
			GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & " &#149; "	
			If zGroup = "EnglishProficiency" THEN
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>English Language Proficiency</FONT> "
			ELSE
				GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=EnglishProficiency&" & zQueryString & "'>English Language Proficiency</A> "
			END IF
								
		END IF  'zGraphInclude = "GCOURSETAKE"
		
		'GenGroupLinksCSEconStat = GenGroupLinksCSEconStatELP & " &#149; "
		'If zGroup = "Migrant" THEN
			'GenGroupLinksCSEconStat = GenGroupLinksCSEconStatELP & "<font color='" & zActiveLinkColor & "'>Migrant</FONT> "
		'ELSE
			'GenGroupLinksCSEconStat = GenGroupLinksCSEconStatELP & "<A HREF='graphshell.asp?Group=Migrant&" & zQueryString & "'>Migrant</A> "
		'END IF
			
	END IF '(strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zCompareTo <> "CURRENTONLY" and zGraphInclude <> "GGRADRATE"
			
	GenGroupLinksCSEconStatELP = GenGroupLinksCSEconStatELP & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
Function GenGroupLinksCSRetention(zQueryString)
	GenGroupLinksCSRetention = "<TABLE cellpadding=3 cellspacing=0 border=0><TR VALIGN='TOP'><TD WIDTH=60 class='text'>View By:</TD><TD class='text'>" 
	If zGroup = "AllStudentsFAY" THEN
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>All Students</FONT> "
	ELSE
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<A HREF='graphshell.asp?Group=AllStudentsFAY&" & zQueryString & "'>All Students</A> "
	END IF
	GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
	' jdj: includes test for currentonly
 	if (strOrgLevel = "DI" or strOrgLevel = "ST") and strTypeCode = "1" and zCompareTo <> "CURRENTONLY" and zGraphInclude <> "GGRADRATE" THEN
 		' District View the summary options are greyed out for all these..
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Gender</FONT> "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Grade</FONT> "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Migrant</FONT> "
	ELSE
		If zGroup = "Gender" THEN
			GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>Gender</FONT> "
		ELSE
			GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<A HREF='graphshell.asp?Group=Gender&" & zQueryString & "'>Gender</A> "
		END IF
		GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
		IF zGraphInclude = "GCOURSETAKE" THEN
			GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Race/Ethnicity</FONT> "
		Else
			If zGroup = "Race/Ethnicity" THEN
				GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>Race/Ethnicity</FONT> "
			ELSE
				GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<A HREF='graphshell.asp?Group=Race/Ethnicity&" & zQueryString & "'>Race/Ethnicity</A> "
			END IF
				IF zGraphInclude = "ACT" or zGraphInclude = "AP" THEN
					GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
					GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Grade</FONT> "
				ELSE
					IF zCompareTo  = "DISTSTATE" or zCompareTo  = "SELSCHOOLS" THEN
					' brb remove for now so that grade shows for current only...
					' or zCompareTo  = "CURRENTONLY"
						GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
						GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Grade</FONT> "
						' brb leaving the link off for selected schools option...
						' problem with having to add missing rows for the entire set of grades for all schools in order to compare across
						'ELSEIF Left(zGraphInclude,7) = "SUSPEXP" or zGraphInclude = "GGRADRATE" THEN
						' brb adding susp_exp by grade back in 
					ELSEIF zGraphInclude = "GGRADRATE" THEN
						GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Grade</FONT> "
						END IF
					ELSE
						GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
						If zGroup = "Grade" THEN
							GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>Grade</FONT> "
						ELSE
							GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<A HREF='graphshell.asp?Group=Grade&" & zQueryString & "'>Grade</A> "
						END IF
					END IF
				END IF
				GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
				IF zGraphInclude = "ACT" THEN 'this is redundant at the momment but will be necessary when Disability is activated
					GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Disability</FONT> "
				Else
					GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='#bcbcbc'>Disability</FONT> "
				End IF
			END IF
			'GenGroupLinksCSRetention = GenGroupLinksCSRetention & " &#149; "
				'If zGroup = "Migrant" THEN
					'GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<font color='" & zActiveLinkColor & "'>Migrant</FONT> "
				'ELSE
					'GenGroupLinksCSRetention = GenGroupLinksCSRetention & "<A HREF='graphshell.asp?Group=Migrant&" & zQueryString & "'>Migrant</A> "
				'END IF
		END IF
GenGroupLinksCSRetention = GenGroupLinksCSRetention & "</TD></TR></TABLE>"
End Function
''''''''''''''''''''''''''''''''''''''''
%>
