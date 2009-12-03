Select 

'year' = v_WSASWithCounts.[Year], 
'tblAgency_key' = v_WSASWithCounts.[AgencyKEY], 
v_WSASWithCounts.[CESA], 
'district_number' = [District Number], 
'school_number' = [School Number], 
'tblAgency_type' = [Agency Type], 

-- must create join to tblAgency 
'school_type' = (case right(v_WSASWithCounts.fullkey,1) when 'X' then 'Summary' else 
	(case tblAgency.schooltype
	when '6' then 'Elementary School Type'
	when '5' then 'Middle/Junior High School Type'
	when '3' then 'High School Type'
	when '7' then 'Comb. Elem/Second School Type'
	else '0' end) 
end), 

'charter' = (case rtrim(tblAgency.schoolcat) when 'CHR' then 'Y' else 'N' end), 

'district_name' = [District Name], 
'school_name' = [School Name], 
'grade_label' = [Grade], 
'race_ethnicity' = (case when Groupnum IN ('14','15','16','17','18','19','20') then rtrim([GroupName]) else 'All Races' end), 
'gender' = (case when Groupnum IN ('11','12', '13') then rtrim([GroupName]) else 'Both Genders' end), 
'disability_status' = (case when Groupnum IN ('25','26') then rtrim([GroupName]) else 'Students with and without Disabilities' end), 
'economic_status' = (case when Groupnum IN ('27','28') then rtrim([GroupName]) else 'Economically Disadvantaged and Not Disadvantaged' end), 
'english_proficiency_status' = (case when Groupnum IN ('21','22') then rtrim([GroupName]) else 'Limited English Proficient and English Proficient' end), 
'migrant_status' = (case when Groupnum IN ('23','24') then rtrim([GroupName]) else 'Migrant and Nonmigrant' end), 

'total_enrollment' = [EnrollmentDenominator], 

--[GroupNum], [GroupName], [SubjectID], [SubjectLabel], [Lowest Grade in School], [Test Date], [Level], [Total Enrollment-PI 1290 definition], [Enrolled], [Included], [Excluded], 

--[Excused-By-Parent], [No WSAS Total], [No WSAS], [PctExcluded], [Eligible-But-Not-Tested], [PctTotalWAADisabil], [Percent Pre-Req Skill], [Percent Pre-Req Skill Level 1], [Percent Pre-Req Skill Level 2], [Percent Pre-Req Skill Level 3], [Percent Pre-Req Skill Level 4], [PctTotalWAALep], [Percent Pre-Req Eng], [Percent Pre-Req Eng Minimal], [Percent Pre-Req Eng Basic], [Percent Pre-Req Eng Proficient], [Percent Pre-Req Eng Advanced], [Percent Minimal], [MinPerfWSAS], [Percent Basic], [BasicWSAS], [Percent Proficient], [ProficientWSAS], [Percent Advanced], [AdvancedWSAS], [PCTAdvPlusPCTPrf], [AdvancedPlusProficientTotalWSAS], [BasicPlusMinPerfPlusPre-ReqSkillsEngPlusNoWSASTotal], [BasicPlusMinPerfPlusNoWSASTotalWSAS] 

SubjectLabel as 'Subject', [Enrolled], 'No WSAS' = [No WSAS Total], 'Min Perf' = MinPerfWSAS, 'Basic' = BasicWSAS, 'Proficient' = ProficientWSAS, 'Advanced' = AdvancedWSAS 
from 
--v_WSAS 
v_WSASWithCounts

-- splicing in join to tblAgency - do in view instead?
left outer join tblAgency on v_WSASWithCounts.year = tblAgency.year and v_WSASWithCounts.fullkey = tblAgency.fullkey

where 

--year = '2006' 
v_WSASWithCounts.year = '2006' 

--and Fullkey = '01361903XXXX' 
--and v_WSASWithCounts.Fullkey = '01361903XXXX' 
and v_WSASWithCounts.Fullkey = '013619040022' 
--and Groupnum = '7' 
and Groupnum IN ('14','15','16','17','18','19','20')

and Grade = '10' 

--and SubjectID in ('1RE','2LA','3MA','4SC','5SS') 
and SubjectID = '1RE' 

order by groupnum, SubjectID;

