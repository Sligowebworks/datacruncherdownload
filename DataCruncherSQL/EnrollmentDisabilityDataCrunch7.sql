select 

-- EnrollmentDisabilityDataCrunch7.sql

year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = [SchoolTypeLabel], 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = rtrim(GradeLabel), 
--'grade_label' = [SchoolTypeLabel], 
'grade_label' = 'PreK-12', 


'total_enrollment_prek-12' = [Enrollment],
--> changes with each
'number_with_disabilities' = [Disabled], 
'percent_with_disabilities' = [% With Disabilities], 
'number_without_disabilities' = [Non-Disabled], 
'percent_without_disabilities' = [% Without Disabilities]

--> changes with each
from v_EnrollFlatWWoDis 
where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = '2004' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 

and (right(left(fullkey,8),2) <> '14' 
or (
--> changes with each
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_EnrollFlatWWoDis.year = agency.year and v_EnrollFlatWWoDis.agencykey = agency.agencykey) is not null 
))

and schooltype <> '9'

order by [District Number],[School Number]--, disability
--, gradecode--, racecode, sexcode


