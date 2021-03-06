SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[spGetDownloadFileNamesOne]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[spGetDownloadFileNamesOne]
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
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

GRANT  EXECUTE  ON [dbo].[spGetDownloadFileNamesOne]  TO [netwisco]
GO

