-- built an all-wkce source table from the '01 structure - add hard-coded years 
-- try mapping all four source files - DTS may match 'em up OK 

-- 98
SELECT 
[CESA], [OrgLevel], [Grade], [DistNumb], [SchlNumb], [StudGrp#], [DistName], [SchlName], [StudGroup],          [Enrolled], [#Incl%s],

				    [%NT_Rdg],           	       [%Min_Rdg],             [%Bas_Rdg],              [%Prf_Rdg],             [%Adv_Rdg],
				    [%NT_Lng], 		 	       [%Min_Lng], 	       [%Bas_Lng], 		[%Prf_Lng], 	  	[%Adv_Lng],
				    [%NT_Math], 	 	       [%Min_Math],	       [%Bas_Math], 		[%Prf_Math], 		[%Adv_Math],
				    [%NT_Scnc], 	 	       [%Min_Scnc], 	       [%Bas_Scnc], 		[%Prf_Scnc], 		[%Adv_Scnc],
				    [%NT_Soc], 		 	       [%Min_Soc], 	       [%Bas_Soc], 		[%Prf_Soc], 		[%Adv_Soc],

[WrtgHol], [NPR_Rdg], [NPR_Lng], [NPR_Math], [NPR_Scnc], [NPR_Soc] 

FROM [Wisconsin].[dbo].[WkceSource98]

-- 99? --> ** CHECK ** 
SELECT 
[CESA], [OrgLevel], [Grade], [DistNumb], [SchlNumb], [StudGrp],  [DistName], [SchlName], [StudGroup], [Blank], [Enrolled], [#Incl%s], 

[Excl_Rdg], [ExcusRdg], [Elig_Rdg],[%NT_Rdg], [%NT_RdgE],	       [%Min_Rdg], [%Min_RdE], [%Bas_Rdg], [%Bas_RdE],  [%Prf_Rdg], [%Prf_RdE], [%Adv_Rdg], [%Adv_RdE], 
[Excl_Lng], [ExcusLng], [Elig_Lng],[%NT_Lng], [%NT_LngE],	       [%Min_Lng], [%Min_LngE],[%Bas_Lng], [%Bas_LngE], [%Prf_Lng], [%Prf_LngE],[%Adv_Lng], [%Adv_LngE], 
[Excl_Mth], [ExcusMth], [Elig_Mth],[%NT_Math],[%NT_MthE],	       [%Min_Math],[%Min_MthE],[%Bas_Math],[%Bas_MthE], [%Prf_Math],[%Prf_MthE],[%Adv_Math],[%Adv_MthE], 
[Excl_Scn], [ExcusScn], [Elig_Scn],[%NT_Scnc],[%NT_ScnE],	       [%Min_Scnc],[%Min_ScnE],[%Bas_Scnc],[%Bas_ScnE], [%Prf_Scnc],[%Prf_ScnE],[%Adv_Scnc],[%Adv_ScnE], 
[Excl_Soc], [ExcusSoc], [Elig_Soc],[%NT_Soc], [%NT_SocE],	       [%Min_Soc], [%Min_SocE],[%Bas_Soc], [%Bas_SocE], [%Prf_Soc], [%Prf_SocE],[%Adv_Soc], [%Adv_SocE], 

[WrtgHol], [NPR_Rdg], [NPR_Lng], [NPR_Math], [NPR_Scnc], [NPR_Soc] 

FROM [Wisconsin].[dbo].[WkceSource]


-- 00
SELECT 
[CESA], [OrgLevel], [Grade], [DistNumb], [SchlNumb], [StudGrp],  [DistName], [SchlName], [StudGroup], [Blank], [Enrolled], [#Incl%s], 

[Excl_Rdg], [ExcusRdg], [Elig_Rdg], [%NT_Rdg], [%NT_RdgE], [%Alt_Rdg], [%Min_Rdg], [%Min_RdE], [%Bas_Rdg], [%Bas_RdE],  [%Prf_Rdg], [%Prf_RdE], [%Adv_Rdg], [%Adv_RdE], 
[Excl_Lng], [ExcusLng], [Elig_Lng], [%NT_Lng], [%NT_LngE], [%Alt_Lng], [%Min_Lng], [%Min_LngE],[%Bas_Lng], [%Bas_LngE], [%Prf_Lng], [%Prf_LngE],[%Adv_Lng], [%Adv_LngE], 
[Excl_Mth], [ExcusMth], [Elig_Mth], [%NT_Math],[%NT_MthE], [%Alt_Mth], [%Min_Math],[%Min_MthE],[%Bas_Math],[%Bas_MthE], [%Prf_Math],[%Prf_MthE],[%Adv_Math],[%Adv_MthE], 
[Excl_Scn], [ExcusScn], [Elig_Scn], [%NT_Scnc],[%NT_ScnE], [%Alt_Scn], [%Min_Scnc],[%Min_ScnE],[%Bas_Scnc],[%Bas_ScnE], [%Prf_Scnc],[%Prf_ScnE],[%Adv_Scnc],[%Adv_ScnE],
[Excl_Soc], [ExcusSoc], [Elig_Soc], [%NT_Soc], [%NT_SocE], [%Alt_Soc], [%Min_Soc], [%Min_SocE],[%Bas_Soc], [%Bas_SocE], [%Prf_Soc], [%Prf_SocE],[%Adv_Soc], [%Adv_SocE], 

[WrtgHol], [NPR_Rdg], [NPR_Lng], [NPR_Math], [NPR_Scnc], [NPR_Soc] 

FROM [Wisconsin].[dbo].[WkceSource2k]


--01
SELECT --[AGENCYTYPE], [AGENCYKEY], [YEAR], 
[CESA], [OrgLevel], [Grade], [DistNumb], [SchlNumb], [StudGrp], [DistName], [SchlName], [StudGroup], [Blank], [Enrolled], [#Incl%s], 
[Excl_Rdg], [ExcusRdg], [Elig_Rdg], [%NT_Rdg], [%NT_RdgE], [%Alt_Rdg], [%Min_Rdg], [%Min_RdE], [%Bas_Rdg], [%Bas_RdE],  [%Prf_Rdg], [%Prf_RdE],  [%Adv_Rdg], [%Adv_RdE], 
[Excl_Lng], [ExcusLng], [Elig_Lng], [%NT_Lng], [%NT_LngE], [%Alt_Lng], [%Min_Lng], [%Min_LngE],[%Bas_Lng], [%Bas_LngE], [%Prf_Lng], [%Prf_LngE], [%Adv_Lng], [%Adv_LngE], 
[Excl_Mth], [ExcusMth], [Elig_Mth], [%NT_Math],[%NT_MthE], [%Alt_Mth], [%Min_Math],[%Min_MthE],[%Bas_Math],[%Bas_MthE], [%Prf_Math],[%Prf_MthE], [%Adv_Math],[%Adv_MthE], 
[Excl_Scn], [ExcusScn], [Elig_Scn], [%NT_Scnc],[%NT_ScnE], [%Alt_Scn], [%Min_Scnc],[%Min_ScnE],[%Bas_Scnc],[%Bas_ScnE], [%Prf_Scnc],[%Prf_ScnE], [%Adv_Scnc],[%Adv_ScnE], 
[Excl_Soc], [ExcusSoc], [Elig_Soc], [%NT_Soc], [%NT_SocE], [%Alt_Soc], [%Min_Soc], [%Min_SocE],[%Bas_Soc], [%Bas_SocE], [%Prf_Soc], [%Prf_SocE], [%Adv_Soc], [%Adv_SocE], 

[WrtgHol], [NPR_Rdg], [NPR_Lng], [NPR_Math], [NPR_Scnc], [NPR_Soc] 

FROM [Wisconsin].[dbo].[WkceSource01]
