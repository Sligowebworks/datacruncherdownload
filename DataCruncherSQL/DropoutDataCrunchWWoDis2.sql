select 
--gradecode, racecode, sexcode, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 

-- new code here
--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
--else (case when rtrim(GradeCode) = '95' then 'Summary' when rtrim(GradeCode) < 65 then 'Summary' else rtrim(GradeShortLabel) end) end), 

'school_type' = SchooltypeLabel, 

charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

'disability' = [DisabilityLabel], 

--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

--v_HSCWWoDisSchoolDistState.enrollment as 'total_enrollment_grades_7-12', v_HSCWWoDisSchoolDistState.[Drop Outs] as 'drop_outs', 
----v_HSCWWoDisSchoolDistState.[Drop Out Rate] as 'drop_out_rate'
--(case v_HSCWWoDisSchoolDistState.enrollment when 0 then '--' else cast(v_HSCWWoDisSchoolDistState.[Drop Out Rate] as char) end) as 'drop_out_rate'

'total_enrollment_grades_7-12' = [enrollment], 
'students_expected_to_complete_the_school_term' = [Students expected to complete the school term], 
'students_who_completed_the_school_term' = [Students who completed the school term], 
'number_drop_outs' = [Drop Outs], 
'drop_out_rate' = [Drop Out Rate] 

--> changes with each
from v_DropoutsWWoDisSchoolDistState
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2004' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' and fullkey = '013619040022'
--and right(left(fullkey,8),2) <> '14' 

and 
(
	(gradecode = '95' and racecode = '9' and sexcode = '9' and disabilitycode = '9')
	or
	(gradecode in ('44','48','52','56','60','64') and racecode = '9' and sexcode = '9' and disabilitycode = '9')
	or 
	(gradecode = '95' and racecode <> '9' and sexcode = '9' and disabilitycode = '9')
	or
	(gradecode = '95' and racecode = '9' and sexcode <> '9' and disabilitycode = '9')
	or
	(gradecode = '95' and racecode = '9' and sexcode = '9' and disabilitycode <> '9')
)

-- exclude below?
and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_DropoutsWWoDisSchoolDistState.year = agency.year and v_DropoutsWWoDisSchoolDistState.agencykey = agency.agencykey) is not null 
))

/*
and (
-- school level
--(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','95')
(right(fullkey,1) <> 'X' and 

(racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','95')
or 
(racecode <> '9' and sexcode = '9' and gradecode = '95') 
or 
(racecode = '9' and sexcode <> '9' and gradecode = '95')

)
and 
(
(gradecode >= (select distinct lowgrade from agency where  v_HSCWWoDisSchoolDistState.year = agency.year and v_HSCWWoDisSchoolDistState.agencykey = agency.agencykey) 
and gradecode <= (select distinct highgrade from agency where v_HSCWWoDisSchoolDistState.year = agency.year and v_HSCWWoDisSchoolDistState.agencykey = agency.agencykey)
)
or gradecode = '95'))

or 

-- district level - grade breakout and schooltypes for all races and all genders 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','95')) or 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','78','79','80','81','95')) or 
-- district level - schooltypes for races 
(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and gradecode in ('78','79','80','81','95')) or 
-- district level - schooltypes for gender 
(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and gradecode in ('78','79','80','81','95'))
)

-- must filter out cross join of race/gender - redundant?
and ((racecode = '9' and sexcode = '9') or (racecode <> '9' and sexcode = '9') or (racecode = '9' and sexcode <> '9'))
-- not filtering out combined groups?
-- and racecode <> '6'

*/

-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and racecode = '9' and sexcode = '9' and gradecode = '95'


order by year, fullkey, SchooltypeLabel, [District Number],[School Number], gradecode, racecode, sexcode
