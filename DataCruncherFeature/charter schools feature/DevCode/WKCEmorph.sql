USE Wisconsin
GO

--~%~%~%~% Morph table, WKCE, for charter schools download
-- NOTE: "WKCE" is an alias  --

IF EXISTS (
		SELECT name FROM sysobjects WHERE name = N'WKCE_DownloadMorph'
)	DROP TABLE WKCE_DownloadMorph
GO



SELECT
	WKCE.[Year]
,	[Test Date]  = 'N/A'
,	[Org Level] =	CASE
		WHEN right(WKCE.fullkey,1) <> 'X' THEN 3
		WHEN right(WKCE.fullkey,1) = 'X' AND left(WKCE.fullkey,1) <> 'X' THEN 2
		WHEN WKCE.fullkey = 'XXXXXXXXXXXX' THEN 1
	END
,	WKCE.[Grade]
,	tA.[District Name] 
,	tA.[District Number] 
,	tA.[School Name]
,	tA.[School Number]
,	[Agency Type] = tA.[AgencyType]
,	[Agency Key] = tA.[AgencyKey] 
,	tA.[CESA]
,	[Lowest Grade in School] = ta.[LowGrade]
,	[Student Group] = WKCE.[GroupNum]
,	[Total Enrollment-PI 1290 definition] = 'N/A'
,	[Total Enrollment-WSAS] = WKCE.[Reading Enrolled]
,	[Enrollment included in %s and other WSAS results] = WKCE.[Reading Included]
-- ~%~%~%~ --
,	[Reading % NO WSAS-Total] = WKCE.[Reading PctNotTested]
,	[Reading % NO WSAS-Excused by Parent] = WKCE.[Reading Excused]
,	[Reading % NO WSAS-Reasons Unknown] = 'N/A'
,	[Reading % Pre-Req Skill -Total] = 'N/A'
,	[Reading % Pre-Req Skill 1] = 'N/A'
,	[Reading % Pre-Req Skill 2] = 'N/A'
,	[Reading % Pre-Req Skill 3] = 'N/A'
,	[Reading % Pre-Req Skill 4] = 'N/A'
,	[Reading % Pre-Req English -Total] = 'N/A'
,	[Reading % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
,	[Reading % Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
,	[Reading % Pre-Req English - Proficient] = 'N/A'
,	[Reading % Pre-Req English - Advanced] = 'N/A'
,	[Reading % Min. Perf.] = WKCE.[Reading PctMin]
,	[Reading % Basic] = WKCE.[Reading PctBas]
,	[Reading % Proficient] = WKCE.[Reading PctPrf]
,	[Reading % Advanced] = WKCE.[Reading PctAdv]
-- ~%~%~%~ --
,	[Language Arts  % NO WSAS-Total] = WKCE.[Language Arts PctNotTested]
,	[Language Arts % NO WSAS-Excused by Parent] = WKCE.[Language Arts Excused]
,	[Language Arts % NO WSAS-Reasons Unknown] = 'N/A'
,	[Language Arts % Pre-Req Skill -Total] = 'N/A'
,	[Language Arts % Pre-Req Skill 1] = 'N/A'
,	[Language Arts % Pre-Req Skill 2] = 'N/A'
,	[Language Arts % Pre-Req Skill 3] = 'N/A'
,	[Language Arts % Pre-Req Skill 4] = 'N/A'
,	[Language Arts % Pre-Req English -Total] = 'N/A'
,	[Language Arts % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
,	[Language Arts % Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
,	[Language Arts % Pre-Req English - Proficient] = 'N/A'
,	[Language Arts % Pre-Req English - Advanced] = 'N/A'
,	[Language Arts % Min. Perf.] = WKCE.[Language Arts PctMin]
,	[Language Arts % Basic] = WKCE.[Language Arts PctBas]
,	[Language Arts % Proficient] = WKCE.[Language Arts PctPrf]
,	[Language Arts % Advanced] = WKCE.[Language Arts PctAdv]
-- ~%~%~%~ --
,	[Math  % NO WSAS-Total] = WKCE.[Math PctNotTested]
,	[Math % NO WSAS-Excused by Parent] = WKCE.[Math Excused]
,	[Math % NO WSAS-Reasons Unknown] = 'N/A'
,	[Math % Pre-Req Skill -Total] = 'N/A'
,	[Math % Pre-Req Skill 1] = 'N/A'
,	[Math % Pre-Req Skill 2] = 'N/A'
,	[Math % Pre-Req Skill 3] = 'N/A'
,	[Math % Pre-Req Skill 4] = 'N/A'
,	[Math % Pre-Req English -Total] = 'N/A'
,	[Math % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
,	[Math % Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
,	[Math % Pre-Req English - Proficient] = 'N/A'
,	[Math % Pre-Req English - Advanced] = 'N/A'
,	[Math % Min. Perf.] = WKCE.[Math PctMin]
,	[Math % Basic] = WKCE.[Math PctBas]
,	[Math % Proficient] = WKCE.[Math PctPrf]
,	[Math % Advanced] = WKCE.[Math PctAdv]
-- ~%~%~%~ --
,	[Science  % NO WSAS-Total] = WKCE.[Science PctNotTested]
,	[Science % NO WSAS-Excused by Parent] = WKCE.[Science Excused]
,	[Science % NO WSAS-Reasons Unknown] = 'N/A'
,	[Science % Pre-Req Skill -Total] = 'N/A'
,	[Science % Pre-Req Skill 1] = 'N/A'
,	[Science % Pre-Req Skill 2] = 'N/A'
,	[Science % Pre-Req Skill 3] = 'N/A'
,	[Science % Pre-Req Skill 4] = 'N/A'
,	[Science % Pre-Req English -Total] = 'N/A'
,	[Science % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
,	[Science % Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
,	[Science % Pre-Req English - Proficient] = 'N/A'
,	[Science % Pre-Req English - Advanced] = 'N/A'
,	[Science % Min. Perf.] = WKCE.[Science PctMin]
,	[Science % Basic] = WKCE.[Science PctBas]
,	[Science % Proficient] = WKCE.[Science PctPrf]
,	[Science % Advanced] = WKCE.[Science PctAdv]
-- ~%~%~%~ --
,	[Social Studies  % NO WSAS-Total] = WKCE.[Social Studies PctNotTested]
,	[Social Studies % NO WSAS-Excused by Parent] = WKCE.[Social Studies Excused]
,	[Social Studies % NO WSAS-Reasons Unknown] = 'N/A'
,	[Social Studies % Pre-Req Skill -Total] = 'N/A'
,	[Social Studies % Pre-Req Skill 1] = 'N/A'
,	[Social Studies % Pre-Req Skill 2] = 'N/A'
,	[Social Studies % Pre-Req Skill 3] = 'N/A'
,	[Social Studies % Pre-Req Skill 4] = 'N/A'
,	[Social Studies % Pre-Req English -Total] = 'N/A'
,	[Social Studies % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
,	[Social Studies % Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
,	[Social Studies % Pre-Req English - Proficient] = 'N/A'
,	[Social Studies % Pre-Req English - Advanced] = 'N/A'
,	[Social Studies % Min. Perf.] = WKCE.[Social Studies PctMin]
,	[Social Studies % Basic] = WKCE.[Social Studies PctBas]
,	[Social Studies % Proficient] = WKCE.[Social Studies PctPrf]
,	[Social Studies % Advanced] = WKCE.[Social Studies PctAdv]


/*
SubjectID	--1RE	2LA	3MA	4SC	5SS
Excluded
Excused
Eligible
PctNotTested
PctNotTested_E
PctExcluded
PctMin
PctMin_E
PctBas
PctBas_E
PctPrf
PctPrf_E
PctAdv
PctAdv_E
FULLKEYOLD
AGENCYKEY
*/

INTO WKCE_DownloadMorph
FROM
WKCE_SubjOnCols WKCE
LEFT JOIN
tblAgenciesWithDistrictAndSchoolNames tA
on WKCE.fullkey = tA.fullkey

														-- ~%~%~%~ --


--2,061,725	--	SELECT count(*) FROM WKCE 
-- 2,061,350 -- SELECT Count(*) FROM WKCE WHERE AGENCYKEY IS NOT NULL	
/*
SELECT * FROM tblAgency WHERE District IN ('7301'	,	'7355'	,	'7354'	,	'7302'	,	'7353'	,	'7352'	,	'7351')
AND right(fullkey, 4) =   'XXXX'

SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'WKCE'
ORDER BY xoffset


SELECT sc.* FROM
syscolumns sc INNER JOIN  sysobjects so
on sc.id = so.id and so.name = 'tblAgency'
ORDER BY xoffset

*/