select 

-- this is EnrollmentAllGenderRaceDataCrunch10.sql

year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = rtrim([SchoolTypeLabel]), 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = rtrim(SchoolTypeLabel), 
'total_enrollment_K-12' = rtrim([Enrollment]),  
'number_female' = [Female], 
'percent_female' = [% Female], 
'number_male' = [Male], 
'percent_male' = [% Male], 
'number_am_ind' = [Am. Ind.], 
'percent_am_ind' = [% Am. Ind.], 
'number_asian' = [Asian], 
'percent_asian' = [% Asian], 
'number_black' = [Black], 
'percent_black' = [% Black], 
'number_hispanic' = [Hisp.], 
'percent_hispanic' = [% Hisp.], 
'number_white' = [White], 
'percent_white' = [% White]

FROM [v_EnrollFlatWWoDis]
where year = ? and CESA = ? and fullkey <> 'XXXXXXXXXXXX' 
-- below is test only
--where year = '2006' and fullkey <> 'XXXXXXXXXXXX' --and CESA = '05' 
--and left(right(fullkey,10),4) = '0714'

and (right(left(fullkey,8),2) <> '14' 
or (
--> changes with each
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_EnrollFlatWWoDis.year = agency.year and v_EnrollFlatWWoDis.agencykey = agency.agencykey) is not null 
))

order by [District Number],[School Number], schooltype --, gradecode--, racecode, sexcode

