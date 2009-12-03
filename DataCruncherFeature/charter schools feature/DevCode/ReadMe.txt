Date: Mon, 22 May 2006 15:27:09 -0400
From: Michael Z Daryabeygi <mzd@sligowebworks.com>
To: Jim Johnson <jdj@sligowebworks.com>
Subject: WI: Charters' download  scripts



** charters_dwnld.sql
is where it all comes together.
This query is not working yet because the select statements don't match.
Plus, the unions need to be verified to be sure that the columns match up correctly.


** tblAgenciesWithDistrictAndSchoolNames.sql
is a supporting table used in WKCEmorph.sql.


** WKCE_SubjOnCols.sql
pivots WKCE to get all subjects into one record


** WKCEmorph.sql
actually creates a table called WKCE_DownloadMorph


getcolumns.sql is not tied into any other script, just a scratch pad and included for completeness.


-- 
~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`
Michael Z Daryabeygi
Database Applications Developer
Sligo Computer Services Co-op
www.sligowebworks.com
301.270.9673 x 304
~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`~,~`

