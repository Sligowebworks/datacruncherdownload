select 

--gradecode, racecode, sexcode, 
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
'race_ethnicity' = 'All Races', 'gender' = 'Both Genders',


--'total_enrollment_K-12' = rtrim([Total Enrollment (K-12)]),  

--'number_of_retentions' = rtrim([Number of Retentions]), 'retention_rate' = rtrim([Retention Rate])

--> changes with each

'total_enrollment_prek-12' = rtrim([Enrollment]),  
'pre-k_number' = [Pre-K.], 
'pre-k_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Pre-K.] as char) end), 
'kinder_number' = [Kinder.], 
'kinder_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Kinder.] as char) end), 
'grade_1_number' = [Grade 1], 
'grade_1_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 1] as char) end), 
'grade_2_number' = [Grade 2], 
'grade_2_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 2] as char) end), 
'grade_3_number' = [Grade 3], 
'grade_3_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 3] as char) end), 
'grade_4_number' = [Grade 4], 
'grade_4_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 4] as char) end), 
'grade_5_number' = [Grade 5], 
'grade_5_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 5] as char) end), 
'grade_6_number' = [Grade 6], 
'grade_6_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 6] as char) end), 
'grade_7_number' = [Grade 7], 
'grade_7_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 7] as char) end), 
'grade_8_number' = [Grade 8], 
'grade_8_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 8] as char) end), 
'grade_9_number' = [Grade 9], 
'grade_9_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 9] as char) end), 
'grade_10_number' = [Grade 10], 
'grade_10_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 10] as char) end), 
'grade_11_number' = [Grade 11], 
'grade_11_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 11] as char) end), 
'grade_12_number' = [Grade 12], 
'grade_12_percent' = (case rtrim([Enrollment]) when 0 then '--' else cast([% Grade 12] as char) end)

--> changes with each
from v_EnrollFlatRaceSexGradesExSS
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2004' and CESA = '01' and fullkey <> 'XXXXXXXXXXXX' 

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
(select distinct PartSchIndic from agency where  v_EnrollFlatRaceSexGradesExSS.year = agency.year and v_EnrollFlatRaceSexGradesExSS.agencykey = agency.agencykey) is not null 
))


--and (
---- school level
----(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','99')
--(right(fullkey,1) <> 'X' and (racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','99')
--or (racecode <> '9' and sexcode = '9' and gradecode = '99') or (racecode = '9' and sexcode <> '9' and gradecode = '99'))
--and ((gradecode >= (select distinct lowgrade from agency where  v_teacherqualifications.year = agency.year and v_teacherqualifications.agencykey = agency.agencykey) 
--and gradecode <= (select distinct highgrade from agency where v_teacherqualifications.year = agency.year and v_teacherqualifications.agencykey = agency.agencykey))
--or gradecode = '99'))
--or 
---- district level - grade breakout and schooltypes for all races and all genders 
----(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('16','20','24','28','32','36','40','44','48','52','56','60','64','78','79','80','81','99')) or 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode = '9' and gradecode in ('44','48','52','56','60','64','78','79','80','81','99')) or 
---- district level - schooltypes for races 
--(right(fullkey,1) = 'X' and racecode <> '9' and sexcode = '9' and gradecode in ('78','79','80','81','99')) or 
---- district level - schooltypes for gender 
--(right(fullkey,1) = 'X' and racecode = '9' and sexcode <> '9' and gradecode in ('78','79','80','81','99'))
--)

---- must filter out cross join of race/gender - redundant?
--and ((racecode = '9' and sexcode = '9') or (racecode <> '9' and sexcode = '9') or (racecode = '9' and sexcode <> '9'))
---- not filtering out combined groups?
---- and racecode <> '6'

-- test only
--and (fullkey = '013619040022' or fullkey = '01361903XXXX')
--and fullkey = '01361903XXXX'
--and fullkey = '012420049200'
--and [district number] = '3619'
--and racecode = '9' and sexcode = '9' 

and gradecode = '99'


order by [District Number],[School Number], gradecode--, racecode, sexcode


