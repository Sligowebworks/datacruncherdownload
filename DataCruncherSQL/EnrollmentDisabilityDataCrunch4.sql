-- suppression!!

select 

year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = [SchoolTypeLabel], 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = rtrim(GradeLabel), 
'grade_label' = [SchoolTypeLabel], 

--> changes with each

-- per jean email of 2006-01-09
'number_with_disabilities' = (case 
	when [Non-Disabled] <= 0 then '*'	
	when enrollment > 0 and enrollment < 6 then '*'	
	when Enrollment is null then '*' 
	when [Disabled] < 0 then '*' 
	when isnull(Enrollment,0) < 0 then '*' 
	else cast([Disabled] as char) 
end), 

'percent_with_disabilities' = (case 
	when [Non-Disabled] <= 0 then '*'	
	when enrollment > 0 and enrollment < 6 then '*'	
	when Enrollment is null then '*' 
	when [Disabled] < 0 then '*' 
	when isnull(Enrollment,0) < 0 then '*' 
	when Enrollment = 0 then '--' 
	else cast((case isnull(Enrollment,0) 
		when 0 then 0 
	else ((cast([Disabled] as decimal)/cast(Enrollment as decimal)) * 100) 
	end) 
as char) end), 

'number_without_disabilities' = (case 
	when [Non-Disabled] <= 0 then '*'	
	when enrollment > 0 and enrollment < 6 then '*'	
	when Enrollment is null then '*' 
	when [Non-Disabled] < 0 then '*' 
	when isnull(Enrollment,0) < 0 then '*' 
	else cast([Non-Disabled] as char) 
end), 

'percent_without_disabilities' = (case 
	when [Non-Disabled] <= 0 then '*'	
	when enrollment > 0 and enrollment < 6 then '*'	
	when Enrollment is null then '*' 
	when [Non-Disabled] < 0 then '*' 
	when isnull(Enrollment,0) < 0 then '*' 
	when Enrollment = 0 then '--' 
	else cast((case isnull(Enrollment,0) 
		when 0 then 0 
	else ((cast([Non-Disabled] as decimal)/cast(Enrollment as decimal)) * 100) 
	end) as char) 
end)


--> changes with each
from v_EnrollFlatWWoDis 
--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
where year = '2004' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 

and (right(left(fullkey,8),2) <> '14' 
or (
--> changes with each
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_EnrollFlatWWoDis.year = agency.year and v_EnrollFlatWWoDis.agencykey = agency.agencykey) is not null 
))

order by [District Number],[School Number]--, disability
--, gradecode--, racecode, sexcode


