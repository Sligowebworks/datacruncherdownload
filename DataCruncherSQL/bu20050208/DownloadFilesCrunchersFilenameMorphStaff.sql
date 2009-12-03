declare @DTSName nvarchar(50)
declare @DatasetName nvarchar(50)
declare @QID nchar(2)
declare @QSubID nchar(2)

--> changes with each
set @DTSName = 'DataCrunchStaff'

--> not used
set @DatasetName = 'IncidentsRate'

--> uses question of this code from glsQuestions
set @QID = '15'
set @QSubID = '0'

/*SELECT 
'call DTSToCSV ' + rtrim(@DTSName) + ' '  + 
+ [Year] + ' ' + CESA + ' 
ren TempFileOutput.csv ' + [FileName] 

FROM 
*/
SELECT 
[Exec] = 
'call DTSToCSV ' + @DTSName + ' '  + 
+ DS.[Year] + ' ' + CESA + '
ren TempFileOutput.csv ' + DS.[FileName] 
--,DS.*
FROM 
WIDownloadFiles.dbo.vDataSets DS
INNER JOIN 
--> changes with each
(SELECT DISTINCT [year] FROM staff) Years
on DS.[Year] = Years.[year]

--where Q.ID not in ('1','2','3','4','5','6','7')
WHERE DS.QuestionKey = @QID
--> changes with each - set to 0 for questions with no subQs? 
and DS.QuestSubDivKey = @QSubID
--AND DS.CESAKey <> 1
AND DS.CESA <> 'All'
AND DS.CESA <> 'State'
AND DS.YearKey <> 1

order by DS.[Year], CESA 

