declare @QID nchar(2)
set @QID = '24'

SELECT 
QuestionKey, QuestSubDivKey, 
FileName
FROM 
WIDownloadFiles.dbo.vDataSets 
WHERE 
--QuestionKey = @QID and QuestSubDivKey = 16 and 
year = '2003' and CESA = '01'
