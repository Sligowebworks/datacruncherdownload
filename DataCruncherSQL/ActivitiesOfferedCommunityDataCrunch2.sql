create procedure procActivitiesOfferedCommunityDataCrunch
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
--else (case when rtrim(gradecode) = '94' then 'Summary' when rtrim(gradecode) < 65 then 'Summary' else rtrim(keys.GradeShortLabel) end) end), 
else (case when rtrim(gradecode) = '96' then 'Summary' when rtrim(gradecode) < 65 then 'Summary' else rtrim(keys.GradeShortLabel) end) end), 
keys.charter, keys.[District Name] as 'district_name', 
keys.[School Name] as 'school_name', keys.GradeLabel as 'grade_label', keys.RaceLabel as 'race_ethnicity', keys.SexLabel as 'gender', keys.name as 'activity_type', 
isnull(keys.Enrollment,0) AS 'enrollment_grades_9-12', 

'offerings_per_school_average' = CASE WHEN keys.suppressed is null THEN '0' WHEN keys.suppressed is not null THEN cast(isnull(Numoffer,0) as char(10)) END

from 
(select distinct v_enrollment.year, v_enrollment.AgencyKey, v_enrollment.CESA, v_enrollment.[District Number], v_enrollment.[School Number], v_enrollment.schooltype, v_enrollment.charter, v_enrollment.[District Name], v_enrollment.[School Name], 
v_enrollment.GradeCode, v_enrollment.GradeLabel, v_enrollment.GradeShortLabel, v_enrollment.RaceLabel, v_enrollment.SexLabel, activities.code, activities.name, enrollment , suppressed, v_enrollment.fullkey 
from activities, v_enrollment left outer join agency on (v_enrollment.year = agency.year and v_enrollment.fullkey = agency.fullkey) 

where activities.code in ('re','vo') and v_enrollment.race = 9 and v_enrollment.sex = 9 and v_enrollment.year = @year 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade = 94) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade = 94)) ) keys 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade in ('90','91','92','93','94')) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))) ) keys 

--and ((left(v_enrollment.fullkey,2) = @cesa and v_enrollment.grade in ('82','83','84','85','96')) 
and ((left(v_enrollment.fullkey,2) = @cesa and 
((right(v_enrollment.fullkey,1) <> 'X' and v_enrollment.grade = '96') or (right(v_enrollment.fullkey,1) = 'X' and v_enrollment.grade in ('82','83','84','85','96')))
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
inner join sponsacts on ( sponsacts.year = v_enrollment.year and sponsacts.fullkey = v_enrollment.fullkey and sponsacts.grade = v_enrollment.grade) 
inner join activities on (activities.code = sponsacts.activity) 

where v_enrollment.race = 9 and v_enrollment.sex = 9 and v_enrollment.year = @year 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade = 94) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade = 94)) ) data 
--and ((v_enrollment.fullkey = '01361903xxxx' and v_enrollment.grade in ('90','91','92','93','94')) or (v_enrollment.fullkey = 'xxxxxxxxxxxx' and v_enrollment.grade in ('90','91','92','93','94'))) ) data 

--and ((left(v_enrollment.fullkey,2) = @cesa and v_enrollment.grade in ('82','83','84','85','96')) 
and ((left(v_enrollment.fullkey,2) = @cesa and 
((right(v_enrollment.fullkey,1) <> 'X' and v_enrollment.grade = '96') or (right(v_enrollment.fullkey,1) = 'X' and v_enrollment.grade in ('82','83','84','85','96')))
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


-- test
--where keys.[District Number] = '3619'


--order by keys.name, left(keys.fullkey, 4), right(keys.fullkey, 4); 
order by keys.[District Number], keys.[School Number], keys.GradeLabel, keys.name 
