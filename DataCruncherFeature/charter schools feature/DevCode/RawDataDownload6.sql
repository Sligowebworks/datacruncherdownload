-- must be sure that agency keys in download files are from tblAgency, not WSAS

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

SubjectLabel as 'Subject', 
'Reading N NO WSAS-Total' = [Number No WSAS Total], 
'Reading N NO WSAS-Excused by Parent ' = [Number Excused-By-Parent], 
'Reading N NO WSAS-Reasons Unknown' = [Number Eligible-But-Not-Tested], 
'Reading N Pre-Req Skill -Total' = [Number TotalWAADisabil], 
'Reading N Pre-Req Skill Minimal' = [Number Pre-Req Skill Level 1], 
'Reading N Pre-Req Skill Basic' = [Number Pre-Req Skill Level 2], 
'Reading N Pre-Req Skill Proficient' = [Number Pre-Req Skill Level 3], 
'Reading N Pre-Req Skill Advanced' = [Number Pre-Req Skill Level 4], 
'Reading N Pre-Req English -Total' = [Number TotalWAALep], 
'Reading N Pre-Req English Minimal' = [Number Pre-Req Eng Minimal], 
'Reading N Pre-Req English Basic' = [Number Pre-Req Eng Basic], 
'Reading N Pre-Req English Proficient' = [Number Pre-Req Eng Proficient], 
'Reading N Pre-Req English Advanced' = [Number Pre-Req Eng Advanced], 
'Reading N Min. Perf.' = [Number Minimal], 
'Reading N Basic' = [Number Basic], 
'Reading N Proficient' = [Number Proficient], 
'Reading N Advanced' = [Number Advanced], 
'Reading % NO WSAS-Total' = [No WSAS Total], 
'Reading % NO WSAS-Excused by Parent' = [Excused-By-Parent], 
'Reading % NO WSAS-Reasons Unknown' = [Eligible-But-Not-Tested], 
'Reading % Pre-Req Skill -Total' = [PctTotalWAADisabil], 
'Reading % Pre-Req Skill Minimal' = [Percent Pre-Req Skill Level 1], 
'Reading % Pre-Req Skill Basic' = [Percent Pre-Req Skill Level 2], 
'Reading % Pre-Req Skill Proficient' = [Percent Pre-Req Skill Level 3], 
'Reading % Pre-Req Skill Advanced' = [Percent Pre-Req Skill Level 4], 
'Reading % Pre-Req English -Total' = [PctTotalWAALep], 
'Reading % Pre-Req English Minimal' = [Percent Pre-Req Eng Minimal], 
'Reading % Pre-Req English Basic' = [Percent Pre-Req Eng Basic], 
'Reading % Pre-Req English Proficient' = [Percent Pre-Req Eng Proficient], 
'Reading % Pre-Req English Advanced' = [Percent Pre-Req Eng Advanced], 
'Reading % Min. Perf.' = [Percent Minimal], 
'Reading % Basic' = [Percent Basic], 
'Reading % Proficient' = [Percent Proficient], 
'Reading % Advanced' = [Percent Advanced], 



/*
'total_enrollment'
'Reading N NO WSAS-Total'
'Reading N NO WSAS-Excused by Parent '
'Reading N NO WSAS-Reasons Unknown'
'Reading N Pre-Req Skill -Total'
'Reading N Pre-Req Skill Minimal'
'Reading N Pre-Req Skill Basic'
'Reading N Pre-Req Skill Proficient'
'Reading N Pre-Req Skill Advanced'
'Reading N Pre-Req English -Total'
'Reading N Pre-Req English Minimal'
'Reading N Pre-Req English Basic'
'Reading N Pre-Req English Proficient'
'Reading N Pre-Req English Advanced'
'Reading N Min. Perf.'
'Reading N Basic'
'Reading N Proficient'
'Reading N Advanced'
'Reading % NO WSAS-Total'
'Reading % NO WSAS-Excused by Parent'
'Reading % NO WSAS-Reasons Unknown'
'Reading % Pre-Req Skill -Total'
'Reading % Pre-Req Skill Minimal'
'Reading % Pre-Req Skill Basic'
'Reading % Pre-Req Skill Proficient'
'Reading % Pre-Req Skill Advanced'
'Reading % Pre-Req English -Total'
'Reading % Pre-Req English Minimal'
'Reading % Pre-Req English Basic'
'Reading % Pre-Req English Proficient'
'Reading % Pre-Req English Advanced'
'Reading % Min. Perf.'
'Reading % Basic'
'Reading % Proficient'
'Reading % Advanced'
*/

[Enrolled], 'No WSAS' = [No WSAS Total], 'Min Perf' = MinPerfWSAS, 'Basic' = BasicWSAS, 'Proficient' = ProficientWSAS, 'Advanced' = AdvancedWSAS 

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

