Select 

-- do a lot of this in the view?
'year' = v_WSASWithCounts.[Year], 'tblAgency_key' = tblAgency.[AgencyKEY], v_WSASWithCounts.[CESA], 'district_number' = [District Number], 'school_number' = [School Number], 
'tblAgency_type' = [Agency Type], 
'school_type' = (case right(v_WSASWithCounts.fullkey,1) when 'X' then 'Summary' else (case tblAgency.schooltype when '6' then 'Elementary School Type' when '5' then 'Middle/Junior High School Type' when '3' then 'High School Type' when '7' then 'Comb. Elem/Second School Type' else '0' end) end), 'charter' = (case rtrim(tblAgency.schoolcat) when 'CHR' then 'Y' else 'N' end), 'district_name' = [District Name], 'school_name' = [School Name], 'grade_label' = [Grade], 'race_ethnicity' = (case when Groupnum IN ('14','15','16','17','18','19','20') then rtrim([GroupName]) else 'All Races' end), 'gender' = (case when Groupnum IN ('11','12', '13') then rtrim([GroupName]) else 'Both Genders' end), 'disability_status' = (case when Groupnum IN ('25','26') then rtrim([GroupName]) else 'Students with and without Disabilities' end), 'economic_status' = (case when Groupnum IN ('27','28') then rtrim([GroupName]) else 'Economically Disadvantaged and Not Disadvantaged' end), 'english_proficiency_status' = (case when Groupnum IN ('21','22') then rtrim([GroupName]) else 'Limited English Proficient and English Proficient' end), 'migrant_status' = (case when Groupnum IN ('23','24') then rtrim([GroupName]) else 'Migrant and Nonmigrant' end), 

'total_enrollment' = [EnrollmentDenominator], SubjectLabel as 'Subject', 'N NO WSAS-Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number No WSAS Total]), 
'N NO WSAS-Excused by Parent ' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Excused-By-Parent]), 
'N NO WSAS-Reasons Unknown' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Eligible-But-Not-Tested]), 

--'N Pre-Req Skill -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number TotalWAADisabil]), 
'N Pre-Req Skill -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Pre-Req Skill]), 

'N Pre-Req Skill Minimal' = [Number Pre-Req Skill Level 1], 'N Pre-Req Skill Basic' = [Number Pre-Req Skill Level 2], 
'N Pre-Req Skill Proficient' = [Number Pre-Req Skill Level 3], 'N Pre-Req Skill Advanced' = [Number Pre-Req Skill Level 4], 

--'N Pre-Req English -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number TotalWAALep]), 
'N Pre-Req English -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Pre-Req Eng]), 

'N Pre-Req English Minimal' = [Number Pre-Req Eng Minimal], 'N Pre-Req English Basic' = [Number Pre-Req Eng Basic], 
'N Pre-Req English Proficient' = [Number Pre-Req Eng Proficient], 'N Pre-Req English Advanced' = [Number Pre-Req Eng Advanced], 

--'N Min. Perf.' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Number Minimal]), 'N Basic' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Number Basic]), 
--'N Proficient' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Number Proficient]), 'N Advanced' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Number Advanced]), 
'N Min. Perf.' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Minimal]), 'N Basic' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Basic]), 
'N Proficient' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Proficient]), 'N Advanced' = dbo.ConvertFloatToCharAndTrapNumericCodes([Number Advanced]), 

'% NO WSAS-Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([No WSAS Total]), '% NO WSAS-Excused by Parent' = dbo.ConvertFloatToCharAndTrapNumericCodes([Excused-By-Parent]), 
'% NO WSAS-Reasons Unknown' = dbo.ConvertFloatToCharAndTrapNumericCodes([Eligible-But-Not-Tested]), 

--'% Pre-Req Skill -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([PctTotalWAADisabil]), 
'% Pre-Req Skill -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Pre-Req Skill]), 

'% Pre-Req Skill Minimal' = [Percent Pre-Req Skill Level 1], '% Pre-Req Skill Basic' = [Percent Pre-Req Skill Level 2], 
'% Pre-Req Skill Proficient' = [Percent Pre-Req Skill Level 3], '% Pre-Req Skill Advanced' = [Percent Pre-Req Skill Level 4], 

--'% Pre-Req English -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([PctTotalWAALep]), 
'% Pre-Req English -Total' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Pre-Req Eng]), 


'% Pre-Req English Minimal' = [Percent Pre-Req Eng Minimal], '% Pre-Req English Basic' = [Percent Pre-Req Eng Basic], 
'% Pre-Req English Proficient' = [Percent Pre-Req Eng Proficient], '% Pre-Req English Advanced' = [Percent Pre-Req Eng Advanced], 

--'% Min. Perf.' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Percent Minimal]), '% Basic' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Percent Basic]), 
--'% Proficient' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Percent Proficient]), '% Advanced' = dbo.ConvertFloatToCharAndTrapNumericCodesDoubledCodes([Percent Advanced]) 
'% Min. Perf.' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Minimal]), '% Basic' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Basic]), 
'% Proficient' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Proficient]), '% Advanced' = dbo.ConvertFloatToCharAndTrapNumericCodes([Percent Advanced]) 



from v_WSASWithCounts left outer join tblAgency on v_WSASWithCounts.year = tblAgency.year and v_WSASWithCounts.fullkey = tblAgency.fullkey where v_WSASWithCounts.year = '2006' and v_WSASWithCounts.fullkey = '013619040022' and groupnum in ('14','15','16','17','18','19','20') and grade = '10' and subjectid = '1re' order by groupnum;