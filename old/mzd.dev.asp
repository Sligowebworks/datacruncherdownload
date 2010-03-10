<!--#include file="adovbs.inc"-->
<!--#include file="connopen.inc"-->
<!--#include file="functions.inc"-->

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>



</body>
</html>

<% 
Function getColumnsRS(strObj)
	Dim RS
	Set RS = Server.CreateObject("ADODB.Recordset")
	RS.ActiveConnection = Conn
	
	RS.Source = "SELECT col.Name, col.colorder FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id " & _
		"WHERE ob.type = 'V' AND ob.uid = 1 AND ob.Name  = '" & strObj & "' ORDER BY col.colorder; "
	RS.Cursortype = adOpenStatic
	RS.LockType = adLockReadOnly
	RS.Open
	
	Set getColumnsRS = RS
End Function

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
'Update 20040616 -- mzd [incorporate and change jdj edits]
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
Sub BuildSQLSelect_v1(ByRef strString, ByVal strNewFields, ByRef blnAddEnd)
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
	If Len(strString) = 0 Then
		strString = strNewFields
	ElseIF blnAddEnd Then
		strString = strString & ", " & strNewFields
	ElseIF NOT blnAddEnd Then
		strString = strNewFields & ", " & strString
	End If
	'meddle with commas....
	strString = replace(strString,", ",",")	' remove spaces
	strString = replace(strString," ,",",") ' remove spaces
	strString = replace(strString,",,",",")	' check for doubles
	strString = replace(strString,",",", ") ' friendly spaces
End Sub
'**************************************************************************
Sub BuildSQLSelect_v2(ByRef strString, ByVal strNewFields, ByRef blnAddEnd)
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
 %>
