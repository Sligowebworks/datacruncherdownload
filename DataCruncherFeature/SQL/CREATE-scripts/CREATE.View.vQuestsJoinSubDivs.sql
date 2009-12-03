-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'vQuestsJoinSubDivs')
    DROP VIEW vQuestsJoinSubDivs
GO

CREATE VIEW vQuestsJoinSubDivs
AS 
	SELECT [QuestionID] = glsQuestions.ID, [Question], [QuestSubDivID] = CASE WHEN glsQuestSubDivs.[ID] IS NULL THEN '' ELSE glsQuestSubDivs.[ID] END, 
	[QuestSubDivLabel] = glsQuestSubDivs.[Label] 
	FROM glsQuestions LEFT JOIN glsQuestSubDivs 
	on glsQuestions.ID = glsQuestSubDivs.QuestionKey
GO

