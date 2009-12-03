-- counts occurrences of columns names in all apparently relevant WI views
SELECT col.Name, Count(Col.Name)
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name NOT IN ('sysalternates', 'sysconstraints', 'syssegments', 'Dropoutcube', 'v_AP_KEYS_test',
'v_ACT_pre_template_keys', 'v_AP_TESTS_BkUp', 'v_COURSE_OFFERINGS_Grind', 'v_COURSEWORK_KEYS_20030811',
'v_COURSE_YEAR', 'v_COURSE_OFFERINGS', 'v_CurrentEducationCostPerMember', 'v_Athletic_Conf', 'v_Districts',
'v_Enrollment_new', 'v_Enrollment_old', 'v_RevenuesH', 'v_SqlSnippets', 'v_WSAS20031007', 'v_ErateRollupsWithSchooltype', 
'v_Expend', 'v_GradesEnrollFlat', 'v_GroupsSelSchoolsEconStat', 'v_Revenues', 'v_SMALL_SCHOOL_ENR', 
'v_SMALL_SCHOOL_ENR_STYPE_70_73', 'v_SMALL_SCHOOL_ENR_STYPE_74_77', 'v_SMALL_SCHOOL_ENR_STYPE_78_81',
'v_SMALL_SCHOOL_ENR_STYPE_82_85', 'v_SMALL_SCHOOL_ENR_STYPE_86_89', 'v_SMALL_SCHOOL_ENR_STYPE_90_93',
'v_SMALL_SCHOOL_ENR_STYPE_BASE', 'v_TeacherQualificationsAthConf', 'v_TeacherQualificationsOrg', 
'v_TeacherQualificationsScatterplotOrg', 'v_WKCEDEMOGRAPHICS_SIM', 'v_WSAS_old', 'vErate')
AND ob.Name NOT Like '%Key%'
GROUP BY col.Name
ORDER BY 
Count(col.Name) DESC

-- shows which columns go with which views
SELECT ob.Name, ob.ID, col.Name, col.colorder
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name NOT IN ('sysalternates', 'sysconstraints', 'syssegments', 'Dropoutcube', 'v_AP_KEYS_test',
'v_ACT_pre_template_keys', 'v_AP_TESTS_BkUp', 'v_COURSE_OFFERINGS_Grind', 'v_COURSEWORK_KEYS_20030811',
'v_COURSE_YEAR', 'v_COURSE_OFFERINGS', 'v_CurrentEducationCostPerMember', 'v_Athletic_Conf', 'v_Districts',
'v_Enrollment_new', 'v_Enrollment_old', 'v_RevenuesH', 'v_SqlSnippets', 'v_WSAS20031007', 'v_ErateRollupsWithSchooltype', 
'v_Expend', 'v_GradesEnrollFlat', 'v_GroupsSelSchoolsEconStat', 'v_Revenues', 'v_SMALL_SCHOOL_ENR', 
'v_SMALL_SCHOOL_ENR_STYPE_70_73', 'v_SMALL_SCHOOL_ENR_STYPE_74_77', 'v_SMALL_SCHOOL_ENR_STYPE_78_81',
'v_SMALL_SCHOOL_ENR_STYPE_82_85', 'v_SMALL_SCHOOL_ENR_STYPE_86_89', 'v_SMALL_SCHOOL_ENR_STYPE_90_93',
'v_SMALL_SCHOOL_ENR_STYPE_BASE', 'v_TeacherQualificationsAthConf', 'v_TeacherQualificationsOrg', 
'v_TeacherQualificationsScatterplotOrg', 'v_WKCEDEMOGRAPHICS_SIM', 'v_WSAS_old', 'vErate')
AND ob.Name NOT Like '%Key%'
ORDER BY 
--ob.Name, col.colorder 
col.Name

-- gives names of all apparently relevant WI views
SELECT Name FROM sysObjects ob
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name NOT IN ('sysalternates', 'sysconstraints', 'syssegments', 'Dropoutcube', 'v_AP_KEYS_test',
'v_ACT_pre_template_keys', 'v_AP_TESTS_BkUp', 'v_COURSE_OFFERINGS_Grind', 'v_COURSEWORK_KEYS_20030811',
'v_COURSE_YEAR', 'v_COURSE_OFFERINGS', 'v_CurrentEducationCostPerMember', 'v_Athletic_Conf', 'v_Districts',
'v_Enrollment_new', 'v_Enrollment_old', 'v_RevenuesH', 'v_SqlSnippets', 'v_WSAS20031007', 'v_ErateRollupsWithSchooltype', 
'v_Expend', 'v_GradesEnrollFlat', 'v_GroupsSelSchoolsEconStat', 'v_Revenues', 'v_SMALL_SCHOOL_ENR', 
'v_SMALL_SCHOOL_ENR_STYPE_70_73', 'v_SMALL_SCHOOL_ENR_STYPE_74_77', 'v_SMALL_SCHOOL_ENR_STYPE_78_81',
'v_SMALL_SCHOOL_ENR_STYPE_82_85', 'v_SMALL_SCHOOL_ENR_STYPE_86_89', 'v_SMALL_SCHOOL_ENR_STYPE_90_93',
'v_SMALL_SCHOOL_ENR_STYPE_BASE', 'v_TeacherQualificationsAthConf', 'v_TeacherQualificationsOrg', 
'v_TeacherQualificationsScatterplotOrg', 'v_WKCEDEMOGRAPHICS_SIM', 'v_WSAS_old', 'vErate')
AND ob.Name NOT Like '%Key%'
ORDER BY ob.Name
