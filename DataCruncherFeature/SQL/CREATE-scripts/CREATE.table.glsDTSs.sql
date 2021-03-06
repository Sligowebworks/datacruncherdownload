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

