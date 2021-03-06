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
