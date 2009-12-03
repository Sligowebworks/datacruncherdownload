-- =============================================
-- Create procedure with OUTPUT Parameters
-- =============================================
-- creating the store procedure
IF EXISTS (SELECT name 
	   FROM   sysobjects 
	   WHERE  name = N'spNewZipFile' 
	   AND 	  type = 'P')
    DROP PROCEDURE spNewZipFile
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

--GRANT EXECUTE ON spNewZipFile TO Public
GO
GRANT EXECUTE ON spNewZipFile TO netwisco
Go
-- =============================================
-- example to execute the store procedure
-- =============================================
/*
DECLARE <@variable_for_output_parameter, sysname, @p2_output> <datatype_for_output_parameter, , int>
EXECUTE <procedure_name, sysname, proc_test> <value_for_param1, , 1>, <@variable_for_output_parameter, sysname, @p2_output> OUTPUT
SELECT <@variable_for_output_parameter, sysname, @p2_output>
*/

