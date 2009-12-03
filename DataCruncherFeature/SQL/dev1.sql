


DECLARE	@strCSVYearIDs nvarchar(200)
DECLARE	@strCSVCESAIDs nvarchar(200)
DECLARE	@strCSVQuestIDs nvarchar(200) 

SET	@strCSVYearIDs = '1,2,3'
SET	@strCSVCESAIDs = '1,2,3'
SET	@strCSVQuestIDs = '1,2,3'

DECLARE @SubQuery nvarchar(200)

SET @SubQuery = 'SELECT ID, CESA FROM glsCESAs WHERE ID IN ( ' + @strCSVCESAIDs + ' )'

CREATE TABLE #CESAs (ID INT, CESA nvarchar(3))
INSERT INTO #CESAs
EXEC sp_executesql @SubQuery

SET @SubQuery = 'SELECT ID, Year FROM glsYears WHERE ID IN ( ' + @strCSVYearIDs + ' )'
CREATE TABLE #Years (ID int, Year nvarchar(4))
INSERT INTO #Years
EXEC sp_executesql @SubQuery

SET @SubQuery = 'SELECT ID, Question FROM glsQuestions WHERE ID IN ( ' + @strCSVQuestIDs + ' )'
CREATE TABLE #Questions (ID int, Question nvarchar(100))
INSERT INTO #Questions
EXEC sp_executesql @SubQuery

SELECT [Filename], #Questions.Question, vDataSets.Year, vDataSets.CESA FROM vDataSets
	INNER JOIN
	#CESAs
	on CESAKey  = #CESAs.ID
	INNER JOIN
	#Years
	on YearKey = #Years.ID
	INNER JOIN
	#Questions
	on QuestionKey = #Questions.ID



--SELECT * FROM #CESAs
--SELECT * FROM #Years
--SELECT * FROM #Questions

DROP TABLE #CESAs
DROP TABLE #Years
DROP TABLE #Questions
