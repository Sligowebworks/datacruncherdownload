-- =============================================
-- Create procedure basic template
-- =============================================
-- creating the store procedure
IF EXISTS (SELECT name 
	   FROM   sysobjects 
	   WHERE  name = N'spGetDownloadFileNamesOne' 
	   AND 	  type = 'P')
    DROP PROCEDURE spGetDownloadFileNamesOne
GO

CREATE PROCEDURE spGetDownloadFileNamesOne
	@strCSVYearIDs nvarchar(200), 
	@strCSVCESAIDs nvarchar(200),
	@strCSVQuestIDs nvarchar(200) 
AS
	-- add check input strings
Execute(
	'SELECT [Filename] FROM vDataSets
	WHERE CESAKey IN (' + @strCSVCESAIDs +') AND
	YearKey IN (' + @strCSVYearIDs +') AND
	QuestionKey IN (' + @strCSVQuestIDs + ')'
)
GO

-- =============================================
-- example to execute the store procedure
-- =============================================
--EXECUTE <procedure_name, sysname, proc_test> <value_for_param1, , 1>, <value_for_param2, , 2>
GO

