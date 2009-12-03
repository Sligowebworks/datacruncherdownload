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
	SELECT tDS.[ID], tDS.[CESAKey], tDS.[YearKey], tDS.[QuestionKey], tDS.[QuestSubDivKey],
	tDS.[DTSKey], tDS.[CreateDate], gQ.[QuestSubDivLabel],
	[FileName] = REPLACE(rTrim(	CASE WHEN gC.[Label] = 'All CESA''s' THEN gC.[Label] WHEN (cast(gC.[Label] as int) < 10) THEN '0' + gC.[Label] ELSE gC.[Label] END
	), ' ', '_' ) + ',' + REPLACE(rTrim(gY.[Label]), ' ', '_' ) + ','
	+ REPLACE(REPLACE(rTrim(gQ.[Question]), '?', '') , ' ', '_' )	-- replace single quotes, question marks and spaces
	+ (CASE WHEN LEN( ISNULL(gQ.[QuestSubDivLabel], '') ) > 0 
	THEN 
	',' + rTrim(gQ.[QuestSubDivLabel]) 
	ELSE ''
	END)
	+ '.csv'
	FROM
	tblDataSets tDS
	INNER JOIN glsCESAs gC on tDS.[CESAKey] = gC.ID
	INNER JOIN glsYears gY on tDS.[YearKey] = gY.ID
	Left JOIN vQuestsJoinSubDivs gQ
	on tDS.[QuestSubDivKey] = gQ.[QuestSubDivID] OR 
	tDS.[QuestionKey] = gQ.[QuestionID]

GO


SELECT * FROM vDataSets