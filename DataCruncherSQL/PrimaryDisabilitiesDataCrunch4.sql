select 
year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = [SchoolTypeLabel], 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
'grade_label' = [SchoolTypeLabel], 
[RaceCode], [RaceLabel], [SexCode], [SexLabel], 
'total_enrollment_prek-12' = [Enrollment PK-12*],
'number_cognitively_disabled' = isnull(CDCount,'n/a'),
'percent_cognitively_disabled' = isnull(CDPercent,'n/a'),
'number_emotional_behavioral_disability' = isnull(EBDCount,'n/a'),
'percent_emotional_behavioral_disability' = isnull(EBDPercent,'n/a'),
'number_specific_learning_disabilities' = isnull(LDCount,'n/a'),
'percent_specific_learning_disabilities' = isnull(LDPercent,'n/a'),
'number_speech_or_language_impaired' = isnull(SLCount,'n/a'),
'percent_speech_or_language_impaired' = isnull(SLPercent,'n/a'),
'number_autism' = isnull(ACount,'n/a'),
'percent_autism' = isnull(APercent,'n/a'),
'number_deaf_blind' = isnull(DBCount,'n/a'),
'percent_deaf_blind' = isnull(DBPercent,'n/a'),
'number_hearing_impaired' = isnull(HCount,'n/a'),
'percent_hearing_impaired' = isnull(HPercent,'n/a'),
'number_other_health_impaired' = isnull(OHICount,'n/a'),
'percent_other_health_impaired' = isnull(OHIPercent,'n/a'),
'number_orthopedically_impaired' = isnull(OICount,'n/a'),
'percent_orthopedically_impaired' = isnull(OIPercent,'n/a'),
'number_significant_developmental_delay' = isnull(SDDCount,'n/a'),
'percent_significant_developmental_delay' = isnull(SDDPercent,'n/a'),
'number_traumatic_brain_injury' = isnull(TBICount,'n/a'),
'percent_traumatic_brain_injury' = isnull(TBIPercent,'n/a'),
'number_visually_impaired' = isnull(VICount,'n/a'),
'percent_visually_impaired' = isnull(VIPercent,'n/a'),
'number_combined' = isnull(SWDCount,'n/a'),
'percent_combined' = isnull(SWDPercent,'n/a'),
'number_without_disability' = isnull(StudentsWODisCount,'n/a'),
'percent_without_disability' = isnull(StudentsWODisPercent,'n/a')

from v_Disabilities2 
--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where fullkey <> 'XXXXXXXXXXXX' and CESA = ? and year = ? 
where year = '2003' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01'
-- what_are_the_primary_disabilities_of_students_in_need_of_special_education_services_2003_cesa01.csv

and (racecode = '9' and sexcode = '9')

and (right(left(fullkey,8),2) <> '14' 
or (
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_Disabilities2.year = agency.year and v_Disabilities2.agencykey = agency.agencykey) is not null 
))

order by [District Number],[School Number], [SchoolTypeLabel], [RaceCode], [SexCode]


