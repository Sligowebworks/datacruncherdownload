-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'vDataSets')
    DROP VIEW vDataSets
GO

CREATE VIEW vDataSets
AS 
	
	
SELECT a.[ID], a.[CESAKey], a.[YearKey], a.[QuestionKey], a.[QuestSubDivKey], a.[DTSKey], a.[CreateDate],
[FileName] = 
	REPLACE(
REPLACE( [FileName], ' ', '')
	, '&' , '_')
FROM	
(
	SELECT tDS.[ID], tDS.[CESAKey], tDS.[YearKey], tDS.[QuestionKey], tDS.[QuestSubDivKey],
	tDS.[DTSKey], tDS.[CreateDate], --gQ.[QuestSubDivLabel],
	[FileName] = 
		CASE WHEN gC.[Label] = 'All CESA''s' THEN gC.[Label] 
		WHEN (cast(gC.[Label] as int) < 10) THEN 'CESA0' + gC.[Label] 
		ELSE 'CESA' + gC.[Label] END
	+ '&' + CASE WHEN ISNUMERIC(gY.[Year]) = 1 THEN right( gY.[Year] , 2) ELSE gY.[Label] END
	+ '&' + gQ.[Question]
	+ CASE WHEN LEN( ISNULL(gQ.[QuestSubDivLabel], '') ) > 0 THEN '&' + gQ.[QuestSubDivLabel] ELSE '' END
	+ '.csv'
	FROM
	tblDataSets tDS
	INNER JOIN glsCESAs gC on tDS.[CESAKey] = gC.ID
	INNER JOIN glsYears gY on tDS.[YearKey] = gY.ID
	Left JOIN vQuestsJoinSubDivs gQ
	on tDS.[QuestSubDivKey] = gQ.[QuestSubDivID] OR 
	tDS.[QuestionKey] = gQ.[QuestionID]

) a
GO


SELECT * FROM vDataSets