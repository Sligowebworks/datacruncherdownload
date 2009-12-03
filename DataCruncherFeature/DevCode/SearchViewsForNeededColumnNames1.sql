-- looks for and returns column names we need for page download feature
SELECT col.Name, col.colorder
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Template_Keys'
and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
'schooltype', 'charter', 'agencykey')
ORDER BY col.colorder 
