-- =============================================
-- Create procedure basic template
-- =============================================
-- creating the store procedure
IF EXISTS (SELECT name 
	   FROM   sysobjects 
	   WHERE  name = N'spGetDownloadFileNames' 
	   AND 	  type = 'P')
    DROP PROCEDURE spGetDownloadFileNames
GO

CREATE PROCEDURE spGetDownloadFileNames 
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

GRANT EXECUTE ON spGetDownloadFileNames TO netwisco

-- =============================================
-- example to execute the store procedure
-- =============================================
--EXECUTE spGetDownloadFileNames '1,2,3', '1,2,3', '1,2,3'
--EXECUTE spGetDownloadFileNames '2, 3, 8, 10', '2, 3, 4', '8, 19'
--EXECUTE spGetDownloadFileNames '7,8', '2, 3, 4', '8, 9'
--GO

