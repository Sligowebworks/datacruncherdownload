-- WIDownloadFiles database build 
  
  
-- CREATE.table.glsCategories.sql  
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
  
go 
  
  
-- CREATE.table.glsCESAs.sql 
/*
CREATE glsCESAs
*/

--DROP
if exists (select * from dbo.sysobjects where id = object_id(N'[glsCESAs]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [glsCESAs]
GO

--CREATE
CREATE TABLE [glsCESAs] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[CESA] [varchar] (10)  NOT NULL ,
	[Label] [varchar] (16) NULL ,
	[Disabled] [varchar] (10) NOT NULL DEFAULT ' ' ,
	CONSTRAINT [PK_glsCESAs] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

--Populate table


INSERT [glsCESAs] ([CESA], [Label], [Disabled]) 
VALUES ('All', 'All CESA''s', 'DISABLED')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('01', '1')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('02', '2')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('03', '3')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('04', '4')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('05', '5')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('06', '6')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('07', '7')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('08', '8')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('09', '9')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('10', '10')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('11', '11')

INSERT [glsCESAs] ([CESA], [Label]) 
VALUES ('12', '12')

INSERT [glsCESAs] ([CESA], [Label], [Disabled]) 
VALUES ('State', 'State Level Data', 'DISABLED')
  
go 
  
  
-- CREATE.table.glsDTSs.sql 
IF EXISTS (SELECT * FROM dbo.sysobjects WHERE ID = object_id(N'[dbo].[glsDTSs]') 
AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[glsDTSs]
GO

CREATE TABLE [dbo].[glsDTSs] (
	[ID] [int] NOT NULL ,
	[DTSName] [char] (50) NOT NULL ,
	[CreateDate] [datetime] NOT NULL ,
	[LastRunDate] [datetime] NULL 
	CONSTRAINT [PK_glsDTSs] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

  
go 
  
  
-- CREATE.table.glsQuestions.sql 
if exists (select * from dbo.sysobjects where id = object_id(N'[glsQuestions]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [glsQuestions]
GO

CREATE TABLE [glsQuestions] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[CategoryKey] [int] NOT NULL ,
	[Question] [nvarchar] (200) NOT NULL ,
	[Display] [nvarchar] (200) NULL ,
	[Disabled] [nvarchar] (10) NOT NULL DEFAULT ' ' ,
	[Sort] [int] NOT NULL ,
	CONSTRAINT [PK_glsQuestions] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

DECLARE @CatKey int
DECLARE @Sort int
DECLARE @Question nvarchar(200)
DECLARE @Display nvarchar(200)

SET @CatKey = 0	-- invalid, increment first

SET @Sort = 0

--Sample

-- SET @Question = ''
-- SET @Display = @Question
--INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
--VALUES (@CatKey,          @Question,	@Display	, @Sort )
--SET @Sort = @Sort + 1	

--elpmaS

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- Section 0 (All)
--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SET @CatKey = @CatKey + 1
SET @Sort = 0

SET @Question = 'All Questions'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining School Performance on Statewide Tests
SET @Question = 'How did students perform on the state reading test at grade 3?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1

SET @Question = 'How did students perform on state tests at grades 4, 8, and 10?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1
 
SET @Question = 'How did performance of all students enrolled compare to continuing students only?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--DELETED, added and deleted to maintain ID numbering
SET @Question = 'How did the performance of my district compare to other districts statewide?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1

DELETE FROM glsQuestions WHERE Question = @Question

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--DELETED, added and deleted to maintain ID numbering
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Test Participation and Alternate Assessments

SET @Question = 'How many students were not tested on WKCE and why?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled])
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1	

DELETE FROM glsQuestions WHERE Question = @Question

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Reviewing Other Student Performance Indicators

SET @Question = 'What other evidence of student proficiency is available locally?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1

SET @Question = 'What percent of students did not advance to the next grade level? '
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1

SET @Question = 'How did students perform on college admissions and placement tests?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1

SET @Question = 'What are the graduation rates?'
SET @Display = 'What are the graduation rates? (Schools with grade 12 only)'
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What are students'' postgraduation plans?'
SET @Display = 'What are students'' postgraduation plans? (Schools with grade 12 only)'
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--Section II
--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SET @CatKey = @CatKey + 1
SET @Sort = 0

--Reviewing School Programs and Processes

SET @Question = 'What school-supported activities are offered?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What are the district requirements for high school graduation?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What advanced courses are offered?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Staffing Patterns

SET @Question = 'What staff are available in this district?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What are the qualifications of teachers?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,	@Question,	@Display	, @Sort, 'DISABLED' )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Spending Patterns

SET @Question = 'How much money is received and spent in this district?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'Where can I find more detailed school finance data?'
SET @Display = '<a href="http://www2.dpi.state.wi.us/sfsdw/download.asp" target="_new">' + @Question + '</a>'
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--Section III
--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Attendance Patterns

SET @Question = 'What percent of students attend school each day?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What percent of students are habitually truant?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Student Involvement

SET @Question = 'Do students participate in school supported activities?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What courses are students taking?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Disciplinary Patterns

SET @Question = 'What percentage of students were suspended or expelled last year?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What percentage of school days were lost due to suspension or expulsion?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What types of incidents resulted in suspensions or expulsions?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

SET @Question = 'What happens after students are expelled?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SET @CatKey = @CatKey + 1
SET @Sort = 0

--Examining Dropout Rates

SET @Question = 'How many students dropped out of school last year?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort )
SET @Sort = @Sort + 1	

--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--Section IV
--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SET @CatKey = @CatKey + 1
SET @Sort = 0
--(none)

SET @Question = 'What is the enrollment by student group?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,	@Question,	@Display	, @Sort, 'DISABLED' )
SET @Sort = @Sort + 1	
	
SET @Question = 'What are the primary disabilities of students in need of special education services?'
SET @Display = 'What are the primary disabilities of students in need of special education services? (not avail. at school level before 2000-01)'
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
SET @Sort = @Sort + 1	
	
SET @Question = 'What are the characteristics of limited English proficient students at this school?'
SET @Display = @Question
INSERT glsQuestions (CategoryKey, Question, Display, Sort, [disabled]) 
VALUES (@CatKey,           @Question,	@Display	, @Sort, 'DISABLED' ) 
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
  
go 
  
  
-- CREATE.table.glsQuestSubDivs.sql 
-- =============================================
-- Create table basic template
-- =============================================
IF EXISTS(SELECT name 
	  FROM 	 sysobjects 
	  WHERE  name = N'glsQuestSubDivs' 
	  AND 	 type = 'U')
    DROP TABLE glsQuestSubDivs
GO

CREATE TABLE glsQuestSubDivs (
	ID int IDENTITY NOT NULL, 
	QuestionKey int NULL,
	Label nvarchar(200)

	CONSTRAINT [PK_glsQuestSubDivs] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
)
GO

--Populate table

--How did students perform on college admissions and placement tests?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (9,'ACT')

--How did students perform on college admissions and placement tests?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (9,'Advanced Placement Exam')

--What school-supported activities are offered?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (12,'Extra/Co-curricular Activities')

--What school-supported activities are offered?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (12,'Community Activities')

--What are the requirements for high school graduation?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (13,'Subjects Required by State Law')

--What are the requirements for high school graduation?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (13,'Additional Subjects')

--What are the qualifications of teachers?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (16,'Wisconsin License Status')

--What are the qualifications of teachers?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (16,'District Experience')

--What are the qualifications of teachers?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (16,'Total Experience')

--What are the qualifications of teachers?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (16,'Highest Degree')

--What are the qualifications of teachers?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (16,'ESEA Qualified')

--How much money is received and spent in this district?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (17,'Revenue Per Member')

--How much money is received and spent in this district?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (17,'Cost Per Member')

--Do students participate in school supported activities?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (21,'Extra/Co-curricular Activities')

--Do students participate in school supported activities?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (21,'Community Activities')

--What percentage of students were suspended or expelled last year?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (23,'Suspension')

--What percentage of students were suspended or expelled last year?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (23,'Expulsion')

--What percentage of school days were lost due to suspension or expulsion?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (24,'Suspension')

--What percentage of school days were lost due to suspension or expulsion?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (24, 'Expulsion')

--What types of incidents resulted in suspensions or expulsions?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (25, 'Incident Rate')

--What types of incidents resulted in suspensions or expulsions?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (25, 'Disciplinary Consequences')

--What happens after students are expelled?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (26, 'Length of Expulsion')

--What happens after students are expelled?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (26, 'Post Expulsion Services')

--What happens after students are expelled?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
-- jdj 20050106: typo - changed from 25 to 26
VALUES (26, 'Returns to School')

--What is the enrollment by student group?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'All Students')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'Gender')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'Race/Ethnicity')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'Disability')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'Economic Status')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'English Proficiency')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (28, 'Grade')

