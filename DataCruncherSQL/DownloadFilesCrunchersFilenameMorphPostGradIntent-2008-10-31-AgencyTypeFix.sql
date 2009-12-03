select 

--gradecode, racecode, sexcode, 
v_post_grad_intent.year, 'agency_key' = v_post_grad_intent.AgencyKey, v_post_grad_intent.CESA, 'district_number' = v_post_grad_intent.[District Number],'school_number' = v_post_grad_intent.[School Number], 'agency_type' = left(right(v_post_grad_intent.fullkey,6),2), 
'school_type' = (case when right(v_post_grad_intent.fullkey,1) <> 'X' then 
(case v_post_grad_intent.schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
--else (case when rtrim(v_post_grad_intent.Grade) = '64' then 'Summary' when rtrim(v_post_grad_intent.Grade) < 65 then 'Summary' else rtrim(v_post_grad_intent.GradeLabel) end) end), 
else 'Summary' end), 
charter, 'district_name' = ltrim(v_post_grad_intent.[District Name]), 'school_name' = ltrim(v_post_grad_intent.[School Name]), 
'grade_label' = (case rtrim(v_post_grad_intent.GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(v_post_grad_intent.GradeLabel) end), 
'race_ethnicity' = rtrim(v_post_grad_intent.RaceLabel), 'gender' = rtrim(v_post_grad_intent.SexLabel),

--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

[Grade 12 Enrollment] as 'grade_12_enrollment', [Number of Graduates] as 'number_of_graduates', [Number 4-Year College] as 'number_4-year_college', 
[% 4-Year College] as 'percent_4-year_college', [Number Voc/Tech College] as 'number_voc_tech_college', [% Voc/Tech College] as 'percent_voc_tech_college', 
[Number Job Training] as 'number_job_training', [% Job Training] as 'percent_job_training', [Number Employment] as 'number_employment', 
[% Employment] as 'percent_employment', [Number Military] as 'number_military', [% Military] as 'percent_military', [Number Seeking Employment] as 'number_seeking_employment', 
[% Seeking Employment] as 'percent_seeking_employment', [Number Other Plans] as 'number_other_plans', [% Other Plans] as 'percent_other_plans', 
[Number Undecided] as 'number_undecided', [% Undecided] as 'percent_undecided', [Number No Response] as 'number_no_response', [% No Response] as 'percent_no_response', 
[Number Miscellaneous] as 'number_miscellaneous', [% Miscellaneous] as 'percent_miscellaneous'

--> changes with each

from v_post_grad_intent

where v_post_grad_intent.year = ? and v_post_grad_intent.fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where v_post_grad_intent.year = '2007' and v_post_grad_intent.fullkey <> 'XXXXXXXXXXXX' and v_post_grad_intent.CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(v_post_grad_intent.fullkey,8),2) <> '14' or (
--> changes with each
right(left(v_post_grad_intent.fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where v_post_grad_intent.year = agency.year and v_post_grad_intent.agencykey = agency.agencykey) is not null 
))

--and (
---- school level
--(right(v_post_grad_intent.fullkey,1) <> 'X' and (v_post_grad_intent.race = '9' and v_post_grad_intent.sex = '9' and v_post_grad_intent.grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','64')
--or (v_post_grad_intent.race <> '9' and v_post_grad_intent.sex = '9' and v_post_grad_intent.grade = '64') or (v_post_grad_intent.race = '9' and v_post_grad_intent.sex <> '9' and v_post_grad_intent.grade = '64'))
--and ((v_post_grad_intent.grade >= (select distinct lowgrade from agency where  v_post_grad_intent.year = agency.year and v_post_grad_intent.agencykey = agency.agencykey) 
--and v_post_grad_intent.grade <= (select distinct highgrade from agency where v_post_grad_intent.year = agency.year and v_post_grad_intent.agencykey = agency.agencykey))
---- special for grad rate 
----or v_post_grad_intent.grade = '64'))
--and v_post_grad_intent.grade = '64'))
--or 
---- district level - grade breakout and schooltypes for all races and all genders 
--(right(v_post_grad_intent.fullkey,1) = 'X' and v_post_grad_intent.race = '9' and v_post_grad_intent.sex = '9' and v_post_grad_intent.grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','64')) or 
---- district level - schooltypes for races 
--(right(v_post_grad_intent.fullkey,1) = 'X' and v_post_grad_intent.race <> '9' and v_post_grad_intent.sex = '9' and v_post_grad_intent.grade in ('78','79','80','81','64')) or 
---- district level - schooltypes for gender 
--(right(v_post_grad_intent.fullkey,1) = 'X' and v_post_grad_intent.race = '9' and v_post_grad_intent.sex <> '9' and v_post_grad_intent.grade in ('78','79','80','81','64'))
--)

-- must filter out cross join of race/gender - redundant?
and ((v_post_grad_intent.race = '9' and v_post_grad_intent.sex = '9') or (v_post_grad_intent.race <> '9' and v_post_grad_intent.sex = '9') or (v_post_grad_intent.race = '9' and v_post_grad_intent.sex <> '9'))
-- not filtering out combined groups?

-- special for grad rate 
and race not in ('6','8')
--and v_post_grad_intent.grade = '64'

--and v_post_grad_intent.[district number] = '3619'
and left(right(v_post_grad_intent.fullkey,6),2) in ('03','04','4C','49') 

-- test only
-- and v_post_grad_intent.[district number] = '9901'
--and fullkey = '013619040022'
--and racecode = '9' and sexcode = '9' and gradecode = '95'


order by v_post_grad_intent.[District Number], v_post_grad_intent.[School Number], v_post_grad_intent.race, v_post_grad_intent.sex
