declare @DTSName nvarchar(30)
declare @DatasetName nvarchar(30)
declare @QID nchar(2)
declare @QSubID nchar(2)

--> changes with each
set @DTSName = 'DataCrunchSuspensionsDaysLost1'

--> not used
set @DatasetName = 'SuspensionsDaysLost'

--> uses question of this code from glsQuestions
set @QID = '24'
set @QSubID = '13'

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
(SELECT DISTINCT [year] FROM Suspensions) Years
on DS.[Year] = Years.[year]

--where Q.ID not in ('1','2','3','4','5','6','7')
WHERE DS.QuestionKey = @QID
--> changes with each - for questions with subQs - otherwise comment out
and DS.QuestSubDivKey = @QSubID
--AND DS.CESAKey <> 1
AND DS.CESA <> 'All'
AND DS.CESA <> 'State'
AND DS.YearKey <> 1

order by DS.[Year], CESA 

