select 

year, 'agency_key' = AgencyKey, CESA, 'district_number' = [District Number],'school_number' = [School Number], 'agency_type' = left(right(fullkey,6),2), 
'school_type' = [SchoolTypeLabel], 
charter, 'district_name' = ltrim([District Name]), 'school_name' = ltrim([School Name]), 
--'grade_label' = rtrim(GradeLabel), 
'grade_label' = [SchoolTypeLabel], 

[RaceCode], [RaceLabel], [SexCode], [SexLabel], 

'total_enrollment_prek-12' = [Enrollment PK-12*],
--> changes with each

[DisStudentCount], 
[DisStudentPercent], 
/*
[CDCount], 
[CDPercent], 
[EBDCount], 
[EBDPercent], 
[LDCount], 
[LDPercent], 
[SLCount], 
[SLPercent], 
[ACount], 
[APercent], 
[DBCount], 
[DBPercent], 
[HCount], 
[HPercent], 
[OHICount], 
[OHIPercent], 
[OICount], 
[OIPercent], 
[SDDCount], 
[SDDPercent], 
[TBICount], 
[TBIPercent], 
[VICount], 
[VIPercent], 
*/

'number_cognitively_disabled' = isnull(CDCount,'n/a'),
'percent_cognitively_disabled' = isnull(CDPercent,'n/a'),
'percent_emotional_behavioral_disability' = isnull(EBDPercent,'n/a'),
'number_emotional_behavioral_disability' = isnull(EBDCount,'n/a'),
'number_specific_learning_disabilities' = isnull(LDCount,'n/a'),
'percent_specific_learning_disabilities' = isnull(LDPercent,'n/a'),
'percent_speech_or_language_impaired' = isnull(SLPercent,'n/a'),
'number_speech_or_language_impaired' = isnull(SLCount,'n/a'),
'number_autism' = isnull(ACount,'n/a'),
'percent_autism' = isnull(APercent,'n/a'),
'number_deaf_blind' = isnull(DBCount,'n/a'),
'percent_deaf_blind' = isnull(DBPercent,'n/a'),
'number_hearing_impaired' = isnull(HCount,'n/a'),
'percent_hearing_impaired' = isnull(HPercent,'n/a'),
'number_other_health_impaired' = isnull(OHICount,'n/a'),
'percent_other_health_impaired' = isnull(OHIPercent,'n/a'),
'percent_orthopedically_impaired' = isnull(OIPercent,'n/a'),
'number_orthopedically_impaired' = isnull(OICount,'n/a'),
'number_significant_developmental_delay' = isnull(SDDCount,'n/a'),
'percent_significant_developmental_delay' = isnull(SDDPercent,'n/a'),
'number_traumatic_brain_injury' = isnull(TBICount,'n/a'),
'percent_traumatic_brain_injury' = isnull(TBIPercent,'n/a'),
'percent_visually_impaired' = isnull(VIPercent,'n/a'),
'number_visually_impaired' = isnull(VICount,'n/a'),

[SWDCount], 
[SWDPercent], 
[StudentsWODisCount], 
[StudentsWODisPercent] 

--'number_with_disabilities' = [Disabled], 
--'percent_with_disabilities' = [% With Disabilities], 
--'number_without_disabilities' = [Non-Disabled], 
--'percent_without_disabilities' = [% Without Disabilities]

--> changes with each
--from v_EnrollFlatWWoDis 
from v_Disabilities2 
-- doing state-level rows on this one?
--where year = ? and fullkey <> 'XXXXXXXXXXXX' and CESA = ?
--where year = ? and CESA = ?
--where year = '2003' and fullkey <> 'XXXXXXXXXXXX' and CESA = '01' 
where year = '2003' and CESA = '01' 

and (racecode = '9' and sexcode = '9')

and (right(left(fullkey,8),2) <> '14' 
or (
--> changes with each
right(left(fullkey,8),6) = '361914' and 
(select distinct PartSchIndic from agency where  v_Disabilities2.year = agency.year and v_Disabilities2.agencykey = agency.agencykey) is not null 
))

order by [District Number],[School Number]--, disability
--, gradecode--, racecode, sexcode