--What courses are students taking?
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (22, 'Advanced Placement')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (22, 'Local College AP')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (22, 'DPI-Defined Advanced Coursework')

INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (22, 'Other')
/*
INSERT [glsQuestSubDivs] ([QuestionKey], [Label])
VALUES (n, 'name')
*/


GO

SELECT * FROM glsQuestSubDivs  
go 
  
  
-- CREATE.table.glsSections.sql 
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
  
go 
  
  
-- CREATE.table.glsYears.sql 

/*
CREATE [glsYears]
*/

--DROP
IF EXISTS (SELECT * FROM dbo.sysobjects WHERE ID = object_id(N'[glsYears]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE [glsYears]
GO

--CREATE
CREATE TABLE [glsYears] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[Year] [varchar] (10) NOT NULL ,
	[Label] [varchar] (10) NULL ,
	[Disabled] [varchar] (10) NOT NULL DEFAULT ' ' ,
	CONSTRAINT [PK_glsYear] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO


--Populate table

INSERT [glsYears] ([Year], [Label], [Disabled])
VALUES ('All', 'All Years', ' DISABLED')

--INSERT [glsYears] ([Year], [Label])
--VALUES ('1996', '1995-96')

INSERT [glsYears] ([Year], [Label])
VALUES ('1997', '1996-97')

INSERT [glsYears] ([Year], [Label])
VALUES ('1998', '1997-98')

INSERT [glsYears] ([Year], [Label])
VALUES ('1999', '1998-99')

INSERT [glsYears] ([Year], [Label])
VALUES ('2000', '1999-00')

INSERT [glsYears] ([Year], [Label])
VALUES ('2001', '2000-01')

INSERT [glsYears] ([Year], [Label])
VALUES ('2002', '2001-02')

INSERT [glsYears] ([Year], [Label])
VALUES ('2003', '2002-03')

INSERT [glsYears] ([Year], [Label])
VALUES ('2004', '2003-04')  
go 
  
  
-- CREATE.View.vQuestsJoinSubDivs.sql 
-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'vQuestsJoinSubDivs')
    DROP VIEW vQuestsJoinSubDivs
GO

CREATE VIEW vQuestsJoinSubDivs
AS 
	SELECT [QuestionID] = glsQuestions.ID, [Question], [QuestSubDivID] = CASE WHEN glsQuestSubDivs.[ID] IS NULL THEN '' ELSE glsQuestSubDivs.[ID] END, 
	[QuestSubDivLabel] = glsQuestSubDivs.[Label] 
	FROM glsQuestions LEFT JOIN glsQuestSubDivs 
	on glsQuestions.ID = glsQuestSubDivs.QuestionKey
GO

  
go 
  
  
-- CREATE.View.v_Questions.sql 
-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'v_Questions')
    DROP VIEW v_Questions
