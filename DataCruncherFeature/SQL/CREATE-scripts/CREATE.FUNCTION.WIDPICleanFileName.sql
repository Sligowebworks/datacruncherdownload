-- =============================================
-- Create inline function (IF)
-- =============================================
/*IF EXISTS (SELECT * 
	   FROM   sysobjects 
	   WHERE  name = N'WIDPICleanFileName')
	DROP FUNCTION WIDPICleanFileName
*/
GO

CREATE FUNCTION WIDPICleanFileName 
	(@String nvarchar(500))
RETURNS nvarchar(500)
as
BEGIN
SET @String = 
	/*REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(
		@String 
	, ' ', '_')
	, '?', '')
	, '/', '_')
	, '\', '_')
	, '''', '')
	, '"', '')
	, '(', '')
	, '}', '')
	, ',', '')
	, '.', '_')*/
RETURN @String = 'foo'
	 
END
GO

-- =============================================
-- Example to execute function
-- =============================================
SELECT * 
FROM 	WIDPICleanFileName
	('su,p?er c.al(iphr)agi')
GO

