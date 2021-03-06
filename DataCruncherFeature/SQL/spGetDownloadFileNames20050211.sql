SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[spGetDownloadFileNames]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[spGetDownloadFileNames]
GO




CREATE  PROCEDURE spGetDownloadFileNames 
	@strCSVYearIDs nvarchar(200), 
	@strCSVCESAIDs nvarchar(200),
	@strCSVQuestIDs nvarchar(200) 
AS

SET NOCOUNT ON
	-- add check input strings
DECLARE @SubQuery nvarchar(200)

SET @SubQuery = 'SELECT ID, Year FROM glsYears WHERE ID IN ( ' + @strCSVYearIDs + ' )'
CREATE TABLE #Years (ID int, Year nvarchar(4))
INSERT INTO #Years
EXEC sp_executesql @SubQuery

SET @SubQuery = 'SELECT ID, CESA FROM glsCESAs WHERE ID IN ( ' + @strCSVCESAIDs + ' )'

CREATE TABLE #CESAs (ID INT, CESA nvarchar(3))
INSERT INTO #CESAs
EXEC sp_executesql @SubQuery

--SET @SubQuery = 'SELECT ID, Question FROM glsQuestions WHERE ID IN ( ' + @strCSVQuestIDs + ' )'
--SET @SubQuery = 'SELECT [ID] = QuestionID, Question, QuestSubDivLabel FROM vQuestsJoinSubDivs WHERE QuestionID IN ( ' + @strCSVQuestIDs + ' )'
SET @SubQuery = 'SELECT [ID] = QuestionID, Question, QuestSubDivLabel, QuestSubDivID FROM vQuestsJoinSubDivs WHERE QuestionID IN ( ' + @strCSVQuestIDs + ' )'
--CREATE TABLE #Questions (ID int, Question nvarchar(100), QuestSubDivLabel nvarChar(100))
CREATE TABLE #Questions (ID int, Question nvarchar(100), QuestSubDivLabel nvarChar(100), QuestSubDivID nvarChar(100))
INSERT INTO #Questions
EXEC sp_executesql @SubQuery

SELECT [Filename], #Questions.Question, #Questions.QuestSubDivLabel, vDataSets.Year, vDataSets.YearLabel, vDataSets.CESA 
	FROM (vDataSets
	INNER JOIN
	#CESAs
	on CESAKey  = #CESAs.ID)
	INNER JOIN
	#Years
	on YearKey = #Years.ID
	INNER JOIN
	#Questions
	--on QuestionKey = #Questions.ID 
	on QuestionKey = #Questions.ID and QuestSubDivKey = #Questions.QuestSubDivID 
	--ORDER BY  vDataSets.Year, vDataSets.CESA, #Questions.Question



--SELECT * FROM #CESAs
--SELECT * FROM #Years
--SELECT * FROM #Questions

DROP TABLE #CESAs
DROP TABLE #Years
DROP TABLE #Questions




GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

GRANT  EXECUTE  ON [dbo].[spGetDownloadFileNames]  TO [netwisco]
GO

