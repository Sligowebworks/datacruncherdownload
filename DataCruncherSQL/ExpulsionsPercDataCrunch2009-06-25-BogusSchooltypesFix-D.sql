select 
--grade, race, sex, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeLabel) when 'K-12' then 'Summary' else rtrim(GradeLabel) end) end), 
--else (case when rtrim(grade) = '99' then 'Summary' when rtrim(grade) < 65 then 'Summary' else rtrim(GradeLabel) end) end), 
'school_type' = (case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' when 9 then 'Summary' else '' end),  
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'grade_label' = rtrim(GradeLabel), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),
'disability' = rtrim(DisabilityLabel), 

--> changes with each

--v_expulsions.enrollment as 'total_enrollment_grades_7-12', v_expulsions.[Drop Outs] as 'drop_outs', v_expulsions.[Drop Out Rate] as 'drop_out_rate'
v_expulsions.[Total Enrollment Prek-12] as 'total_enrollment_Prek-12', 
isnull(v_expulsions.[Number of Students Expelled],0) as 'number_of_students_expelled', 
(case v_expulsions.[Total Enrollment Prek-12] when 0 then '--' else cast(isnull(v_expulsions.[Expulsion Percent],0) as char) end) as 'expulsion_percent'

--> changes with each
from v_ExpulsionsDisDnlFiles v_expulsions
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2002' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

-- strip out counties and CESAs from new tblAgencyFull-based view 
and right(left(fullkey,8),2) <> '02' 
and right(left(fullkey,8),2) <> '01' 

-- include only certain private schools per Jean 
and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_expulsions.year = agency.year and v_expulsions.agencykey = agency.agencykey) is not null 
))

and 
-- school level
((
right(fullkey,1) <> 'X' 
	and (
	race = '9' and sex = '9' and disabilitycode = '9' and grade in ('12','16','20','24','28','32','36','40','44','48','52','56','60','64','99')
	or 
	race <> '9' and sex = '9' and disabilitycode = '9' and grade = '99' 
	or 
	race = '9' and sex <> '9' and disabilitycode = '9' and grade = '99'
	or 
	race = '9' and sex = '9' and disabilitycode <> '9' and grade = '99'
	)
and ((grade >= (select distinct lowgrade from agency where  v_expulsions.year = agency.year and v_expulsions.agencykey = agency.agencykey) 
and grade <= (select distinct highgrade from agency where v_expulsions.year = agency.year and v_expulsions.agencykey = agency.agencykey))
or grade = '99'
))

or 
-- district level - grade breakout and schooltypes for all races and all genders 
(right(fullkey,1) = 'X' and race = '9' and sex = '9' and disabilitycode = '9' and grade in ('12','16','20','24','28','32','36','40','44','48','52','56','60','64','99')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and race <> '9' and sex = '9' and disabilitycode = '9' and grade = '99') or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and race = '9' and sex <> '9' and disabilitycode = '9' and grade = '99') or
-- district level - schooltypes for disability 
(right(fullkey,1) = 'X' and race = '9' and sex = '9' and disabilitycode <> '9' and grade = '99')
)

-- must filter out cross join of race/gender - redundant?
and ((race = '9' and sex = '9' and disabilitycode = '9') or (race <> '9' and sex = '9' and disabilitycode = '9') or (race = '9' and sex <> '9' and disabilitycode = '9') or (race = '9' and sex = '9' and disabilitycode <> '9'))
-- not filtering out combined groups?
-- and race <> '6'

and left(right(fullkey,6),2) in ('03','04','4C','49') 

and 
(
	-- if school row, full grade breakouts - no need to specify schooltype here? 
	(schooltype in ('3','5','6','7','9') and right(fullkey,1) <> 'X')
	or 
	-- if district row and schooltype is summary, full grade breakouts
	(schooltype = '9' and right(fullkey,1) = 'X')
	or 
	-- if district row and schooltype isn't summary, no grade breakouts
	(schooltype <> '9' and right(fullkey,1) = 'X' and grade = '99')
)


-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and race = '9' and sex = '9' and disabilitycode = '9' 
--and grade = '99'


order by [District Number],[School Number], schooltype, grade, race, sex, disabilitycode
