select 
--grade, race, sex, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = (case when right(fullkey,1) <> 'X' then 
(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
--else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
else (case when rtrim(grade) = '95' then 'Summary' when rtrim(grade) < 65 then 'Summary' else 
--rtrim(GradeLabel) 
rtrim(replace(GradeLabel, 'Grades 6-12 Combined', 'Grades 6-12'))
end) end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else 
--rtrim(GradeLabel) 
rtrim(replace(GradeLabel, 'Grades 6-12 Combined', 'Grades 6-12'))
end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),


--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

--v_Dropouts.enrollment as 'total_enrollment_grades_7-12', v_Dropouts.[Drop Outs] as 'drop_outs', v_Dropouts.[Drop Out Rate] as 'drop_out_rate'

v_COURSEWORK.Enrollment as 'total_enrolled_in_grades', 'subject' = WMAS_Description1, 
v_Coursework.Course as 'course_content', v_COURSEWORK.[# Who Took Course] as 'sum_of_students_taking_courses'

--> changes with each
from v_COURSEWORK
--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2008' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
where year = '2008' and fullkey = '01811103XXXX' and CESA = '01' 

--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_COURSEWORK.year = agency.year and v_COURSEWORK.agencykey = agency.agencykey) is not null 
))

and (

---- school level
--(right(fullkey,1) <> 'X' and (race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','95')
--or race <> '9' and sex = '9' and grade = '95' or race = '9' and sex <> '9' and grade = '95')
--and ((grade >= (select distinct lowgrade from agency where  v_dropouts.year = agency.year and v_dropouts.agencykey = agency.agencykey) 
--and grade <= (select distinct highgrade from agency where v_dropouts.year = agency.year and v_dropouts.agencykey = agency.agencykey))
--or grade = '95'))
--or 

-- district level - grade breakout and schooltypes for all races and all genders 
--(right(fullkey,1) = 'X' and race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','95')) or 
--(right(fullkey,1) = 'X' and sex = '9' and grade in ('52','56','60','64','94')) or 


(

(
right(fullkey,1) = 'X' 
--or 
--fullkey in (select distinct (left(fullkey,6) + '03XXXX') from tblAgencyFull where agencytype = '49')
)

and sex = '9' and grade in ('40','44','48','52','56','60','64','94')) or 


-- district level - schooltypes for races 
--(right(fullkey,1) = 'X' and race <> '9' and sex = '9' and grade in ('78','79','80','81','95')) or 
-- district level - schooltypes for gender 
--(right(fullkey,1) = 'X' and race = '9' and sex <> '9' and grade in ('78','79','80','81','95'))
--(right(fullkey,1) = 'X' and sex <> '9' and grade in ('52','56','60','64','94'))


(
(
right(fullkey,1) = 'X' 
--or 
--fullkey in (select distinct (left(fullkey,6) + '03XXXX') from tblAgencyFull where agencytype = '49')
)

and sex <> '9' and grade in ('40','44','48','52','56','60','64','94')) 


)

-- must filter out cross join of race/gender - redundant?
--and ((race = '9' and sex = '9') or (race <> '9' and sex = '9') or (race = '9' and sex <> '9'))
and ((sex = '9') or (sex <> '9'))
-- not filtering out combined groups?
-- and race <> '6'

--and coursetypeid in ('1','2','3','4') 
-- this should be all that changes between the different course types
and coursetypeid = '2'

and wmasid1 in ('4','8','10','11','1','2','3','5','6','7','9','12','13')


-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and race = '9' and sex = '9' and grade = '95'


order by [District Number],[School Number], grade, sex
