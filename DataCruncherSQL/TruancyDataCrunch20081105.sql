select 
schooltype, gradecode, 
--gradecode, racecode, sexcode, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
--else (case when rtrim(GradeCode) = '98' then 'Summary' when rtrim(GradeCode) < 65 then 'Summary' else rtrim(GradeShortLabel) end) end), 
'school_type' = (case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' when 9 then 'Summary' else '' end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

v_Truancy.[Total Enrollment (K-12)] as 'total_enrollment_K-12', 
v_Truancy.[Number of Students Habitually Truant] as 'number_of_students_habitually_truant', 
--v_Truancy.[Truancy Rate] as 'truancy_rate'
(case v_Truancy.[Total Enrollment (K-12)]  when 0 then '--' else cast(v_Truancy.[Truancy Rate] as char) end) as 'truancy_rate'
--(case v_Truancy.[Total Enrollment (K-12)]  when 0 then '--' else cast(cast(v_Truancy.[Truancy Rate] as numeric(8,4)) as char) end) as 'truancy_rate'

--v_truancy.[enrollment prek-12] as 'enrollment_prek-12', 
--v_truancy.[Actual Days Of Attendance] as 'actual_days_of_attendance', v_truancy.[Possible Days Of Attendance] as 'possible_days_of_attendance', 
--v_truancy.[Attendance Rate] as 'attendance_rate'


--> changes with each
from v_TruancySchoolDistState v_truancy
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2007' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_truancy.year = agency.year and v_truancy.agencykey = agency.agencykey) is not null 
))

and (
-- school level
(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','98')
or racecode <> '9' and sexcode = '9' and gradecode = '98' or racecode = '9' and sexcode <> '9' and gradecode = '98')
and ((gradecode >= (select distinct lowgrade from agency where  v_truancy.year = agency.year and v_truancy.agencykey = agency.agencykey) 
and gradecode <= (select distinct highgrade from agency where v_truancy.year = agency.year and v_truancy.agencykey = agency.agencykey))
or gradecode = '98'))
or 
-- district level - grade breakout and schooltypes for all races and all genders 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','74','75','76','77','98')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and gradecode in ('74','75','76','77','98')) or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and gradecode in ('74','75','76','77','98'))
)

-- must filter out cross join of race/gender - redundant?
and ((racecode = '9' and sexcode = '9') or (racecode <> '9' and sexcode = '9') or (racecode = '9' and sexcode <> '9'))
-- not filtering out combined groups?
-- and racecode <> '6'

-- fix for new table structure - 
and gradecode not in ('74','75','76','77')

and left(right(fullkey,6),2) in ('03','04','4C','49') 

-- test only
--and agencykey = '79187'
--and fullkey = '12017003XXXX'
--and fullkey = '01361903XXXX'
--and fullkey = '013619040022'
--and [district number] = '3619'
--and racecode = '9' and sexcode = '9' and gradecode = '98'

order by [District Number],[School Number], (case schooltype when 3 then ' High' when 4 then '  Mid/Jr Hi' when 5 then '  Mid/Jr Hi' when 6 then '    Elem' when 7 then ' El/Sec' when 9 then 'Summary' else '' end), gradecode, racecode, sexcode
