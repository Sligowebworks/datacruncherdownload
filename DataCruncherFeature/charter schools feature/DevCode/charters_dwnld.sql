USE Wisconsin
GO
/***
* MAP:
*		1)  drop the table (comment out if first time)
*		2)    SELECT
*				- column definition sections:
*					- District and School info
*					- Student Info
*					- "Topic" Info (measures)
*		3)  INTO CharterDownloadTable2006_05_18
*		4) FROM "UNION ALL" of data sets with alias, "Source":
*				- tblWSASWithCountsSourceOrg
*				- [WSAS_EDISA_Source]  WHERE [Year] = '2003'
*				- WKCE
*		5)	LEFT JOIN tblAgency tA on Source.[Agency Key] = tA.AgencyKey 
*				LEFT JOIN SchoolTypes Stype on tA.SchoolType = TypeNUM
*				LEFT JOIN groups on [Student Group] = groupnum
*
*
***/

--SELECT * FROM tblWSASWithCountsSource
DROP TABLE CharterDownloadTable2006_05_18

GO

SELECT --DISTINCT

																								-- ~%~%~%~  [District/School Info]  ~%~%~%~ --

  Source.[Year] 
, Source.[Agency Key]
, Source.CESA
, Source.[District Number]
, Source.[School Number] 
, Source.[Agency Type]
--, TYPENUM
--, ta.fullkey
, [School Type] = CASE 
		WHEN right(tA.fullkey,1) = 'X'  THEN 'Summary' 
  		WHEN TYPENUM = 4 OR TYPENUM = 5 THEN 'Junior/Middle' 
		ELSE  IsNull(Stype.Name , 'Summary')
  END
, [Charter] = CASE tA.SchoolCat WHEN 'CHR' THEN 'Y' ELSE 'N' END
, [District Name]
, [School Name]

																								-- ~%~%~%~  [Student Info]  ~%~%~%~ --

, [Grade Label] = Source.Grade

--, groupnum
, [Race/Ethnicity] =
	CASE
		WHEN groupnum >= 15 AND groupnum <= 20 THEN groupname
		ELSE 'ALL' 
	END
, [Gender] = 
	CASE
		WHEN  11 <= groupnum AND groupnum <= 13 THEN groupname
		ELSE 'ALL'
	END
, [English Proficiency] =
	CASE
		WHEN  groupnum IN (21, 22) THEN groupname
		ELSE 'ALL'
	END
, [Migrant Status] = 
	CASE
		WHEN  groupnum IN (23, 24) THEN groupname
		ELSE 'ALL'
	END
, [Disability Status] =
	CASE
		WHEN  groupnum IN (25, 26) THEN groupname
		ELSE 'ALL'
	END
, [Economically Disadvantaged Status] = 
	CASE
		WHEN  groupnum IN (27, 28) THEN groupname
		ELSE 'ALL'
	END

																								-- ~%~%~%~ [Topic Info]  ~%~%~%~ --

, [Total Enrollment-PI 1290 definition]
, [Total Enrollment-WSAS]
, [Enrollment included in %s and other WSAS results]

