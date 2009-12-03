
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