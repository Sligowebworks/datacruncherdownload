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