, [Reading N NO WSAS-Total]
, [Reading N NO WSAS-Excused by Parent]
, [Reading N NO WSAS-Reasons Unknown]
, [Reading N Pre-Req Skill -Total]
, [Reading N Pre-Req Skill 1]
, [Reading N Pre-Req Skill 2]
, [Reading N Pre-Req Skill 3]
, [Reading N Pre-Req Skill 4]
, [Reading N Pre-Req English -Total]
, [Reading N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
, [Reading N Pre-Req English Early Production (Basic beginning in 2003-04)]
, [Reading N Pre-Req English - Proficient]
, [Reading N Pre-Req English - Advanced]
, [Reading N Min. Perf.]
, [Reading N Basic]
, [Reading N Proficient]
, [Reading N Advanced]
, [Reading  % NO WSAS-Total]
, [Reading % NO WSAS-Excused by Parent]
, [Reading % NO WSAS-Reasons Unknown]
, [Reading % Pre-Req Skill -Total]
, [Reading % Pre-Req Skill 1]
, [Reading % Pre-Req Skill 2]
, [Reading % Pre-Req Skill 3]
, [Reading % Pre-Req Skill 4]
, [Reading % Pre-Req English -Total]
, [Reading % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
, [Reading % Pre-Req English Early Production (Basic beginning in 2003-04)]
, [Reading % Pre-Req English - Proficient]
, [Reading % Pre-Req English - Advanced]
, [Reading % Min. Perf.]
, [Reading % Basic]
, [Reading % Proficient]
, [Reading % Advanced]
							-- ~%~%~%~ --
, [Language Arts N NO WSAS-Total]
, [Language Arts N NO WSAS-Excused by Parent]
, [Language Arts N NO WSAS-Reasons Unknown]
, [Language Arts N Pre-Req Skill -Total]
, [Language Arts N Pre-Req Skill 1]
, [Language Arts N Pre-Req Skill 2]
, [Language Arts N Pre-Req Skill 3]
, [Language Arts N Pre-Req Skill 4]
, [Language Arts N Pre-Req English -Total]
, [Language Arts N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
, [Language Arts N Pre-Req English Early Production (Basic beginning in 2003-04)]
, [Language Arts N Pre-Req English - Proficient]
, [Language Arts N Pre-Req English - Advanced]
, [Language Arts N Min. Perf.]
, [Language Arts N Basic]
, [Language Arts N Proficient]
, [Language Arts N Advanced]
, [Language Arts % NO WSAS-Total]
, [Language Arts % NO WSAS-Excused by Parent]
, [Language Arts % NO WSAS-Reasons Unknown]
, [Language Arts % Pre-Req Skill -Total]
, [Language Arts % Pre-Req Skill 1]
, [Language Arts % Pre-Req Skill 2]
, [Language Arts % Pre-Req Skill 3]
, [Language Arts % Pre-Req Skill 4]
, [Language Arts % Pre-Req English -Total]
, [Language Arts % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
, [Language Arts % Pre-Req English Early Production (Basic beginning in 2003-04)]
, [Language Arts % Pre-Req English - Proficient]
, [Language Arts % Pre-Req English - Advanced]
, [Language Arts % Min. Perf.]
, [Language Arts % Basic]
, [Language Arts % Proficient]
, [Language Arts % Advanced]
							-- ~%~%~%~ --
, [Math N NO WSAS-Total]
, [Math N NO WSAS-Excused by Parent]
, [Math N NO WSAS-Reasons Unknown]
, [Math N Pre-Req Skill -Total]
, [Math N Pre-Req Skill 1]
, [Math N Pre-Req Skill 2]
, [Math N Pre-Req Skill 3]
, [Math N Pre-Req Skill 4]
, [Math N Pre-Req English -Total]
, [Math N Pre-Req English Minimal]
, [Math N Pre-Req English Basic]
, [Math N Pre-Req English Proficient]
, [Math N Pre-Req English Advanced]
, [Math N Min. Perf.]
, [Math N Basic]
, [Math N Proficient]
, [Math N Advanced]
, [Math  % NO WSAS-Total]
, [Math % NO WSAS-Excused by Parent]
, [Math % NO WSAS-Reasons Unknown]
, [Math % Pre-Req Skill -Total]
, [Math % Pre-Req Skill 1]
, [Math % Pre-Req Skill 2]
, [Math % Pre-Req Skill 3]
, [Math % Pre-Req Skill 4]
, [Math % Pre-Req English -Total]
, [Math % Pre-Req English Minimal]
, [Math % Pre-Req English Basic]
, [Math % Pre-Req English Proficient]
, [Math % Pre-Req English Advanced]
, [Math % Min. Perf.]
, [Math % Basic]
, [Math % Proficient]
, [Math % Advanced]
							-- ~%~%~%~ --
, [Science N NO WSAS-Total]
, [Science N NO WSAS-Excused by Parent]
, [Science N NO WSAS-Reasons Unknown]
, [Science N Pre-Req Skill -Total]
, [Science N Pre-Req Skill 1]
, [Science N Pre-Req Skill 2]
, [Science N Pre-Req Skill 3]
, [Science N Pre-Req Skill 4]
, [Science N Pre-Req English -Total]
, [Science N Pre-Req English Minimal]
, [Science N Pre-Req English Basic]
, [Science N Pre-Req English Proficient]
, [Science N Pre-Req English Advanced]
, [Science N Min. Perf.]
, [Science N Basic]
, [Science N Proficient]
, [Science N Advanced]
, [Science  % NO WSAS-Total]
, [Science % NO WSAS-Excused by Parent]
, [Science % NO WSAS-Reasons Unknown]
, [Science % Pre-Req Skill -Total]
, [Science % Pre-Req Skill 1]
, [Science % Pre-Req Skill 2]
, [Science % Pre-Req Skill 3]
, [Science % Pre-Req Skill 4]
, [Science % Pre-Req English -Total]
, [Science % Pre-Req English Minimal]
, [Science % Pre-Req English Basic]
, [Science % Pre-Req English Proficient]
, [Science % Pre-Req English Advanced]
, [Science % Min. Perf.]
, [Science % Basic]
, [Science % Proficient]
, [Science % Advanced]
							-- ~%~%~%~ --
, [Social Studies N NO WSAS-Total]
, [Social Studies N NO WSAS-Excused by Parent]
, [Social Studies N NO WSAS-Reasons Unknown]
, [Social Studies N Pre-Req Skill -Total]
, [Social Studies N Pre-Req Skill 1]
, [Social Studies N Pre-Req Skill 2]
, [Social Studies N Pre-Req Skill 3]
, [Social Studies N Pre-Req Skill 4]
, [Social Studies N Pre-Req English -Total]
, [Social Studies N Pre-Req English Minimal]
, [Social Studies N Pre-Req English Basic]
, [Social Studies N Pre-Req English Proficient]
, [Social Studies N Pre-Req English Advanced]
, [Social Studies N Min. Perf.]
, [Social Studies N Basic]
, [Social Studies N Proficient]
, [Social Studies N Advanced]
, [Social Studies  % NO WSAS-Total]
, [Social Studies % NO WSAS-Excused by Parent]
, [Social Studies % NO WSAS-Reasons Unknown]
, [Social Studies % Pre-Req Skill -Total]
, [Social Studies % Pre-Req Skill 1]
, [Social Studies % Pre-Req Skill 2]
, [Social Studies % Pre-Req Skill 3]
, [Social Studies % Pre-Req Skill 4]
, [Social Studies % Pre-Req English -Total]
, [Social Studies % Pre-Req English Minimal]
, [Social Studies % Pre-Req English Basic]
, [Social Studies % Pre-Req English Proficient]
, [Social Studies % Pre-Req English Advanced]
, [Social Studies % Min. Perf.]
, [Social Studies % Basic]
, [Social Studies % Proficient]
, [Social Studies % Advanced]

INTO CharterDownloadTable2006_05_18
																														-- ~%~%~%~ -- 
FROM
(
SELECT 
	[Year]
,	[Test Date]
,	[Org Level]
,	[Grade]
,	[District Name]
,	[District Number]
,	[School Name]
,	[School Number]
,	[Agency Type]
,	[Agency Key]
,	[CESA]
,	[Lowest Grade in School]
,	[Student Group]
,	[Total Enrollment-PI 1290 definition]
,	[Total Enrollment-WSAS]
,	[Enrollment included in %s and other WSAS results]
,	[Reading  % NO WSAS-Total]
,	[Reading % NO WSAS-Excused by Parent]
,	[Reading % NO WSAS-Reasons Unknown]
,	[Reading % Pre-Req Skill -Total]
,	[Reading % Pre-Req Skill 1]
,	[Reading % Pre-Req Skill 2]
,	[Reading % Pre-Req Skill 3]
,	[Reading % Pre-Req Skill 4]
,	[Reading % Pre-Req English -Total]
,	[Reading % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
,	[Reading % Pre-Req English Early Production (Basic beginning in 2003-04)]
,	[Reading % Pre-Req English - Proficient]
,	[Reading % Pre-Req English - Advanced]
,	[Reading % Min. Perf.]
,	[Reading % Basic]
,	[Reading % Proficient]
,	[Reading % Advanced]
,	[Language Arts % NO WSAS-Total]
,	[Language Arts % NO WSAS-Excused by Parent]
,	[Language Arts % NO WSAS-Reasons Unknown]
,	[Language Arts % Pre-Req Skill -Total]
,	[Language Arts % Pre-Req Skill 1]
,	[Language Arts % Pre-Req Skill 2]
,	[Language Arts % Pre-Req Skill 3]
,	[Language Arts % Pre-Req Skill 4]
,	[Language Arts % Pre-Req English -Total]
,	[Language Arts % Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
,	[Language Arts % Pre-Req English Early Production (Basic beginning in 2003-04)]
,	[Language Arts % Pre-Req English - Proficient]
,	[Language Arts % Pre-Req English - Advanced]
,	[Language Arts % Min. Perf.]
,	[Language Arts % Basic]
,	[Language Arts % Proficient]
,	[Language Arts % Advanced]
,	[Math  % NO WSAS-Total]
,	[Math % NO WSAS-Excused by Parent]
,	[Math % NO WSAS-Reasons Unknown]
,	[Math % Pre-Req Skill -Total]
,	[Math % Pre-Req Skill 1]
,	[Math % Pre-Req Skill 2]
,	[Math % Pre-Req Skill 3]
,	[Math % Pre-Req Skill 4]
,	[Math % Pre-Req English -Total]
,	[Math % Pre-Req English Minimal]
,	[Math % Pre-Req English Basic]
,	[Math % Pre-Req English Proficient]
,	[Math % Pre-Req English Advanced]
,	[Math % Min. Perf.]
,	[Math % Basic]
,	[Math % Proficient]
,	[Math % Advanced]
,	[Science  % NO WSAS-Total]
,	[Science % NO WSAS-Excused by Parent]
,	[Science % NO WSAS-Reasons Unknown]
,	[Science % Pre-Req Skill -Total]
,	[Science % Pre-Req Skill 1]
,	[Science % Pre-Req Skill 2]
,	[Science % Pre-Req Skill 3]
,	[Science % Pre-Req Skill 4]
,	[Science % Pre-Req English -Total]
,	[Science % Pre-Req English Minimal]
,	[Science % Pre-Req English Basic]
,	[Science % Pre-Req English Proficient]
,	[Science % Pre-Req English Advanced]
,	[Science % Min. Perf.]
,	[Science % Basic]
,	[Science % Proficient]
,	[Science % Advanced]
,	[Social Studies  % NO WSAS-Total]
,	[Social Studies % NO WSAS-Excused by Parent]
,	[Social Studies % NO WSAS-Reasons Unknown]
,	[Social Studies % Pre-Req Skill -Total]
,	[Social Studies % Pre-Req Skill 1]
,	[Social Studies % Pre-Req Skill 2]
,	[Social Studies % Pre-Req Skill 3]
,	[Social Studies % Pre-Req Skill 4]
,	[Social Studies % Pre-Req English -Total]
,	[Social Studies % Pre-Req English Minimal]
,	[Social Studies % Pre-Req English Basic]
,	[Social Studies % Pre-Req English Proficient]
,	[Social Studies % Pre-Req English Advanced]
,	[Social Studies % Min. Perf.]
,	[Social Studies % Basic]
,	[Social Studies % Proficient]
,	[Social Studies % Advanced]
,	[Reading N NO WSAS-Total]
,	[Reading N NO WSAS-Excused by Parent]
,	[Reading N NO WSAS-Reasons Unknown]
,	[Reading N Pre-Req Skill -Total]
,	[Reading N Pre-Req Skill 1]
,	[Reading N Pre-Req Skill 2]
,	[Reading N Pre-Req Skill 3]
,	[Reading N Pre-Req Skill 4]
,	[Reading N Pre-Req English -Total]
,	[Reading N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
,	[Reading N Pre-Req English Early Production (Basic beginning in 2003-04)]
,	[Reading N Pre-Req English - Proficient]
,	[Reading N Pre-Req English - Advanced]
,	[Reading N Min. Perf.]
,	[Reading N Basic]
,	[Reading N Proficient]
,	[Reading N Advanced]
,	[Language Arts N NO WSAS-Total]
,	[Language Arts N NO WSAS-Excused by Parent]
,	[Language Arts N NO WSAS-Reasons Unknown]
,	[Language Arts N Pre-Req Skill -Total]
,	[Language Arts N Pre-Req Skill 1]
,	[Language Arts N Pre-Req Skill 2]
,	[Language Arts N Pre-Req Skill 3]
,	[Language Arts N Pre-Req Skill 4]
,	[Language Arts N Pre-Req English -Total]
,	[Language Arts N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)]
,	[Language Arts N Pre-Req English Early Production (Basic beginning in 2003-04)]
,	[Language Arts N Pre-Req English - Proficient]
,	[Language Arts N Pre-Req English - Advanced]
,	[Language Arts N Min. Perf.]
,	[Language Arts N Basic]
,	[Language Arts N Proficient]
,	[Language Arts N Advanced]
,	[Math N NO WSAS-Total]
,	[Math N NO WSAS-Excused by Parent]
,	[Math N NO WSAS-Reasons Unknown]
,	[Math N Pre-Req Skill -Total]
,	[Math N Pre-Req Skill 1]
,	[Math N Pre-Req Skill 2]
,	[Math N Pre-Req Skill 3]
,	[Math N Pre-Req Skill 4]
,	[Math N Pre-Req English -Total]
,	[Math N Pre-Req English Minimal]
,	[Math N Pre-Req English Basic]
,	[Math N Pre-Req English Proficient]
,	[Math N Pre-Req English Advanced]
,	[Math N Min. Perf.]
,	[Math N Basic]
,	[Math N Proficient]
,	[Math N Advanced]
,	[Science N NO WSAS-Total]
,	[Science N NO WSAS-Excused by Parent]
,	[Science N NO WSAS-Reasons Unknown]
,	[Science N Pre-Req Skill -Total]
,	[Science N Pre-Req Skill 1]
,	[Science N Pre-Req Skill 2]
,	[Science N Pre-Req Skill 3]
,	[Science N Pre-Req Skill 4]
,	[Science N Pre-Req English -Total]
,	[Science N Pre-Req English Minimal]
,	[Science N Pre-Req English Basic]
,	[Science N Pre-Req English Proficient]
,	[Science N Pre-Req English Advanced]
,	[Science N Min. Perf.]
,	[Science N Basic]
,	[Science N Proficient]
,	[Science N Advanced]
,	[Social Studies N NO WSAS-Total]
,	[Social Studies N NO WSAS-Excused by Parent]
,	[Social Studies N NO WSAS-Reasons Unknown]
,	[Social Studies N Pre-Req Skill -Total]
,	[Social Studies N Pre-Req Skill 1]
,	[Social Studies N Pre-Req Skill 2]
,	[Social Studies N Pre-Req Skill 3]
,	[Social Studies N Pre-Req Skill 4]
,	[Social Studies N Pre-Req English -Total]
,	[Social Studies N Pre-Req English Minimal]
,	[Social Studies N Pre-Req English Basic]
,	[Social Studies N Pre-Req English Proficient]
,	[Social Studies N Pre-Req English Advanced]
,	[Social Studies N Min. Perf.]
,	[Social Studies N Basic]
,	[Social Studies N Proficient]
,	[Social Studies N Advanced]

 FROM
tblWSASWithCountsSourceOrg--tblWSASWithCountsSource 

UNION ALL
																														-- ~%~%~%~ -- 
SELECT
  [Year]
, [Test Date]
, [Level]
, [Grade]
, [District Name]
, [District Number]
, [School Name]
, [School Number]
, [Agency Type]
, [Agency Key]
, [CESA]
, [Lowest Grade in School]
, [Student Group]
, [Total Enrollment-PI 1290 definition]
, [Total Enrollment-WSAS]
, [Enrollment included in %s and other WSAS results]
, [Reading % NO WSAS-Total]
, [Reading % NO WSAS-Excused by Parent]
, [Reading % NO WSAS-Reasons Unknown]
, [Reading % Pre-Req Skill -Total]
, [Reading % Pre-Req Skill 1]
, [Reading % Pre-Req Skill 2]
, [Reading % Pre-Req Skill 3]
, [Reading % Pre-Req Skill 4]
, [Reading % Pre-Req English -Total]
, [Reading % Pre-Req English Preproduction]
, [Reading % Pre-Req English Early Production]
, [Reading % Pre-Req English Filler 1]
, [Reading % Pre-Req English Filler 2]
, [Reading % Min. Perf.]
, [Reading % Basic]
, [Reading % Proficient]
, [Reading % Advanced]
, [Language Arts % NO WSAS-Total]
, [Language Arts % NO WSAS-Excused by Parent]
, [Language Arts % NO WSAS-Reasons Unknown]
, [Language Arts % Pre-Req Skill -Total]
, [Language Arts % Pre-Req Skill 1]
, [Language Arts % Pre-Req Skill 2]
, [Language Arts % Pre-Req Skill 3]
, [Language Arts % Pre-Req Skill 4]
, [Language Arts % Pre-Req English -Total]
, [Language Arts % Pre-Req English Preproduction]
, [Language Arts % Pre-Req English Early Production]
, [Language Arts % Pre-Req English Filler 1]
, [Language Arts % Pre-Req English Filler 2]
, [Language Arts % Min. Perf.]
, [Language Arts % Basic]
, [Language Arts % Proficient]
, [Language Arts % Advanced]
, [Math % NO WSAS-Total]
, [Math % NO WSAS-Excused by Parent]
, [Math % NO WSAS-Reasons Unknown]
, [Math % Pre-Req Skill -Total]
, [Math % Pre-Req Skill 1]
, [Math % Pre-Req Skill 2]
, [Math % Pre-Req Skill 3]
, [Math % Pre-Req Skill 4]
, [Math % Pre-Req English -Total]
, [Math % Pre-Req English Minimal]
, [Math % Pre-Req English Basic]
, [Math % Pre-Req English Proficient]
, [Math % Pre-Req English Advanced]
, [Math % Min. Perf.]
, [Math % Basic]
, [Math % Proficient]
, [Math % Advanced]
, [Science % NO WSAS-Total]
, [Science % NO WSAS-Excused by Parent]
, [Science % NO WSAS-Reasons Unknown]
, [Science % Pre-Req Skill -Total]
, [Science % Pre-Req Skill 1]
, [Science % Pre-Req Skill 2]
, [Science % Pre-Req Skill 3]
, [Science % Pre-Req Skill 4]
, [Science % Pre-Req English -Total]
, [Science % Pre-Req English Minimal]
, [Science % Pre-Req English Basic]
, [Science % Pre-Req English Proficient]
, [Science % Pre-Req English Advanced]
, [Science % Min. Perf.]
, [Science % Basic]
, [Science % Proficient]
, [Science % Advanced]
, [Social Studies % NO WSAS-Total]
, [Social Studies % NO WSAS-Excused by Parent]
, [Social Studies % NO WSAS-Reasons Unknown]
, [Social Studies % Pre-Req Skill -Total]
, [Social Studies % Pre-Req Skill 1]
, [Social Studies % Pre-Req Skill 2]
, [Social Studies % Pre-Req Skill 3]
, [Social Studies % Pre-Req Skill 4]
, [Social Studies % Pre-Req English -Total]
, [Social Studies % Pre-Req English Minimal]
, [Social Studies % Pre-Req English Basic]
, [Social Studies % Pre-Req English Proficient]
, [Social Studies % Pre-Req English Advanced]
, [Social Studies % Min. Perf.]
, [Social Studies % Basic]
, [Social Studies % Proficient]
, [Social Studies % Advanced]
, [Reading N NO WSAS-Total] = 'N/A'
, [Reading N NO WSAS-Excused by Parent] = 'N/A'
, [Reading N NO WSAS-Reasons Unknown] = 'N/A'
, [Reading N Pre-Req Skill -Total] = 'N/A'
, [Reading N Pre-Req Skill 1] = 'N/A'
, [Reading N Pre-Req Skill 2] = 'N/A'
, [Reading N Pre-Req Skill 3] = 'N/A'
, [Reading N Pre-Req Skill 4] = 'N/A'
, [Reading N Pre-Req English -Total] = 'N/A'
, [Reading N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
, [Reading N Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
, [Reading N Pre-Req English - Proficient] = 'N/A'
, [Reading N Pre-Req English - Advanced] = 'N/A'
, [Reading N Min. Perf.] = 'N/A'
, [Reading N Basic] = 'N/A'
, [Reading N Proficient] = 'N/A'
, [Reading N Advanced] = 'N/A'
, [Language Arts N NO WSAS-Total] = 'N/A'
, [Language Arts N NO WSAS-Excused by Parent] = 'N/A'
, [Language Arts N NO WSAS-Reasons Unknown] = 'N/A'
, [Language Arts N Pre-Req Skill -Total] = 'N/A'
, [Language Arts N Pre-Req Skill 1] = 'N/A'
, [Language Arts N Pre-Req Skill 2] = 'N/A'
, [Language Arts N Pre-Req Skill 3] = 'N/A'
, [Language Arts N Pre-Req Skill 4] = 'N/A'
, [Language Arts N Pre-Req English -Total] = 'N/A'
, [Language Arts N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
, [Language Arts N Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
, [Language Arts N Pre-Req English - Proficient] = 'N/A'
, [Language Arts N Pre-Req English - Advanced] = 'N/A'
, [Language Arts N Min. Perf.] = 'N/A'
, [Language Arts N Basic] = 'N/A'
, [Language Arts N Proficient] = 'N/A'
, [Language Arts N Advanced] = 'N/A'
, [Math N NO WSAS-Total] = 'N/A'
, [Math N NO WSAS-Excused by Parent] = 'N/A'
, [Math N NO WSAS-Reasons Unknown] = 'N/A'
, [Math N Pre-Req Skill -Total] = 'N/A'
, [Math N Pre-Req Skill 1] = 'N/A'
, [Math N Pre-Req Skill 2] = 'N/A'
, [Math N Pre-Req Skill 3] = 'N/A'
, [Math N Pre-Req Skill 4] = 'N/A'
, [Math N Pre-Req English -Total] = 'N/A'
, [Math N Pre-Req English Minimal] = 'N/A'
, [Math N Pre-Req English Basic] = 'N/A'
, [Math N Pre-Req English Proficient] = 'N/A'
, [Math N Pre-Req English Advanced] = 'N/A'
, [Math N Min. Perf.] = 'N/A'
, [Math N Basic] = 'N/A'
, [Math N Proficient] = 'N/A'
, [Math N Advanced] = 'N/A'
, [Science N NO WSAS-Total] = 'N/A'
, [Science N NO WSAS-Excused by Parent] = 'N/A'
, [Science N NO WSAS-Reasons Unknown] = 'N/A'
, [Science N Pre-Req Skill -Total] = 'N/A'
, [Science N Pre-Req Skill 1] = 'N/A'
, [Science N Pre-Req Skill 2] = 'N/A'
, [Science N Pre-Req Skill 3] = 'N/A'
, [Science N Pre-Req Skill 4] = 'N/A'
, [Science N Pre-Req English -Total] = 'N/A'
, [Science N Pre-Req English Minimal] = 'N/A'
, [Science N Pre-Req English Basic] = 'N/A'
, [Science N Pre-Req English Proficient] = 'N/A'
, [Science N Pre-Req English Advanced] = 'N/A'
, [Science N Min. Perf.] = 'N/A'
, [Science N Basic] = 'N/A'
, [Science N Proficient] = 'N/A'
, [Science N Advanced] = 'N/A'
, [Social Studies N NO WSAS-Total] = 'N/A'
, [Social Studies N NO WSAS-Excused by Parent] = 'N/A'
, [Social Studies N NO WSAS-Reasons Unknown] = 'N/A'
, [Social Studies N Pre-Req Skill -Total] = 'N/A'
, [Social Studies N Pre-Req Skill 1] = 'N/A'
, [Social Studies N Pre-Req Skill 2] = 'N/A'
, [Social Studies N Pre-Req Skill 3] = 'N/A'
, [Social Studies N Pre-Req Skill 4] = 'N/A'
, [Social Studies N Pre-Req English -Total] = 'N/A'
, [Social Studies N Pre-Req English Minimal] = 'N/A'
, [Social Studies N Pre-Req English Basic] = 'N/A'
, [Social Studies N Pre-Req English Proficient] = 'N/A'
, [Social Studies N Pre-Req English Advanced] = 'N/A'
, [Social Studies N Min. Perf.] = 'N/A'
, [Social Studies N Basic] = 'N/A'
, [Social Studies N Proficient] = 'N/A'
, [Social Studies N Advanced] = 'N/A'


FROM [WSAS_EDISA_Source]  WHERE [Year] = '2003'

UNION ALL
																														-- ~%~%~%~ -- 

SELECT 
 [Year]
, [Test Date]
, [Org Level]
, [Grade]
, [District Name]
, [District Number]
, [School Name]
, [School Number]
, [Agency Type]
, [Agency Key]
, [CESA]
, [Lowest Grade in School]
, [Student Group]
, [Total Enrollment-PI 1290 definition]
, [Total Enrollment-WSAS]
, [Enrollment included in %s and other WSAS results]
, [Reading % NO WSAS-Total]
, [Reading % NO WSAS-Excused by Parent]
, [Reading % NO WSAS-Reasons Unknown]
, [Reading % Pre-Req Skill -Total]
, [Reading % Pre-Req Skill 1]
, [Reading % Pre-Req Skill 2]
, [Reading % Pre-Req Skill 3]
, [Reading % Pre-Req Skill 4]
, [Reading % Pre-Req English -Total]
, [Reading % Pre-Req English Preproduction]
, [Reading % Pre-Req English Early Production]
, [Reading % Pre-Req English Filler 1]
, [Reading % Pre-Req English Filler 2]
, [Reading % Min. Perf.]
, [Reading % Basic]
, [Reading % Proficient]
, [Reading % Advanced]
, [Language Arts % NO WSAS-Total]
, [Language Arts % NO WSAS-Excused by Parent]
, [Language Arts % NO WSAS-Reasons Unknown]
, [Language Arts % Pre-Req Skill -Total]
, [Language Arts % Pre-Req Skill 1]
, [Language Arts % Pre-Req Skill 2]
, [Language Arts % Pre-Req Skill 3]
, [Language Arts % Pre-Req Skill 4]
, [Language Arts % Pre-Req English -Total]
, [Language Arts % Pre-Req English Preproduction]
, [Language Arts % Pre-Req English Early Production]
, [Language Arts % Pre-Req English Filler 1]
, [Language Arts % Pre-Req English Filler 2]
, [Language Arts % Min. Perf.]
, [Language Arts % Basic]
, [Language Arts % Proficient]
, [Language Arts % Advanced]
, [Math % NO WSAS-Total]
, [Math % NO WSAS-Excused by Parent]
, [Math % NO WSAS-Reasons Unknown]
, [Math % Pre-Req Skill -Total]
, [Math % Pre-Req Skill 1]
, [Math % Pre-Req Skill 2]
, [Math % Pre-Req Skill 3]
, [Math % Pre-Req Skill 4]
, [Math % Pre-Req English -Total]
, [Math % Pre-Req English Minimal]
, [Math % Pre-Req English Basic]
, [Math % Pre-Req English Proficient]
, [Math % Pre-Req English Advanced]
, [Math % Min. Perf.]
, [Math % Basic]
, [Math % Proficient]
, [Math % Advanced]
, [Science % NO WSAS-Total]
, [Science % NO WSAS-Excused by Parent]
, [Science % NO WSAS-Reasons Unknown]
, [Science % Pre-Req Skill -Total]
, [Science % Pre-Req Skill 1]
, [Science % Pre-Req Skill 2]
, [Science % Pre-Req Skill 3]
, [Science % Pre-Req Skill 4]
, [Science % Pre-Req English -Total]
, [Science % Pre-Req English Minimal]
, [Science % Pre-Req English Basic]
, [Science % Pre-Req English Proficient]
, [Science % Pre-Req English Advanced]
, [Science % Min. Perf.]
, [Science % Basic]
, [Science % Proficient]
, [Science % Advanced]
, [Social Studies % NO WSAS-Total]
, [Social Studies % NO WSAS-Excused by Parent]
, [Social Studies % NO WSAS-Reasons Unknown]
, [Social Studies % Pre-Req Skill -Total]
, [Social Studies % Pre-Req Skill 1]
, [Social Studies % Pre-Req Skill 2]
, [Social Studies % Pre-Req Skill 3]
, [Social Studies % Pre-Req Skill 4]
, [Social Studies % Pre-Req English -Total]
, [Social Studies % Pre-Req English Minimal]
, [Social Studies % Pre-Req English Basic]
, [Social Studies % Pre-Req English Proficient]
, [Social Studies % Pre-Req English Advanced]
, [Social Studies % Min. Perf.]
, [Social Studies % Basic]
, [Social Studies % Proficient]
, [Social Studies % Advanced]
, [Reading N NO WSAS-Total] = 'N/A'
, [Reading N NO WSAS-Excused by Parent] = 'N/A'
, [Reading N NO WSAS-Reasons Unknown] = 'N/A'
, [Reading N Pre-Req Skill -Total] = 'N/A'
, [Reading N Pre-Req Skill 1] = 'N/A'
, [Reading N Pre-Req Skill 2] = 'N/A'
, [Reading N Pre-Req Skill 3] = 'N/A'
, [Reading N Pre-Req Skill 4] = 'N/A'
, [Reading N Pre-Req English -Total] = 'N/A'
, [Reading N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
, [Reading N Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
, [Reading N Pre-Req English - Proficient] = 'N/A'
, [Reading N Pre-Req English - Advanced] = 'N/A'
, [Reading N Min. Perf.] = 'N/A'
, [Reading N Basic] = 'N/A'
, [Reading N Proficient] = 'N/A'
, [Reading N Advanced] = 'N/A'
, [Language Arts N NO WSAS-Total] = 'N/A'
, [Language Arts N NO WSAS-Excused by Parent] = 'N/A'
, [Language Arts N NO WSAS-Reasons Unknown] = 'N/A'
, [Language Arts N Pre-Req Skill -Total] = 'N/A'
, [Language Arts N Pre-Req Skill 1] = 'N/A'
, [Language Arts N Pre-Req Skill 2] = 'N/A'
, [Language Arts N Pre-Req Skill 3] = 'N/A'
, [Language Arts N Pre-Req Skill 4] = 'N/A'
, [Language Arts N Pre-Req English -Total] = 'N/A'
, [Language Arts N Pre-Req English Preproduction (Min. Perf. Beginning in 2003-04)] = 'N/A'
, [Language Arts N Pre-Req English Early Production (Basic beginning in 2003-04)] = 'N/A'
, [Language Arts N Pre-Req English - Proficient] = 'N/A'
, [Language Arts N Pre-Req English - Advanced] = 'N/A'
, [Language Arts N Min. Perf.] = 'N/A'
, [Language Arts N Basic] = 'N/A'
, [Language Arts N Proficient] = 'N/A'
, [Language Arts N Advanced] = 'N/A'
, [Math N NO WSAS-Total] = 'N/A'
, [Math N NO WSAS-Excused by Parent] = 'N/A'
, [Math N NO WSAS-Reasons Unknown] = 'N/A'
, [Math N Pre-Req Skill -Total] = 'N/A'
, [Math N Pre-Req Skill 1] = 'N/A'
, [Math N Pre-Req Skill 2] = 'N/A'
, [Math N Pre-Req Skill 3] = 'N/A'
, [Math N Pre-Req Skill 4] = 'N/A'
, [Math N Pre-Req English -Total] = 'N/A'
, [Math N Pre-Req English Minimal] = 'N/A'
, [Math N Pre-Req English Basic] = 'N/A'
, [Math N Pre-Req English Proficient] = 'N/A'
, [Math N Pre-Req English Advanced] = 'N/A'
, [Math N Min. Perf.] = 'N/A'
, [Math N Basic] = 'N/A'
, [Math N Proficient] = 'N/A'
, [Math N Advanced] = 'N/A'
, [Science N NO WSAS-Total] = 'N/A'
, [Science N NO WSAS-Excused by Parent] = 'N/A'
, [Science N NO WSAS-Reasons Unknown] = 'N/A'
, [Science N Pre-Req Skill -Total] = 'N/A'
, [Science N Pre-Req Skill 1] = 'N/A'
, [Science N Pre-Req Skill 2] = 'N/A'
, [Science N Pre-Req Skill 3] = 'N/A'
, [Science N Pre-Req Skill 4] = 'N/A'
, [Science N Pre-Req English -Total] = 'N/A'
, [Science N Pre-Req English Minimal] = 'N/A'
, [Science N Pre-Req English Basic] = 'N/A'
, [Science N Pre-Req English Proficient] = 'N/A'
, [Science N Pre-Req English Advanced] = 'N/A'
, [Science N Min. Perf.] = 'N/A'
, [Science N Basic] = 'N/A'
, [Science N Proficient] = 'N/A'
, [Science N Advanced] = 'N/A'
, [Social Studies N NO WSAS-Total] = 'N/A'
, [Social Studies N NO WSAS-Excused by Parent] = 'N/A'
, [Social Studies N NO WSAS-Reasons Unknown] = 'N/A'
, [Social Studies N Pre-Req Skill -Total] = 'N/A'
, [Social Studies N Pre-Req Skill 1] = 'N/A'
, [Social Studies N Pre-Req Skill 2] = 'N/A'
, [Social Studies N Pre-Req Skill 3] = 'N/A'
, [Social Studies N Pre-Req Skill 4] = 'N/A'
, [Social Studies N Pre-Req English -Total] = 'N/A'
, [Social Studies N Pre-Req English Minimal] = 'N/A'
, [Social Studies N Pre-Req English Basic] = 'N/A'
, [Social Studies N Pre-Req English Proficient] = 'N/A'
, [Social Studies N Pre-Req English Advanced] = 'N/A'
, [Social Studies N Min. Perf.] = 'N/A'
, [Social Studies N Basic] = 'N/A'
, [Social Studies N Proficient] = 'N/A'
, [Social Studies N Advanced] = 'N/A'

FROM WKCE_DownloadMorph
																														-- ~%~%~%~ -- 
)
 Source 
LEFT JOIN tblAgency tA 
on Source.[Agency Key] = tA.AgencyKey 
LEFT JOIN SchoolTypes Stype
on tA.SchoolType = TypeNUM
LEFT JOIN groups
on [Student Group] = groupnum

GO


/*

SELECT DISTINCT [Agency Type], [Agency Key], [School Name] FROM tblWSASWithCountsSource WHERE [Agency Type] = '03'


SELECT DISTINCT SchoolType, S.Name FROM tblAgency A  INNER JOIN SchoolTypes S on A.SchoolType = TypeNUM

SELECT * FROM SchoolTypes

SELECT * FROM groups

SELECT subjectID  FROM WSAS

*/