IF EXISTS (SELECT * FROM dbo.sysobjects WHERE ID = object_id(N'[dbo].[tblDataFiles]') 
AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[tblDataFiles]
GO

CREATE TABLE [dbo].[tblDataFiles] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[CESAKey] [int] NOT NULL ,
	[YearKey] [int] NOT NULL ,
	[QuestionKey] [int] NOT NULL ,
	[DTSKey] [int] NOT NULL ,
	[CreateDate] [datetime] NOT NULL
	CONSTRAINT [PK_tblDataFiles] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
) ON [PRIMARY]
GO

