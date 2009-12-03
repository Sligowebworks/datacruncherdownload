
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

INSERT [glsYears] ([Year], [Label])
VALUES ('2005', '2004-05')

INSERT [glsYears] ([Year], [Label])
VALUES ('2006', '2005-06')

INSERT [glsYears] ([Year], [Label])
VALUES ('2007', '2006-07')

INSERT [glsYears] ([Year], [Label])
VALUES ('2008', '2007-08')

