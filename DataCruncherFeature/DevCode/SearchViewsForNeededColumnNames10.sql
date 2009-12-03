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
'GradeLabel', 'GradeShortLabel', 'enrollment', 'schooltype', 'charter', 'agencykey')
) control

left outer join

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
and 

(
-- ob.Name = 'v_TeacherQualificationsScatterplot'
-- ob.Name = 'v_TeacherQualifications'
-- ob.Name = 'v_LEP'
-- ob.Name = 'v_ErateRollups'
-- ob.Name = 'v_COURSEWORK_KEYS'
-- ob.Name = 'v_COURSEWORK' -- **
-- ob.Name = 'v_GroupsSelSchools' -- **
-- ob.Name = 'v_POST_GRAD_INTENT' -- **
--ob.Name = 'v_ACT'
--ob.Name = 'v_Staff' -- **
--ob.Name = 'v_COURSE_OFFERINGS' -- **
--ob.Name = 'v_Grad_Reqs'
-- ob.Name = 'vExpulsionServices' -- **
--ob.Name = 'vLEPGroupsDistrict' -- ** - many? not needed?
--ob.Name = 'vExpulsionServicesAndReturns'
-- ob.Name = 'vExpServicesKey'  -- ** - others - not nec?
--ob.Name = 'v_Expulsions' -- **
--ob.Name = 'v_Expulsions_Keys'  -- **
--ob.Name = 'v_SuspExpIncidents'  -- **
-- ob.Name = 'v_Suspensions'  -- **
--ob.Name = 'v_Suspensions_Keys' -- **
--ob.Name = 'v_Revenues_2'  
--ob.Name = 'v_Expend_2'
-- ob.Name = 'v_Expend'
--ob.Name = 'v_AP_TESTS' -- **
-- ob.Name = 'vAct' -- ** - others - not nec?
)

--and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
--'schooltype', 'charter', 'agencykey')
) test

on control.name = test.name
where test.name is null

