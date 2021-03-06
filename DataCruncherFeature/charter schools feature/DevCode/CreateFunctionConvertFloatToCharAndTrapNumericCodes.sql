drop FUNCTION dbo.ConvertFloatToCharAndTrapNumericCodes 
go

CREATE FUNCTION ConvertFloatToCharAndTrapNumericCodes (@IncomingCode float)
RETURNS char(8)
AS
BEGIN 
	declare @Outgoingcode char(8)
	--set @Outgoingcode = cast(@IncomingCode as char(50))
	set @Outgoingcode = rtrim(str(@IncomingCode,8,2))
	--if isnumeric(rtrim(@IncomingCode)) = 0 set @Outgoingcode = 'ERROR - NOT NUMERIC'
	if rtrim(@IncomingCode) = '-10' set @Outgoingcode = '*'
	if rtrim(@IncomingCode) = '-20' set @Outgoingcode = 'N/A'
	--else set @Outgoingcode = 'xxx'
	--set @Outgoingcode = @IncomingCode 
	RETURN rtrim(ltrim(@Outgoingcode))
END
go
