USE Wisconsin
GO

-- ~%~%~%~%~%~ -- Replication of table, WKCE with separate columns for subjects instead of the SubjectID columns
-- ~%~%~%~%~%~ -- Created for Charter Schools' download feature; May, 2006 -- MZD

IF EXISTS (
		SELECT name FROM sysobjects WHERE name = N'WKCE_SubjOnCols'
)	DROP TABLE WKCE_SubjOnCols
GO

--SubjectID	--1RE	2LA	3MA	4SC	5SS
-- SELECT Count(*) FROM WKCE	 -- 2,061,725
--WHERE AGENCYKEY IS NOT NULL		--2,061,350

-- ** count(WKCE )/ 5 = 412,345
-- ** count(WKCE  WHERE AGENCYKEY IS NOT NULL )/ 5 = 412,270

-- SELECT INTO	--412,270 rows (inner Join); 412645 (full outer)
SELECT RE.[FullKey],	RE.[Grade],	RE.[GroupNum], RE.[FULLKEYOLD],	RE.[AGENCYKEY],	RE.[Year]
,	[Reading Enrolled] =  RE.[Enrolled] 
,	[Reading Included] =  RE.[Included] 
,	[Reading Excluded] =  RE.[Excluded] 
,	[Reading Excused] =  RE.[Excused] 
,	[Reading Eligible] =  RE.[Eligible] 
,	[Reading PctNotTested] =  RE.[PctNotTested] 
,	[Reading PctNotTested_E] =  RE.[PctNotTested_E] 
,	[Reading PctExcluded] =  RE.[PctExcluded] 
,	[Reading PctMin] =  RE.[PctMin] 
,	[Reading PctMin_E] =  RE.[PctMin_E] 
,	[Reading PctBas] =  RE.[PctBas] 
,	[Reading PctBas_E] =  RE.[PctBas_E] 
,	[Reading PctPrf] =  RE.[PctPrf] 
,	[Reading PctPrf_E] =  RE.[PctPrf_E] 
,	[Reading PctAdv] =  RE.[PctAdv] 
,	[Reading PctAdv_E] =  RE.[PctAdv_E] 
							-- ~%~%~%~ --
,	[Language Arts Enrolled] =  LA.[Enrolled] 
,	[Language Arts Included] =  LA.[Included] 
,	[Language Arts Excluded] =  LA.[Excluded] 
,	[Language Arts Excused] =  LA.[Excused] 
,	[Language Arts Eligible] =  LA.[Eligible] 
,	[Language Arts PctNotTested] =  LA.[PctNotTested] 
,	[Language Arts PctNotTested_E] =  LA.[PctNotTested_E] 
,	[Language Arts PctExcluded] =  LA.[PctExcluded] 
,	[Language Arts PctMin] =  LA.[PctMin] 
,	[Language Arts PctMin_E] =  LA.[PctMin_E] 
,	[Language Arts PctBas] =  LA.[PctBas] 
,	[Language Arts PctBas_E] =  LA.[PctBas_E] 
,	[Language Arts PctPrf] =  LA.[PctPrf] 
,	[Language Arts PctPrf_E] =  LA.[PctPrf_E] 
,	[Language Arts PctAdv] =  LA.[PctAdv] 
,	[Language Arts PctAdv_E] =  LA.[PctAdv_E] 
							-- ~%~%~%~ --
,	[Math Enrolled] =  MA.[Enrolled] 
,	[Math Included] =  MA.[Included] 
,	[Math Excluded] =  MA.[Excluded] 
,	[Math Excused] =  MA.[Excused] 
,	[Math Eligible] =  MA.[Eligible] 
,	[Math PctNotTested] =  MA.[PctNotTested] 
,	[Math PctNotTested_E] =  MA.[PctNotTested_E] 
,	[Math PctExcluded] =  MA.[PctExcluded] 
,	[Math PctMin] =  MA.[PctMin] 
,	[Math PctMin_E] =  MA.[PctMin_E] 
,	[Math PctBas] =  MA.[PctBas] 
,	[Math PctBas_E] =  MA.[PctBas_E] 
,	[Math PctPrf] =  MA.[PctPrf] 
,	[Math PctPrf_E] =  MA.[PctPrf_E] 
,	[Math PctAdv] =  MA.[PctAdv] 
,	[Math PctAdv_E] =  MA.[PctAdv_E]
							-- ~%~%~%~ --
