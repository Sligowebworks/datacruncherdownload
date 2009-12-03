if exists (select * from dbo.sysobjects where id = object_id(N'[glsSections]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [glsSections]
GO
CREATE TABLE [glsSections] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[DatabaseKey] [int] NULL ,
	[SectionName] [varchar] (50) NOT NULL ,
	[SectionQuestion] [varchar] (50) NOT NULL ,
	[Disabled] [varchar] (10) NOT NULL DEFAULT ' ' ,
	[Sort] [int] NOT NULL --,
	CONSTRAINT [PK_glsSection] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

DECLARE @Sort int
SET @Sort = 0

INSERT glsSections (DatabaseKey, SectionName, SectionQuestion, Sort ) 
VALUES (NULL, 'All', ' ', @Sort)
SET @Sort = @Sort + 1

INSERT glsSections (DatabaseKey, SectionName, SectionQuestion, Sort) 
VALUES (NULL, 'Performance', 'How are students performing academically?', @Sort )
SET @Sort = @Sort + 1

INSERT glsSections (DatabaseKey, SectionName, SectionQuestion, Sort) 
VALUES (NULL, 'Resources', 'What programs, staff, and money are available?', @Sort )
SET @Sort = @Sort + 1

INSERT glsSections (DatabaseKey, SectionName, SectionQuestion, Sort) 
VALUES (NULL, 'Attendance', 'What about attendance and behavior?', @Sort )
SET @Sort = @Sort + 1

INSERT glsSections (DatabaseKey, SectionName, SectionQuestion, Sort) 
VALUES (NULL, 'Demographics', 'What are student demographics?', @Sort )
SET @Sort = @Sort + 1


/*-- =============================================
-- Create index basic template
-- =============================================
CREATE INDEX <index_name, sysname, ind_test>
ON <database_name, sysname, pubs>.<owner, sysname, dbo>.<table_or_view_name, sysname, authors> 
	(<column_1, sysname, au_lname>, 
	 <column_2, sysname, au_fname>)
--GO
*/
