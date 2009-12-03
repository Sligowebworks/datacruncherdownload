-- looks for and returns column names we need for page download feature

select 
--'Status' = rtrim(cast(case when test.name is null then control.name + ' missing!!' else 'OK' end as char(30)))
'Status' = rtrim(cast(case when test.name is null then 'E.[' + control.name + '], ' else 'OK' end as char(100)))
--, cast(control.name as char(20)) as 'Name', test.name 

from 

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Template_Keys'
and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'Student Group', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 
'GradeLabel', 'enrollment', 'schooltype', 'charter', 'agencykey')
) control

left outer join

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
--AND ob.Name = 'Athletic_Conf'
--AND ob.Name = 'v_Grad_Reqs'
--AND ob.Name = 'v_Staff'
--AND ob.Name = 'v_COURSE_OFFERINGS'
--AND ob.Name = 'v_COURSEWORK'
--AND ob.Name = 'vExpulsionServices'
AND ob.Name = 'v_LEP'

--and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
--'schooltype', 'charter', 'agencykey')
) test

on control.name = test.name
where test.name is null

