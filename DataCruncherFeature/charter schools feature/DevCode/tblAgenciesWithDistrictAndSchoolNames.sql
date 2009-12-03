USE Wisconsin
GO

--~%~%~%~% CREATE Temp Table, tblAgenciesWithDistrictAndSchoolNames

IF EXISTS (
		SELECT name FROM sysobjects WHERE name = N'tblAgenciesWithDistrictAndSchoolNames'
)
DROP TABLE tblAgenciesWithDistrictAndSchoolNames
GO

SELECT * INTO tblAgenciesWithDistrictAndSchoolNames FROM
(
				SELECT d.[District Name]	,	s.*  
					--DISTINCT s.District--, s.Year
					FROM
					(	-- Schools Query: 41547; 3413
							SELECT 
								[Year]	,		[AgencyKey]	,	[FullKey]	,	[District Number] = [District]	,	[School Number] = [School]	,	[SchoolOrg]	,	[AgencyType]	
							,	[AgencyTypeOrg]	,	[SchoolType]	,	[SchoolTypeOrg]	,	[School Name] = [Name]	,	[CESA]	,	[County]	,	[LowGrade]	,	[LowGradeOrg]	
							,	[HighGrade]	,	[HighGradeOrg]	,	[ParentKey]	,	[SchoolCat]	,	[UHSIndic]	,	[PartSchIndic]	,	[SMS]			
							 FROM tblAgency
							WHERE right(fullkey, 4) <> 'XXXX' AND [Year] = 2006
					) s 
						LEFT JOIN
						 (-- Disctricts Query 533
							SELECT 	[Year]	,	[AgencyKey]	,	[FullKey]	,	[District]	,	[School]	,	[SchoolOrg]	,	[AgencyType]	,	[AgencyTypeOrg]	,	[SchoolType]	,	[SchoolTypeOrg]	,	[District Name] = [Name]
							,	[CESA]	,	[County]	,	[LowGrade]	,	[LowGradeOrg]	,	[HighGrade]	,	[HighGradeOrg]	,	[ParentKey]	,	[SchoolCat]	,	[UHSIndic]	,	[PartSchIndic]	,	[SMS]
							 FROM tblAgency	WHERE		right(fullkey, 4) =  'XXXX' AND left(fullkey,1) <> 'X'  AND [Year] = 2006 
						) d 
					on left(s.fullkey, 6) = left(d.fullkey, 6) 
					WHERE d.fullkey IS NOT NULL

					UNION

					SELECT 	[District Name] = [Name]	,	[Year]	,	[AgencyKey]	,	[FullKey]	,	[District]	,	[School]	,	[SchoolOrg]	,	[AgencyType]	,	[AgencyTypeOrg]	,	[SchoolType]	,	[SchoolTypeOrg]	,	[Name]
					,	[CESA]	,	[County]	,	[LowGrade]	,	[LowGradeOrg]	,	[HighGrade]	,	[HighGradeOrg]	,	[ParentKey]	,	[SchoolCat]	,	[UHSIndic]	,	[PartSchIndic]	,	[SMS]
					FROM tblAgency	WHERE		right(fullkey, 4) =  'XXXX' AND left(fullkey,1) <> 'X'  AND [Year] = 2006 
) source

GO


CREATE CLUSTERED INDEX [clustered_tblAgenciesWithDistrictAndSchoolNames_] ON [dbo].[tblAgenciesWithDistrictAndSchoolNames] 
(
	[FullKey] ASC,
	[Year] ASC
) ON [PRIMARY]
GO


--	~%~%~%~	--
