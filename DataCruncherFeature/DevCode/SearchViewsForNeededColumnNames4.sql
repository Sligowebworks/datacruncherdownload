-- looks for and returns column names we need for page download feature

select 
'Status' = cast(case when test.name is null then control.name + ' missing!!' else 'OK' end as char(30)), 
cast(control.name as char(20)) as 'Name', test.name 
from 

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Template_Keys'
and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
'schooltype', 'charter', 'agencykey')
) control

left outer join

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Retention'
--and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
--'schooltype', 'charter', 'agencykey')
) test

on control.name = test.name
