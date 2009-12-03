-- numbers don't match page - district level high schools
-- small schools? private schools?
-- differs from v_enrollment

SELECT [year], [YearFormatted], [fullkey], [agencykey], [CESA], [schooltype], [District Number], [School Number], [charter], [county], [OrgLevelLabel], [Name], [District Name], 
[School Name], [LinkedName], [LinkedDistrictName], [LinkedSchoolName], 

[Grade], [GradeCode], [GradeLabel], [GradeShortLabel],
[Enrollment], [Female], [% Female], [Male], [% Male], [Am. Ind.], [% Am. Ind.], [Asian], [% Asian], [Black], [% Black], [Hisp.], [% Hisp.], [White], [% White]

--, [Comb.], [% Comb.], [No Resp], [% No Resp]

--[Female], [Male], [% Female], [% Male], [Am. Ind.], [Asian], [Black], [Hisp.], [White], [Comb.], [No Resp], [% Am. Ind.], [% Asian], [% Black], [% Hisp.], [% White], [% Comb.], [% No Resp], 

--[Pre-K.], [Kinder.], [Grade 1], [Grade 2], [Grade 3], [Grade 4], [Grade 5], [Grade 6], [Grade 7], [Grade 8], [Grade 9], [Grade 10], [Grade 11], [Grade 12], 
--[% Pre-K.], [% Kinder.], [% Grade 1], [% Grade 2], [% Grade 3], [% Grade 4], [% Grade 5], [% Grade 6], [% Grade 7], [% Grade 8], [% Grade 9], [% Grade 10], [% Grade 11], [% Grade 12], 

FROM [wisconsin].[dbo].[v_EnrollFlatRaceSexGrades]

where year = '2004' 
--and fullkey = 'XXXXXXXXXXXX'
and 
(fullkey = 'XXXXXXXXXXXX' or fullkey = '01361903XXXX' or fullkey = '013619040022')
and 
(grade = '99' 
or grade = (case right(fullkey,1) when 'X' then '70' else '99' end) 
or grade = (case right(fullkey,1) when 'X' then '71' else '99' end)
or grade = (case right(fullkey,1) when 'X' then '72' else '99' end) 
or grade = (case right(fullkey,1) when 'X' then '73' else '99' end))

--and grade in (case right(fullkey,1) when 'X' then ('99') else ('70','71','72','73','99') end)
--and grade in ('70','71','72','73','99') 
