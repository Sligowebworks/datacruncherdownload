select 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = (case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else 'Summary' end), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'grade_label' = rtrim(GradeLabel), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

--> changes with each

v_SuspExpIncidents.Enrollment as 'enrollment_PreK-12', 
IncidentCountTotalWeaponDrug as 'weapon_drug_number_of_incidents', 
(case v_SuspExpIncidents.Enrollment when 0 then '--' else cast(WeaponDrugIncidentRate as char) end) as 'weapon_drug_incidents_per_1000_students', 
IncidentCountTotalNonWeaponDrug as 'not_weapon_drug_number_of_incidents', 
(case v_SuspExpIncidents.Enrollment when 0 then '--' else cast(NonWeaponDrugIncidentRate as char) end) as 'not_weapon_drug_incidents_per_1000_students'

--> changes with each
from v_SuspExpIncidentsWWoDisSchoolDistState v_suspexpincidents 
--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
where year = '2008' and fullkey <> 'XXXXXXXXXXXX' and CESA = '02' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  v_SuspExpIncidents.year = agency.year and v_SuspExpIncidents.agencykey = agency.agencykey) is not null 
))

and (
-- school level

(race = '9' and gender = '9' and DisabilityCode = '9' and grade in ('12','16','20','24','28','32','36','40','44','48','52','56','60','64','99'))
or 
(race <> '9' and gender = '9' and DisabilityCode = '9' and grade = '99')
or 
(race = '9' and gender <> '9' and DisabilityCode = '9' and grade = '99')
or 
(race = '9' and gender = '9' and DisabilityCode <> '9' and grade = '99')
)

and 
((grade >= (select distinct lowgrade from tblAgencyFull agency where  v_SuspExpIncidents.year = agency.year and v_SuspExpIncidents.agencykey = agency.agencykey) 
and grade <= (select distinct highgrade from tblAgencyFull agency where v_SuspExpIncidents.year = agency.year and v_SuspExpIncidents.agencykey = agency.agencykey))
or grade = '99')


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
and fullkey = '023269040150'
--and [district number] = '3619'
--and race = '9' and sex = '9' and grade = '99'

order by [District Number],[School Number], schooltype, grade, race, SexCode, DisabilityCode
