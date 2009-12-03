--> everything above the select needs to be cut for the DTS to run this
-- be sure to change schooltypes AND '99'/'98'/etc...DISTRICT LEVEL ONLY 
-- check retention/dropouts/truancy/attendance re above
-- susp/exp uses GradeLabel instead of GradeShortLabel - Droputs may be better template

select 
--grade, race, sex, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 

--> special override - no grade/race/sex/schooltypes
--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeLabel) when 'K-12' then 'Summary' else rtrim(GradeLabel) end) end), 
--else (case when rtrim(grade) = '99' then 'Summary' when rtrim(grade) < 65 then 'Summary' else rtrim(GradeLabel) end) end), 
'school_type' = 'Summary', 
--> end special override 


charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = (case rtrim(GradeLabel) when 'Grades PreK-12' then 'Grades K-12' else rtrim(GradeLabel) end), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),

--> changes with each
--> may need to make 'as' into '=' for DTS to run right
[Total # Students without Disabilities Expelled] as 'total_number_students_without_disabilities_expelled', 
[Total # Students without Disabilities Offered Post Expulsion Services] as 'total_number_students_without_disabilities_offered_post_expulsion_services', 
([Total # Students without Disabilities Expelled]-[Total # Students without Disabilities Offered Post Expulsion Services]) as 'total_number_students_without_disabilities_not_offered_post_expulsion_services' ,
[% of Expelled Students without Disabilities Offered Post Expulsion Services] as 'percent_of_expelled_students_without_disabilities_offered_post_expulsion_services'

--> changes with each
from vexpulsionservicesandreturns  
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2003' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
--and right(left(fullkey,8),2) <> '14' 

and (right(left(fullkey,8),2) <> '14' or (
--> changes with each
right(left(fullkey,8),6) = '361914' and (select distinct PartSchIndic from agency where  vexpulsionservicesandreturns .year = agency.year and vexpulsionservicesandreturns .agencykey = agency.agencykey) is not null 
))

--> special override - no grade/race/sex/schooltypes
--and (
---- school level
---- DON'T CHANGE 99 HERE
--(right(fullkey,1) <> 'X' and (race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','99')
--or race <> '9' and sex = '9' and grade = '99' or race = '9' and sex <> '9' and grade = '99')
--and ((grade >= (select distinct lowgrade from agency where  vexpulsionservices.year = agency.year and vexpulsionservices.agencykey = agency.agencykey) 
--and grade <= (select distinct highgrade from agency where vexpulsionservices.year = agency.year and vexpulsionservices.agencykey = agency.agencykey))
--or grade = '99'))
--or 
---- district level - grade breakout and schooltypes for all races and all genders 
---- be sure to change schooltypes AND '99'/'98'/etc...DISTRICT LEVEL ONLY - check retention/dropouts/truancy/attendance/suspensions
--(right(fullkey,1) = 'X' and race = '9' and sex = '9' and grade in ('16','20','24','28','32','36','40','44','48','52','56','60','64','70','71','72','73','99')) or 
---- district level - schooltypes for races 
--(right(fullkey,1) = 'X' and race <> '9' and sex = '9' and grade in ('70','71','72','73','99')) or 
---- district level - schooltypes for gender 
--(right(fullkey,1) = 'X' and race = '9' and sex <> '9' and grade in ('70','71','72','73','99'))
--)
--
---- must filter out cross join of race/gender - redundant?
--and ((race = '9' and sex = '9') or (race <> '9' and sex = '9') or (race = '9' and sex <> '9'))
--
---- not filtering out combined groups?
---- and race <> '6'
--
--> end special override 

-- test only
--and fullkey = '013619040022'
--and [district number] = '3619'
--and race = '9' and sex = '9' and grade = '99'

--> special override - no grade/race/sex/schooltypes
--order by [District Number],[School Number], grade, race, sex
order by [District Number],[School Number]
