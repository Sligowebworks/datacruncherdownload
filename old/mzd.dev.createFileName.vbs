OPTION EXPLICIT

' test to create unique filenames

Dim FSO
Dim strFileName 
Dim strNow

Dim array(9)
Dim n

'strNow = CStr(Now())
strNow = Now()
'WSH.Echo strNow

strFileName = Replace(Replace(strNow, "/", "-"), " ", "_") & ".zip"

'WSH.Echo strFileName

For n = 0 to 9
	'array(n) = Replace(Replace(Now(), "/", "-"), " ", "_") & ".zip"
	array(n) = Replace(Replace(Now(), "/", "-"), " ", "_") & "." & CStr(Round(Rnd() * 100, 0)) & ".zip"
Next

For n = 0 to 9
	WSH.Echo array(n)
Next

