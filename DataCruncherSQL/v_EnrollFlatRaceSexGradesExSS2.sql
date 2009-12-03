SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

/****** Object:  View dbo.v_EnrollFlatRaceSexGradesExSS2    Script Date: 1/19/2007 2:59:09 PM ******/
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[v_EnrollFlatRaceSexGradesExSS2]') and OBJECTPROPERTY(id, N'IsView') = 1)
drop view [dbo].[v_EnrollFlatRaceSexGradesExSS2]
GO



CREATE view dbo.v_EnrollFlatRaceSexGradesExSS2 as

-- jdj: seriously tortured code that flattens race, sex and grades (Pre-K thru 12) from v_Enrollment into columns....
-- but leaves schooltype numbers (grades 70/71/72/73) for race and sex as rows, so the groups page can do its warped thing

select 
year, YearFormatted, fullkey, agencykey, CESA, schooltype, [District Number], [School Number], charter, county,OrgLevelLabel, Name, [District Name], 
[School Name], 
LinkedName, LinkedDistrictName, 
LinkedSchoolName, Enrollment, Suppressed, 
[Female], [Male], 
(case isnull(Enrollment,0) when 0 then 0 else (([Female]/Enrollment) * 100) end) as '% Female', 
(case isnull(Enrollment,0) when 0 then 0 else (([Male]/Enrollment) * 100) end) as '% Male', 
[Am. Ind.], [Asian], [Black], [Hisp.], [White], [Comb.], [No Resp], 
(case isnull(Enrollment,0) when 0 then 0 else (([Am. Ind.]/Enrollment) * 100) end) as '% Am. Ind.', 
(case isnull(Enrollment,0) when 0 then 0 else (([Asian]/Enrollment) * 100) end) as '% Asian', 
(case isnull(Enrollment,0) when 0 then 0 else (([Black]/Enrollment) * 100) end) as '% Black', 
(case isnull(Enrollment,0) when 0 then 0 else (([Hisp.]/Enrollment) * 100) end) as '% Hisp.', 
(case isnull(Enrollment,0) when 0 then 0 else (([White]/Enrollment) * 100) end) as '% White',
(case isnull(Enrollment,0) when 0 then 0 else (([Comb.]/Enrollment) * 100) end) as '% Comb.', 
(case isnull(Enrollment,0) when 0 then 0 else (([No Resp]/Enrollment) * 100) end) as '% No Resp', 
[Pre-K.], [Kinder.], [Grade 1], [Grade 2], [Grade 3], [Grade 4], [Grade 5], [Grade 6], [Grade 7], [Grade 8], [Grade 9], [Grade 10], [Grade 11], [Grade 12], 
(case isnull(Enrollment,0) when 0 then 0 else (([Pre-K.]/Enrollment) * 100) end) as '% Pre-K.', 
(case isnull(Enrollment,0) when 0 then 0 else (([Kinder.]/Enrollment) * 100) end) as '% Kinder.',
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 1]/Enrollment) * 100) end) as '% Grade 1',
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 2]/Enrollment) * 100) end) as '% Grade 2', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 3]/Enrollment) * 100) end) as '% Grade 3', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 4]/Enrollment) * 100) end) as '% Grade 4', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 5]/Enrollment) * 100) end) as '% Grade 5', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 6]/Enrollment) * 100) end) as '% Grade 6', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 7]/Enrollment) * 100) end) as '% Grade 7', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 8]/Enrollment) * 100) end) as '% Grade 8',
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 9]/Enrollment) * 100) end) as '% Grade 9',
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 10]/Enrollment) * 100) end) as '% Grade 10',
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 11]/Enrollment) * 100) end) as '% Grade 11', 
(case isnull(Enrollment,0) when 0 then 0 else (([Grade 12]/Enrollment) * 100) end) as '% Grade 12',
[Grade], [GradeCode], [GradeLabel], [GradeShortLabel]


from (

select 

d.year, d.YearFormatted, d.fullkey, d.agencykey, d.CESA, d.schooltype, d.[District Number], d.[School Number], d.charter, d.county,d.OrgLevelLabel, d.Name, d.[District Name], 
d.[School Name], 
d.LinkedName, d.LinkedDistrictName, d.LinkedSchoolName, 
-- must use bogus d.race <> 9 and d.sex = 9 to get enrollment without small schools at district level
'Enrollment' = 
sum(case when right(d.fullkey,1) = 'X' and left(d.fullkey,1) <> 'X' then 
-- must leave out 8's in race to get number that match current pages
(CASE WHEN d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) AND  d.race in (1,2,3,4,5,8) and d.sex = 9 THEN isnull(d.enrollment,'0') ELSE 0 END)
else 
(CASE WHEN d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) AND  d.race = 9 and d.sex <> 9 THEN isnull(d.enrollment,'0') ELSE 0 END)
end),