GO

CREATE VIEW v_Questions
AS 

SELECT q.ID, q.[Disabled], q.Question, q.Display, s.SectionName, s.SectionQuestion, c.CategoryName, [PrimarySort] = s.sort, [SecondarySort] = c.sort, [TertiarySort] = q.sort
FROM 	glsQuestions 	q
INNER JOIN
	glsCategories	c	on q.CategoryKey = c.ID
INNER JOIN
	glsSections 	s	on c.SectionKey = s.ID


GO

  
go 
  
  
-- CREATE.table.tblDataSets.sql 
IF EXISTS (SELECT * FROM dbo.sysobjects WHERE ID = object_id(N'[dbo].[tblDataSets]') 
AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[tblDataSets]
GO

CREATE TABLE [dbo].[tblDataSets] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[CESAKey] [int] NOT NULL ,
	[YearKey] [int] NOT NULL ,
	[QuestionKey] [int] NOT NULL ,
	[QuestSubDivKey] [int] NULL ,
	[DTSKey] [int] NULL ,
	[CreateDate] [datetime] NULL
	CONSTRAINT [PK_tblDataSets] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) 
GO

--populate table

INSERT tblDataSets
SELECT [CESAKey] = gC.ID, [YearKey] = gY.ID, [QuestionKey] = gQ.[QuestionID], 
[QuestSubDivKey] = gQ.[QuestSubDivID], [DTSKey] = NULL, [CreateDate] = NULL
FROM
glsCESAs gC
CROSS JOIN 
glsYears gY
CROSS JOIN
vQuestsJoinSubDivs gQ
--WHERE gC.Cesa <> 'State'
  
