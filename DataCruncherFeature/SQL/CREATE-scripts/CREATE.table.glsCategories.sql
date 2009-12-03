if exists (select * from dbo.sysobjects where id = object_id(N'[glsCategories]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [glsCategories]
GO
CREATE TABLE [glsCategories] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[SectionKey] [int] NOT NULL ,
	[CategoryName] [varchar] (100) NOT NULL ,
	[Disabled] [varchar] (10) NOT NULL DEFAULT ' ' ,
	[Sort] [int] NOT NULL ,
	CONSTRAINT [PK_glsCategories] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

DECLARE @SectionKey int
DECLARE @Sort int

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @SectionKey = 1
SET @Sort = 0

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           ' ', @Sort )

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @SectionKey = @SectionKey + 1
SET @Sort = 0

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining School Performance on StatewideTests', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Test Participation and alternate Assessments', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Reviewing Other Student Performance Indicators', @Sort )
SET @Sort = @Sort + 1

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @SectionKey = @SectionKey + 1
SET @Sort = 0

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Reviewing School Programs and Processes', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Staffing Patterns', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Spending Patterns', @Sort )
SET @Sort = @Sort + 1

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @SectionKey = @SectionKey + 1
SET @Sort = 0

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining attendance Patterns', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Student Involvement', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Disciplinary Patterns', @Sort )
SET @Sort = @Sort + 1

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           'Examining Dropout Rates', @Sort )
SET @Sort = @Sort + 1

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @SectionKey = @SectionKey + 1
SET @Sort = 0

INSERT glsCategories (SectionKey, CategoryName, Sort) 
VALUES (@SectionKey,           '', @Sort )
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
