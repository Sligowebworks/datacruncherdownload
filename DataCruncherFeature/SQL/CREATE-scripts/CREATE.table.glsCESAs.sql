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
