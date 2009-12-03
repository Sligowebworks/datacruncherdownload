SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[procActivitiesOfferedExtraCoDataCrunch]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[procActivitiesOfferedExtraCoDataCrunch]
GO


create procedure procActivitiesOfferedExtraCoDataCrunch
@year char(4),
@cesa char(2)
as
-- must restrict wheres further per previous crunch queries
--declare @year char(4)
--declare @cesa char(2)
--set @year = '2003' 
--set @cesa = '01' 
select keys.year, keys.AgencyKey as 'agency_key', keys.CESA, keys.[District Number] as 'district_number', isnull(keys.[School Number],'') as 'school_number', 
'agency_type' = left(right(keys.fullkey,6),2), 
'school_type' = (case when right(keys.fullkey,1) <> 'X' then 
(case keys.schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeLabel) when 'K-12' then 'Summary' else rtrim(GradeLabel) end) end), 
else (case when rtrim(gradecode) = '94' then 'Summary' when rtrim(gradecode) < 65 then 'Summary' else rtrim(keys.GradeShortLabel) end) end), 
keys.charter, keys.[District Name] as 'district_name', 
keys.[School Name] as 'school_name', keys.GradeLabel as 'grade_label', keys.RaceLabel as 'race_ethnicity', keys.SexLabel as 'gender', keys.name as 'activity_type', 
isnull(keys.Enrollment,0) AS 'enrollment_grades_6-12', 
'offerings per school (average)' = case when keys.suppressed is null then '0' when keys.suppressed is not null then cast(isnull(numoffer,0) as char(10)) end 
--'pupils_participating' = CASE WHEN keys.suppressed is null THEN '0' WHEN keys.suppressed is not null THEN cast(isnull(PupilParticip,0) as char(10)) END, 
--'participation_rate' = CASE WHEN keys.suppressed is null THEN '0.0%' WHEN keys.suppressed is not null THEN CASE WHEN PupilParticip is null THEN '0.0%' 
--when data.Enrollment = 0 THEN '0.0%' WHEN PupilParticip is not null THEN cast(((PupilParticip/data.Enrollment)*100) as varchar(50)) END END
from 
(select distinct v_enrollment.year, v_enrollment.AgencyKey, v_enrollment.CESA, v_enrollment.[District Number], v_enrollment.[School Number], v_enrollment.schooltype, v_enrollment.charter, v_enrollment.[District Name], v_enrollment.[School Name], 
v_enrollment.GradeCode, v_enrollment.GradeLabel, v_enrollment.GradeShortLabel, v_enrollment.RaceLabel, v_enrollment.SexLabel, activities.code, activities.name, enrollment , suppressed, v_enrollment.fullkey 
from activities, v_enrollment left outer join agency on (v_enrollment.year = agency.year and v_enrollment.fullkey = agency.fullkey) 
where activities.code in ('at','ac','ms') and v_enrollment.race = 9 and v_enrollment.sex = 9 
--and v_enrollment.year <= 2003 
and v_enrollment.year = @year 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade = 94) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade = 94)) ) keys 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade in ('90','91','92','93','94')) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))) ) keys 
--and ((left(v_enrollment.fullkey,2) = @cesa and v_enrollment.grade in ('90','91','92','93','94')) 
and ((left(v_enrollment.fullkey,2) = @cesa and 
((right(v_enrollment.fullkey,1) <> 'X' and v_enrollment.grade = '94') or (right(v_enrollment.fullkey,1) = 'X' and v_enrollment.grade in ('90','91','92','93','94')))
) 
--or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))
and (right(left(v_enrollment.fullkey,8),2) <> '14' or (
--> changes with each
right(left(v_enrollment.fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_enrollment.year = agency.year and v_enrollment.agencykey = agency.agencykey) is not null 
))
) ) keys 
left outer join 
--(select v_enrollment.year, agency.name, enrollment, suppressed, pupilparticip, code, v_enrollment.fullkey 
(select v_enrollment.year, agency.name, enrollment, suppressed, numoffer, code, v_enrollment.fullkey, v_enrollment.gradelabel
from v_enrollment 
left outer join agency on (v_enrollment.year = agency.year and v_enrollment.fullkey = agency.fullkey) 
inner join extracurr on ( extracurr.year = v_enrollment.year and extracurr.fullkey = v_enrollment.fullkey and extracurr.grade = v_enrollment.grade) 
inner join activities on (activities.code = extracurr.activity) 
where v_enrollment.race = 9 and v_enrollment.sex = 9 and v_enrollment.year = @year 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade = 94) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade = 94)) ) data 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade in ('90','91','92','93','94')) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))) ) data 
--and ((left(v_enrollment.fullkey,2) = @cesa and v_enrollment.grade in ('90','91','92','93','94')) 
and ((left(v_enrollment.fullkey,2) = @cesa and 
((right(v_enrollment.fullkey,1) <> 'X' and v_enrollment.grade = '94') or (right(v_enrollment.fullkey,1) = 'X' and v_enrollment.grade in ('90','91','92','93','94')))
) 
--or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))
and (right(left(v_enrollment.fullkey,8),2) <> '14' or (
--> changes with each
right(left(v_enrollment.fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_enrollment.year = agency.year and v_enrollment.agencykey = agency.agencykey) is not null 
))
) ) data 
--on (keys.year = data.year and keys.code = data.code and keys.fullkey = data.fullkey) 
on (keys.year = data.year and keys.code = data.code and keys.fullkey = data.fullkey and keys.gradelabel = data.gradelabel) 
left outer join agency on (agency.year = keys.year and agency.fullkey = keys.fullkey) 

where left(right(keys.fullkey,6),2) in ('03','04','4C','49') 	

-- test
--where keys.[District Number] = '3619'
--order by keys.name, left(keys.fullkey, 4), right(keys.fullkey, 4); 
order by keys.[District Number], keys.[School Number], keys.GradeLabel, keys.name 


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

