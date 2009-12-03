select 
--gradecode, racecode, sexcode, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = (case when right(fullkey,1) <> 'X' then 
(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
else (case when rtrim(Grade) = '96' then 'Summary' when rtrim(Grade) < 65 then 'Summary' else rtrim(GradeLabel) end) end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

--v_Dropouts.enrollment as 'total_enrollment_grades_7-12', v_Dropouts.[Drop Outs] as 'drop_outs', v_Dropouts.[Drop Out Rate] as 'drop_out_rate'

--vact.enrollment as 'enrollment_grade_12', vact.Pupilcount as 'number_tested', [Perc Tested] as 'percent_tested', vACT.Reading as 'average_score_reading', 
--vACT.[English] as 'average_score_english', vACT.[Math] as 'average_score_math', vACT.[Science] as 'average_score_science', vACT.[Composite] as 'average_score_summary'

v_AP_TESTS.Enrollment as 'enrollment_grades_9-12', v_AP_TESTS.[# Taking Exams] as 'number_taking_exams', v_AP_TESTS.[% Taking Exams] as 'percent_taking_exams', 
v_AP_TESTS.[# Exams Taken] as 'number_exams_taken', v_AP_TESTS.[# Exams Passed] as 'number_exams_passed_score_of_3_or_above', 
v_AP_TESTS.[% of Exams Passed] as 'percent_exams_passed_score_of_3_or_above'

--> changes with each
from v_AP_TESTS

where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '1998' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_AP_TESTS.year = agency.year and v_AP_TESTS.agencykey = agency.agencykey) is not null 
))

and (
-- school level
--(right(fullkey,1) <> 'X' and (race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','96')
--or (race <> '9' and sex = '9' and grade = '96') or (race = '9' and sex <> '9' and grade = '96'))
--and ((grade >= (select distinct lowgrade from agency where  v_AP_TESTS.year = agency.year and v_AP_TESTS.agencykey = agency.agencykey) 
--and grade <= (select distinct highgrade from agency where v_AP_TESTS.year = agency.year and v_AP_TESTS.agencykey = agency.agencykey))
--or grade = '96'))
--or 
-- district level - grade breakout and schooltypes for all races and all genders 
--(right(fullkey,1) = 'X' and race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','96')) or 
(right(fullkey,1) = 'X' and race = '9' and sex = '9' and grade in ('78','79','80','81','96')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and race <> '9' and sex = '9' and grade in ('78','79','80','81','96')) or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and race = '9' and sex <> '9' and grade in ('78','79','80','81','96'))
)

-- must filter out cross join of race/gender - redundant?
and ((race = '9' and sex = '9') or (race <> '9' and sex = '9') or (race = '9' and sex <> '9'))
-- not filtering out combined groups?
and race <> '6'

-- special for AP
and examcode = 99 
and grade in ('78','79','80','81','96')

-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and racecode = '9' and sexcode = '9' and gradecode = '95'


order by [District Number],[School Number], grade, race, sex
