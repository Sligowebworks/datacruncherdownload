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
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort)
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
INSERT glsQuestions (CategoryKey, Question, Display, Sort) 
VALUES (@CatKey,	@Question,	@Display	, @Sort)
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
