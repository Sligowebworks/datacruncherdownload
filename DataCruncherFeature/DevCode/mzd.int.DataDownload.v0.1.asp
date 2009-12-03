<!--#INCLUDE file="functions.inc" -->
<% 
Dim blnDebug
blnDebug = CBool(Request.QueryString("debug"))
If (Not blnDebug) AND CBool(Request.Form("debug")) Then
	blnDebug = True
End IF

dim arrYears(7)
dim arrCESAs(12)
dim arrQuests(27)

'------------------------- DEBUG ----------------------
If blnDebug Then
	Dim item
	Dim item2
	Call PrintVar("Request.Form.Count")
	For Each item in Request.form
		If Request.form(item).count > 1 Then
			Call PrintVar("item")
			For Each item2 in Request.form(item) 
				Response.Write("<br>")
				Response.Write(item2)
'				Call PrintVar("Request.form(" & item & ")(" & item2 & ")") 
				'Response.Write("Request.Form(" & item & ").count")
				'Response.Write(Request.form(item).count)
				'Call PrintVar("Request.Form(" & item & ").count")
				'Call PrintVar("Request.form(" & item & ")")
			Next
		End IF
	Next
End If
'------------------------------------

dim colForm
set colForm = Request.Form("chkQuests")
intQuestCount = colForm.Count
Call FillDownloadArray(arrQuests, colForm)

set colForm = Request.Form("chkCESAs")
intCESACount = colForm.Count
Call FillDownloadArray(arrCESAs, colForm)

set colForm = Request.Form("chkYears")
intYearCount = colForm.Count
Call FillDownloadArray(arrYears, colForm)

dim intNumFiles 
intNumFiles = intYearCount * intCESACount * intQuestCount
'Call PrintVar("intNumFiles")

redim arrFileNames(intNumFiles)
dim n
n = 0
arrx = arrQuests
arry = arrYears
arrz = arrCESAs
'Call PrintVar("intQuestCount")
'Call PrintVar("intYearCount")
'Call PrintVar("intCESACount")
For x = 0 to intQuestCount - 1
	'Call PrintVar("x")
	For y = 0 to intYearCount - 1
		'Call PrintVar("y")
		For z = 0 to intCESACount -1
			'Call PrintVar("z")
			arrFileNames(n) = CStr(arrx(x)) & "_" & CStr(arry(y)) & "_" & CStr(arrz(z)) & ".csv"
			n = n + 1
		Next
	Next
Next

If blnDebug Then
	For n = 0 to intNumFiles - 1
		Call PrintVar("arrFileNames(" & n & ")")
	Next
End If

'~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~
Sub FillDownloadArray(arr, colForm)
	For i = 0 to colForm.count -1
		arr(i) = colForm(i+1)	'form collections are One based
	Next
End Sub

%>
