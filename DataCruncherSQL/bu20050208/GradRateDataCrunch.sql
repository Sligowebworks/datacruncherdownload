select 
--gradecode, racecode, sexcode, 
v_enrollment.year, 'agency_key' = v_enrollment.AgencyKey, v_enrollment.CESA, 'district_number' = v_enrollment.[District Number],'school_number' = v_enrollment.[School Number], 'agency_type' = left(right(v_enrollment.fullkey,6),2), 
'school_type' = (case when right(v_enrollment.fullkey,1) <> 'X' then 
(case v_enrollment.schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
else (case when rtrim(v_enrollment.Grade) = '64' then 'Summary' when rtrim(v_enrollment.Grade) < 65 then 'Summary' else rtrim(v_enrollment.GradeLabel) end) end), 
charter, 'district_name' = ltrim(v_enrollment.[District Name]), 'school_name' = ltrim(v_enrollment.[School Name]), 
'grade_label' = (case rtrim(v_enrollment.GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(v_enrollment.GradeLabel) end), 
'race_ethnicity' = rtrim(v_enrollment.RaceLabel), 'gender' = rtrim(v_enrollment.SexLabel),

--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

--v_Dropouts.enrollment as 'total_enrollment_grades_7-12', v_Dropouts.[Drop Outs] as 'drop_outs', v_Dropouts.[Drop Out Rate] as 'drop_out_rate'

--vact.enrollment as 'enrollment_grade_12', vact.Pupilcount as 'number_tested', [Perc Tested] as 'percent_tested', vACT.Reading as 'average_score_reading', 
--vACT.[English] as 'average_score_english', vACT.[Math] as 'average_score_math', vACT.[Science] as 'average_score_science', vACT.[Composite] as 'average_score_summary'

--v_AP_TESTS.Enrollment as 'enrollment_grades_9-12', v_AP_TESTS.[# Taking Exams] as 'number_taking_exams', v_AP_TESTS.[% Taking Exams] as 'percent_taking_exams', 
--v_AP_TESTS.[# Exams Taken] as 'number_exams_taken', v_AP_TESTS.[# Exams Passed] as 'number_exams_passed', 
--v_AP_TESTS.[% of Exams Passed] as 'percent_exams_passed_score_of_3_or_above'

v_enrollment.enrollment as 'total_enrollment_grade_12', (case when v_enrollment.suppressed < 0 then '*' else cast(isnull(graduates,0) as varchar) end) as 'number_of_graduates', 
(case when v_enrollment.suppressed < 0 then '*' else cast(isnull(dropoutcohorts,0) as varchar) end) as 'number_of_cohort_dropouts', 
'graduation_rate' = (case (isnull(graduates,0) + isnull(dropoutcohorts,0)) when 0 then '--'  
else cast(cast((isnull(graduates,0) / (isnull(graduates,0) + isnull(dropoutcohorts,0)) *100) as decimal(6,2)) as char) end)

--> changes with each
from v_enrollment left outer join grad on (v_enrollment.year = grad.year and v_enrollment.race = grad.race and v_enrollment.sex = grad.sex and grad.fullkey = v_enrollment.fullkey ) 

where v_enrollment.year = ? and v_enrollment.fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where v_enrollment.year = '1998' and v_enrollment.fullkey <> 'XXXXXXXXXXXX' and v_enrollment.CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(v_enrollment.fullkey,8),2) <> '14' or (
--> changes with each
right(left(v_enrollment.fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  grad.year = agency.year and grad.agencykey = agency.agencykey) is not null 
))

and (
-- school level
(right(v_enrollment.fullkey,1) <> 'X' and (v_enrollment.race = '9' and v_enrollment.sex = '9' and v_enrollment.grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','64')
or (v_enrollment.race <> '9' and v_enrollment.sex = '9' and v_enrollment.grade = '64') or (v_enrollment.race = '9' and v_enrollment.sex <> '9' and v_enrollment.grade = '64'))
and ((v_enrollment.grade >= (select distinct lowgrade from agency where  grad.year = agency.year and grad.agencykey = agency.agencykey) 
and v_enrollment.grade <= (select distinct highgrade from agency where grad.year = agency.year and grad.agencykey = agency.agencykey))
-- special for grad rate 
--or v_enrollment.grade = '64'))
and v_enrollment.grade = '64'))
or 
-- district level - grade breakout and schooltypes for all races and all genders 
(right(v_enrollment.fullkey,1) = 'X' and v_enrollment.race = '9' and v_enrollment.sex = '9' and v_enrollment.grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','64')) or 
-- district level - schooltypes for races 
(right(v_enrollment.fullkey,1) = 'X' and v_enrollment.race <> '9' and v_enrollment.sex = '9' and v_enrollment.grade in ('78','79','80','81','64')) or 
-- district level - schooltypes for gender 
(right(v_enrollment.fullkey,1) = 'X' and v_enrollment.race = '9' and v_enrollment.sex <> '9' and v_enrollment.grade in ('78','79','80','81','64'))
)

-- must filter out cross join of race/gender - redundant?
and ((v_enrollment.race = '9' and v_enrollment.sex = '9') or (v_enrollment.race <> '9' and v_enrollment.sex = '9') or (v_enrollment.race = '9' and v_enrollment.sex <> '9'))
-- not filtering out combined groups?

-- special for grad rate 
and racecode not in ('6','8')
and v_enrollment.grade = '64'

-- test only
--and fullkey = '013619040022'
--and v_enrollment.[district number] = '3619'
--and racecode = '9' and sexcode = '9' and gradecode = '95'


order by v_enrollment.[District Number], v_enrollment.[School Number], v_enrollment.grade, v_enrollment.race, v_enrollment.sex
