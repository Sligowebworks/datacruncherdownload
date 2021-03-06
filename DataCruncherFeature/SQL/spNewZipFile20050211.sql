SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[spNewZipFile]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[spNewZipFile]
GO


CREATE PROCEDURE spNewZipFile 
	@Address nvarchar(15) , 
	@Request nvarchar(500),
	@ID int OUTPUT
AS
SET NOCOUNT ON

	INSERT INTO logDownloadFiles (HTTP_REMOTE_ADDR, RequestString, RequestDate )
	VALUES (@Address, @Request, GETDATE() )

	SET @ID = @@IDENTITY

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

GRANT  EXECUTE  ON [dbo].[spNewZipFile]  TO [netwisco]
GO

