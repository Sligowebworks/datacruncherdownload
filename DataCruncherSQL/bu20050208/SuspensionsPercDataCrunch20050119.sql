select 
--grade, race, sex, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = (case when right(fullkey,1) <> 'X' then 
(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeLabel) when 'K-12' then 'Summary' else rtrim(GradeLabel) end) end), 
else (case when rtrim(grade) = '99' then 'Summary' when rtrim(grade) < 65 then 'Summary' else rtrim(GradeLabel) end) end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'grade_label' = rtrim(GradeLabel), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

--> changes with each

--v_suspensions.enrollment as 'total_enrollment_grades_7-12', v_suspensions.[Drop Outs] as 'drop_outs', v_suspensions.[Drop Out Rate] as 'drop_out_rate'
v_suspensions.[Total Enrollment Prek-12] as 'total_enrollment_Prek-12', isnull(v_suspensions.[Number of Students Suspended],0) as 'number_of_students_suspended', isnull(v_suspensions.[Suspension Percent],0) as 'suspension_percent'

--> changes with each
from v_suspensions
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2003' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_suspensions.year = agency.year and v_suspensions.agencykey = agency.agencykey) is not null 
))

and (
-- school level
(right(fullkey,1) <> 'X' and (race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','99')
or race <> '9' and sex = '9' and grade = '99' or race = '9' and sex <> '9' and grade = '99')
and ((grade >= (select distinct lowgrade from agency where  v_suspensions.year = agency.year and v_suspensions.agencykey = agency.agencykey) 
and grade <= (select distinct highgrade from agency where v_suspensions.year = agency.year and v_suspensions.agencykey = agency.agencykey))
or grade = '99'))
or 
-- district level - grade breakout and schooltypes for all races and all genders 
(right(fullkey,1) = 'X' and race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','70','71','72','73','99')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and race <> '9' and sex = '9' and grade in ('70','71','72','73','99')) or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and race = '9' and sex <> '9' and grade in ('70','71','72','73','99'))
)

-- must filter out cross join of race/gender - redundant?
and ((race = '9' and sex = '9') or (race <> '9' and sex = '9') or (race = '9' and sex <> '9'))
-- not filtering out combined groups?
-- and race <> '6'

-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and race = '9' and sex = '9' and grade = '99'


order by [District Number],[School Number], grade, race, sex
