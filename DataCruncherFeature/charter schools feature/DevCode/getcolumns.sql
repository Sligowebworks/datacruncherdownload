USE Wisconsin
GO

SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'WKCE'
ORDER BY xoffset


SELECT sc.*, sT.name, sT.Length, sT.xprec, sT.xscale FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'tblWSASWithCountsSourceOrg'
INNER JOIN sysTypes sT on St.xtype = sc.xtype
--WHERE colid > 12
ORDER BY xoffset


SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'tblAgency'
ORDER BY xoffset


SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'SchoolTypes'
ORDER BY xoffset


SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'groups'
ORDER BY xoffset

SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'WSAS'
ORDER BY xoffset


-- ~%~%~%~

SELECT [Source] = Source.Name, [WKCE] = ws.Name
FROM
(SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'tblWSASWithCountsSource'
) Source
FULL OUTER JOIN 
(SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'WKCE'--'tblWSASWithCountsSource2003AndOnUnifiedColumns'
) ws 
on Source.Name = ws.Name
ORDER BY Source.xoffset, ws.xoffset

-- ~%~%~%~

SELECT [Source] = Source.Name, [WSAS] = ws.Name
FROM
(SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'tblWSASWithCountsSource'
) Source
FULL OUTER JOIN 
(SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'WSAS_EDISA_Source'
) ws 
on Source.Name = ws.Name
ORDER BY Source.xoffset, ws.xoffset

