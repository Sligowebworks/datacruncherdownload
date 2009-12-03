select 

--grade, gradecode, 
--racecode, sexcode, 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 

--'school_type' = (case when right(fullkey,1) <> 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' else '' end) 
----else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
--else (case when rtrim(GradeCode) = '99' then 'Summary' when rtrim(GradeCode) < 65 then 'Summary' 
--else 
--cast(replace(rtrim(GradeShortLabel),'PreK-12','K-12') as char)
--end) end), 

'school_type' = (case when right(fullkey,1) <> 'X' or right(fullkey,1) = 'X' then 
--(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' when 9 then 'Summary' else GradeShortLabel end) 
(case schooltype when 3 then 'High' when 4 then 'Mid/Jr Hi' when 5 then 'Mid/Jr Hi' when 6 then 'Elem' when 7 then 'El/Sec' when 9 then 'Summary' else 
-- if null - ugly trapping of wrong word, but seems to work - for this dataset only....
(case rtrim(GradeShortLabel) when 'Prek-12' then 'Summary' else GradeShortLabel end) end) 
--else (case rtrim(GradeShortLabel) when 'K-12' then 'Summary' else rtrim(GradeShortLabel) end) end), 
else 
--(case when rtrim(GradeCode) = '99' then 'Summary' when rtrim(GradeCode) < 65 then 'Summary' 
'Summary' 
--else 
--'Summary' 
--cast(replace(rtrim(GradeShortLabel),'PreK-12','K-12') as char)
--end) 
end), 

charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = rtrim(GradeLabel), 
'race_ethnicity' = rtrim(RaceLabel), 'gender' = rtrim(SexLabel),


--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

--enrollment as 'enrollment_prek-12', 
--[number eligible for subsidized lunch] as 'number_eligible_for_subsidized_lunch', 
--(case  enrollment when 0 then '--' else cast([% eligible for subsidized lunch] as char) end) as 'percent_eligible_for_subsidized_lunch', 
--[number not eligible/no data] as 'number_not_eligible_for_subsidized_lunch_or_no_data', 
--(case  enrollment when 0 then '--' else cast([% not eligible/no data] as char) end) as 'percent_not_eligible_for_subsidized_lunch_or_no_data'

enrollment as 'enrollment_prek-12', 

[number eligible for subsidized lunch] as 'number_eligible_for_subsidized_lunch', 

(case enrollment when 0 then '--' else cast([% eligible for subsidized lunch] as char) end) as 'percent_eligible_for_subsidized_lunch', 

[number not eligible/no data] as 'number_not_eligible_for_subsidized_lunch_or_no_data', 

(case  enrollment when 0 then '--' else cast([% not eligible/no data] as char) end) as 'percent_not_eligible_for_subsidized_lunch_or_no_data'

from v_ErateRollupsWithSchoolTypes2

--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
where year = '2009' and fullkey <> 'XXXXXXXXXXXX' and CESA = '04'

-- filters out schooltype rows that shows 0 at school level 
and 
(grade = '99' 
or grade = (case right(fullkey,1) when 'X' then '70' else '99' end) 
or grade = (case right(fullkey,1) when 'X' then '71' else '99' end)
or grade = (case right(fullkey,1) when 'X' then '72' else '99' end) 
or grade = (case right(fullkey,1) when 'X' then '73' else '99' end))


--and right(left(fullkey,8),2) <> '14' 

--and right(left(fullkey,8),2) <> '14'

and (right(left(fullkey,8),2) <> '14' 
or (
--> changes with each
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_ErateRollupsWithSchoolTypes2.year = agency.year and v_ErateRollupsWithSchoolTypes2.agencykey = agency.agencykey) is not null 
))


--and (
---- school level
--(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','99')
----(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','99')
--or (racecode <> '9' and sexcode = '9' and gradecode = '99') or (racecode = '9' and sexcode <> '9' and gradecode = '99'))
--and ((gradecode >= (select distinct lowgrade from agency where  v_eraterollups.year = agency.year and v_eraterollups.agencykey = agency.agencykey) 
--and gradecode <= (select distinct highgrade from agency where v_eraterollups.year = agency.year and v_eraterollups.agencykey = agency.agencykey))
--or gradecode = '99'))
--or 
---- district level - grade breakout and schooltypes for all races and all genders 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','70','71','72','73','99')) or 
----(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','78','79','80','81','99')) or 
---- district level - schooltypes for races 
--(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and gradecode in ('70','71','72','73','99')) or 
---- district level - schooltypes for gender 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and gradecode in ('70','71','72','73','99'))
--)

---- must filter out cross join of race/gender - redundant?
--and ((racecode = '9' and sexcode = '9') or (racecode <> '9' and sexcode = '9') or (racecode = '9' and sexcode <> '9'))
---- not filtering out combined groups?
---- and racecode <> '6'

-- test only
--and (fullkey = '013619040022' or fullkey = '01361903XXXX')
and fullkey = '0463214C9407'
--and fullkey = '01361903XXXX'
--and [district number] = '3619'
--and racecode = '9' and sexcode = '9' 

--and gradecode = '99'


order by [District Number],[School Number], gradecode--, racecode, sexcode


