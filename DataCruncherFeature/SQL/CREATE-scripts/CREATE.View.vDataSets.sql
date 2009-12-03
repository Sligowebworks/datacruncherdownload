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
	tDS.[DTSKey], tDS.[CreateDate], [Year] = gY.[Year], [CESA] = gC.[CESA], [YearLabel] = gY.[Label],
[FileName] = 
						REPLACE(
					REPLACE(
				REPLACE(
			REPLACE(
		REPLACE(
	REPLACE(
REPLACE( lower(

	rtrim(gQ.[Question]) + CASE WHEN LEN( rtrim(ISNULL(gQ.[QuestSubDivLabel], '')) ) > 0 THEN '_' + rtrim(gQ.[QuestSubDivLabel]) ELSE '' END 
	+ '_' + CASE WHEN ISNUMERIC(gY.[Year]) = 1 THEN rtrim(gY.[Year]) ELSE rtrim(gY.[Year]) END
	+ '_' + 'CESA' + rtrim(gC.[CESA])
--	+ '_' + CASE WHEN rtrim(gC.[Label]) = 'All CESA''s' THEN rtrim(gC.[Label])
--		WHEN (cast(gC.[Label] as int) < 10) THEN 'CESA0' + rtrim(gC.[Label])
--		ELSE 'CESA' + rtrim(gC.[Label]) END
	+ '.csv'
), ' ', '_')
	, '?', '')
		, '\', '')
			, '/', '')
				, '''', '')
					, '(', '')
						, ')', '')
	FROM
	tblDataSets tDS
	INNER JOIN glsCESAs gC on tDS.[CESAKey] = gC.ID
	INNER JOIN glsYears gY on tDS.[YearKey] = gY.ID
	INNER JOIN vQuestsJoinSubDivs gQ
	on tDS.[QuestSubDivKey] = gQ.[QuestSubDivID] AND
	tDS.[QuestionKey] = gQ.[QuestionID]

GO


--SELECT * FROM vDataSets