go 
  
  
-- CREATE.View.vDataSets.sql 
-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'vDataSets')
    DROP VIEW vDataSets
GO

CREATE VIEW vDataSets
AS 
	
	SELECT tDS.[ID], tDS.[CESAKey], tDS.[YearKey], tDS.[QuestionKey], tDS.[QuestSubDivKey],
	tDS.[DTSKey], tDS.[CreateDate], [Year] = gY.[Year], [CESA] = gC.[CESA], [YearLabel] = gY.[Label],
[FileName] = 
						REPLACE(
					REPLACE(
				REPLACE(
			REPLACE(
		REPLACE(
	REPLACE(
REPLACE( lower(

	rtrim(gQ.[Question]) + CASE WHEN LEN( rtrim(ISNULL(gQ.[QuestSubDivLabel], '')) ) > 0 THEN '_' + rtrim(gQ.[QuestSubDivLabel]) ELSE '' END 
	+ '_' + CASE WHEN ISNUMERIC(gY.[Year]) = 1 THEN rtrim(gY.[Year]) ELSE rtrim(gY.[Year]) END
	+ '_' + 'CESA' + rtrim(gC.[CESA])
--	+ '_' + CASE WHEN rtrim(gC.[Label]) = 'All CESA''s' THEN rtrim(gC.[Label])
--		WHEN (cast(gC.[Label] as int) < 10) THEN 'CESA0' + rtrim(gC.[Label])
--		ELSE 'CESA' + rtrim(gC.[Label]) END
	+ '.csv'
), ' ', '_')
	, '?', '')
		, '\', '')
			, '/', '')
				, '''', '')
					, '(', '')
						, ')', '')
	FROM
	tblDataSets tDS
	INNER JOIN glsCESAs gC on tDS.[CESAKey] = gC.ID
	INNER JOIN glsYears gY on tDS.[YearKey] = gY.ID
	INNER JOIN vQuestsJoinSubDivs gQ
	on tDS.[QuestSubDivKey] = gQ.[QuestSubDivID] AND
	tDS.[QuestionKey] = gQ.[QuestionID]

GO


--SELECT * FROM vDataSets  
go 
  
  
-- CREATE.table.logDownloadFiles.sql 

IF EXISTS (SELECT * FROM dbo.sysobjects WHERE ID = object_id(N'logDownloadFiles') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table logDownloadFiles
GO
CREATE TABLE logDownloadFiles (
	[ID] int IDENTITY (1, 1) NOT NULL ,
	[HTTP_REMOTE_ADDR] nvarchar (15) NULL,
	[RequestDate] datetime NOT NULL,
	[RequestString] nvarchar(500) NULL
	CONSTRAINT [PK_logDownloadFiles] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO  
go 
  
  
-- CREATE.PROCEDURE.GetDownloadFilenames.sql 
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

  
  
-- CREATE.PROCEDURE.NewZipFile.sql 
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

  
-- should be done now 