,	[Science Enrolled] =  MA.[Enrolled] 
,	[Science Included] =  MA.[Included] 
,	[Science Excluded] =  MA.[Excluded] 
,	[Science Excused] =  MA.[Excused] 
,	[Science Eligible] =  MA.[Eligible] 
,	[Science PctNotTested] =  MA.[PctNotTested] 
,	[Science PctNotTested_E] =  MA.[PctNotTested_E] 
,	[Science PctExcluded] =  MA.[PctExcluded] 
,	[Science PctMin] =  MA.[PctMin] 
,	[Science PctMin_E] =  MA.[PctMin_E] 
,	[Science PctBas] =  MA.[PctBas] 
,	[Science PctBas_E] =  MA.[PctBas_E] 
,	[Science PctPrf] =  MA.[PctPrf] 
,	[Science PctPrf_E] =  MA.[PctPrf_E] 
,	[Science PctAdv] =  MA.[PctAdv] 
,	[Science PctAdv_E] =  MA.[PctAdv_E]
							-- ~%~%~%~ --
,	[Social Studies Enrolled] =  SS.[Enrolled] 
,	[Social Studies Included] =  SS.[Included] 
,	[Social Studies Excluded] =  SS.[Excluded] 
,	[Social Studies Excused] =  SS.[Excused] 
,	[Social Studies Eligible] =  SS.[Eligible] 
,	[Social Studies PctNotTested] =  SS.[PctNotTested] 
,	[Social Studies PctNotTested_E] =  SS.[PctNotTested_E] 
,	[Social Studies PctExcluded] =  SS.[PctExcluded] 
,	[Social Studies PctMin] =  SS.[PctMin] 
,	[Social Studies PctMin_E] =  SS.[PctMin_E] 
,	[Social Studies PctBas] =  SS.[PctBas] 
,	[Social Studies PctBas_E] =  SS.[PctBas_E] 
,	[Social Studies PctPrf] =  SS.[PctPrf] 
,	[Social Studies PctPrf_E] =  SS.[PctPrf_E] 
,	[Social Studies PctAdv] =  SS.[PctAdv] 
,	[Social Studies PctAdv_E] =  SS.[PctAdv_E]
							-- ~%~%~%~ --
INTO WKCE_SubjOnCols
FROM
( SELECT * FROM WKCE WHERE SubjectID = '1RE' ) RE	-- 412,345
 INNER JOIN 
( SELECT * FROM WKCE WHERE SubjectID = '2LA' ) LA -- 412,345
on RE.[FullKey] = LA.[FullKey]  AND  RE.[Grade] = LA.[Grade]  AND  RE.[GroupNum] = LA.[GroupNum]   AND  	RE.[AGENCYKEY] = LA.[AGENCYKEY]  AND  	RE.[Year] = LA.[Year]	 AND   RE.[FULLKEYOLD] = LA.[FULLKEYOLD]
INNER JOIN
( SELECT * FROM WKCE WHERE SubjectID = '3MA' ) MA -- 412,345
on RE.[FullKey] = MA.[FullKey]  AND  RE.[Grade] = MA.[Grade]  AND  RE.[GroupNum] = MA.[GroupNum]  AND  	RE.[AGENCYKEY] = MA.[AGENCYKEY]  AND  	RE.[Year] = MA.[Year]	 AND   RE.[FULLKEYOLD] = MA.[FULLKEYOLD]
INNER JOIN
( SELECT * FROM WKCE WHERE SubjectID = '4SC') SC -- 412,345
on RE.[FullKey] = SC.[FullKey]  AND  RE.[Grade] = SC.[Grade]  AND  RE.[GroupNum] = SC.[GroupNum]  AND  	RE.[AGENCYKEY] = SC.[AGENCYKEY]  AND  	RE.[Year] = SC.[Year] AND   RE.[FULLKEYOLD] = SC.[FULLKEYOLD]
INNER JOIN
( SELECT * FROM WKCE WHERE SubjectID = '5SS' ) SS -- 412,345
on RE.[FullKey] = SS.[FullKey]  AND  RE.[Grade] = SS.[Grade]  AND  RE.[GroupNum] = SS.[GroupNum]  AND  	RE.[AGENCYKEY] = SS.[AGENCYKEY]  AND  	RE.[Year] = SS.[Year] AND   RE.[FULLKEYOLD] = SS.[FULLKEYOLD]

GO

CREATE CLUSTERED INDEX [clustered_WKCE_SubjOnCols_] ON [dbo].[WKCE_SubjOnCols] 
(
	[FullKey] ASC,
	[Grade] ASC,
	[GroupNum] ASC,
	[AGENCYKEY] ASC,
	[Year] ASC
) ON [PRIMARY]
GO

/*
,	[Enrolled]
,	[Included]
,	[Excluded]
,	[Excused]
,	[Eligible]
,	[PctNotTested]
,	[PctNotTested_E]
,	[PctExcluded]
,	[PctMin]
,	[PctMin_E]
,	[PctBas]
,	[PctBas_E]
,	[PctPrf]
,	[PctPrf_E]
,	[PctAdv]
,	[PctAdv_E]
*/
