select 

--gradecode, racecode, sexcode, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = ltrim(SchooltypeLabel2), 
--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
--else (case when rtrim(GradeCode) = 99 then 'Summary' when rtrim(GradeCode) < 65 then 'Summary' else rtrim(GradeShortLabel) end) end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'grade_label' = rtrim(GradeLabel), 
--'grade_label' = (case GradeCode when '99' then 'Grades K-12 Combined' else rtrim(GradeLabel) end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),
'disability' = DisabilityLabel, 


--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

v_attendance.[enrollment prek-12] as 'enrollment_prek-12', 
v_Attendance.[Actual Days Of Attendance] as 'actual_days_of_attendance', v_Attendance.[Possible Days Of Attendance] as 'possible_days_of_attendance', 
--v_Attendance.[Attendance Rate] as 'attendance_rate'
(case v_Attendance.[Possible Days Of Attendance] when '0.0' then '--' else cast(v_Attendance.[Attendance Rate] as char) end) as 'attendance_rate'

from v_AttendanceWWoDisSchoolDistState v_attendance 
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2004' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_attendance.year = agency.year and v_attendance.agencykey = agency.agencykey) is not null 
))

and left(right(fullkey,6),2) in ('03','04','49','4C')

and (
-- school level
(right(fullkey,1) <> 'X' and 
(racecode = '9' and sexcode = '9' and disabilitycode = '9' and gradecode in ('12','16','20','24','28','32','36','40','44','48','52','56','60','64','99')
or (racecode <> '9' and sexcode = '9' and disabilitycode = '9' and gradecode = '99')
or (racecode = '9' and sexcode <> '9' and disabilitycode = '9' and gradecode = '99')
or (racecode = '9' and sexcode = '9' and disabilitycode <> '9' and gradecode = '99')
)

and ((gradecode >= (select distinct lowgrade from agency where  v_attendance.year = agency.year and v_attendance.agencykey = agency.agencykey) 
and gradecode <= (select distinct highgrade from agency where v_attendance.year = agency.year and v_attendance.agencykey = agency.agencykey))
or gradecode = '99'))
or 

---- district level - grade breakout and schooltypes for all races and all genders 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and disabilitycode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','70','71','72','73','99')) or 
---- district level - schooltypes for races 
--(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and disabilitycode = '9' and gradecode in ('70','71','72','73','99')) or 
---- district level - schooltypes for gender 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and disabilitycode = '9' and gradecode in ('70','71','72','73','99')) or
---- district level - schooltypes for disability
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and disabilitycode <> '9' and gradecode in ('70','71','72','73','99'))

-- district level - grade breakout and schooltypes for all races and all genders 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and disabilitycode = '9' and gradecode in ('12','16','20','24','28','32','36','40','44','48','52','56','60','64','99')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and disabilitycode = '9' and gradecode = '99') or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and disabilitycode = '9' and gradecode = '99') or
-- district level - schooltypes for disability
(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and disabilitycode <> '9' and gradecode = '99')

)

-- must filter out cross join of race/gender - redundant?
and (
(racecode = '9' and sexcode = '9' and disabilitycode = '9') 
or (racecode <> '9' and sexcode = '9' and disabilitycode = '9') 
or (racecode = '9' and sexcode <> '9' and disabilitycode = '9')
or (racecode = '9' and sexcode = '9' and disabilitycode <> '9')
)
-- not filtering out combined groups?
and racecode <> '6'
and racecode <> '8'

--and (schooltypecode = '9' and gradecode in ('70','71','72','73','99') or schooltypecode <> '9' and gradecode not in ('70','71','72','73','99'))

--and fullkey = '013619040022'
--and [district number] = '3619'
--and racecode = '9' 
--and sexcode = '9' and disabilitycode = '9' --and gradecode = '99'

--and [school number] is null

order by [District Number], [School Number], SchooltypeLabel2, gradecode, racecode, sexcode, disabilitycode