-- old suppressed below - may need to reference if bug
--'Suppressed' = case when min(cast(isnull(d.suppressed,0) as int)) < 0 then cast(min(cast(isnull(d.suppressed,0) as int)) as char) else rtrim(cast(sum(cast(isnull(d.suppressed,'0') as int)) as char)) end,
'Suppressed' = 
case 
	when min(cast(isnull(d.suppressed,0) as int)) < 0 -- if there are any suppressed numbers in the rows to be grouped
	then cast(min(cast(isnull(d.suppressed,0) as int)) as char) -- don't sum the suppression indicator, just return the lowest suppression indicator as char
	else rtrim(cast(	sum(CASE WHEN d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) AND  d.race <> 9 and d.sex <> 9 THEN cast(isnull(d.Suppressed,'0') as int) 
		ELSE 0 END) as char)) -- otherwise apply the same formula as to enrollment
end,

'Female' = sum(case when sexcode = 1 and racecode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Male' = sum(case when sexcode = 2 and racecode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Am. Ind.' = sum(case when racecode = 1 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Asian' = sum(case when racecode = 2 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Black' = sum(case when racecode = 3 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Hisp.' = sum(case when racecode = 4 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'White' = sum(case when racecode = 5 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Comb.' = sum(case when racecode = 6 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'No Resp' = sum(case when racecode = 8 and sexcode = 9 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) then enrollment else 0 end), 
'Pre-K.' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 12 then enrollment else 0 end), 
'Kinder.' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 16 then enrollment else 0 end), 
'Grade 1' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 20 then enrollment else 0 end), 
'Grade 2' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 24 then enrollment else 0 end), 
'Grade 3' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 28 then enrollment else 0 end), 
'Grade 4' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 32 then enrollment else 0 end), 
'Grade 5' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 36 then enrollment else 0 end), 
'Grade 6' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 40 then enrollment else 0 end), 
'Grade 7' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 44 then enrollment else 0 end), 
'Grade 8' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 48 then enrollment else 0 end), 
'Grade 9' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 52 then enrollment else 0 end), 
'Grade 10' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 56 then enrollment else 0 end), 
'Grade 11' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 60 then enrollment else 0 end), 
'Grade 12' = sum(case when racecode = 9 and sexcode = 9 and gradecode = 64 then enrollment else 0 end), 
'Grade' = (case when gradecode in (70,71,72,73) then gradecode else 99 end), 
'GradeCode' = (case when gradecode in (70,71,72,73) then gradecode else 99 end), 
'GradeLabel' = (case when gradecode in (70,71,72,73) then [GradeLabel] else 'Grades PreK-12' end), 
'GradeShortLabel' = (case when gradecode in (70,71,72,73) then [GradeShortLabel] else 'PreK-12' end)

from v_enrollment d where 
-- below are for test only
--year = '2003' and 
--fullkey = 'XXXXXXXXXXXX' and

-- must include below
cast(year as int) > 1996 and d.gradecode in (12,16,20,24,28,32,36,40,44,48,52,56,60,64,70,71,72,73) 

group by d.year, d.YearFormatted, d.fullkey, d.agencykey, d.CESA, d.schooltype, d.[District Number], d.[School Number], d.charter, d.county,d.OrgLevelLabel, d.Name, d.[District Name], 
d.[School Name], d.LinkedName, d.LinkedDistrictName, d.LinkedSchoolName, (case when gradecode in (70,71,72,73) then gradecode else 99 end), 
(case when gradecode in (70,71,72,73) then [GradeLabel] else 'Grades PreK-12' end), (case when gradecode in (70,71,72,73) then [GradeShortLabel] else 'PreK-12' end)


) OuterSelect

-- below are for test only
--where year = '2003' and fullkey = 'XXXXXXXXXXXX'



GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

GRANT  SELECT  ON [dbo].[v_EnrollFlatRaceSexGradesExSS2]  TO [public]
GO

