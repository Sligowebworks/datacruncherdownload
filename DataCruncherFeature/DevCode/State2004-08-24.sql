-- 14 rows
SELECT DistState as '  ', Subject, [Credits Required by District], [Credits Required by State] as 'Credits Required by State Law', [District Requirements Meet or Exceed Law], 
[% of Districts Where Credit Requirements Exceed State Law] 
from v_Grad_Reqs 
where (Fullkey = '02326903XXXX' or Fullkey = 'XXXXXXXXXXXX') and year = '2003' and SubjectID >= 1 and SubjectID <= 7 and v_Grad_Reqs.year <= '2003' 
ORDER BY DISTSTATE, SubjectID;
--SELECT DistState as '  ', Subject, [Credits Required by District], [Credits Required by State] as 'Credits Required by State Law', [District Requirements Meet or Exceed Law], [% of Districts Where Credit Requirements Exceed State Law] from v_Grad_Reqs where (Fullkey = '02326903XXXX' or Fullkey = 'XXXXXXXXXXXX') and year = '2003' and SubjectID >= 1 and SubjectID <= 7 and v_Grad_Reqs.year <= '2003' ORDER BY DISTSTATE, SubjectID; 

SELECT DistState as '  ', Subject, [Credits Required by District], [Credits Required by State] as 'Credits Required by State Law', [District Requirements Meet or Exceed Law], 
[% of Districts Where Credit Requirements Exceed State Law] 
from v_Grad_Reqs_jdjtest 
where (Fullkey = '02326903XXXX' or Fullkey = 'XXXXXXXXXXXX') and year = '2003' and SubjectID >= 1 and SubjectID <= 7 and v_Grad_Reqs_jdjtest.year <= '2003' 
ORDER BY DISTSTATE, SubjectID;

--SELECT DistState as '  ', Subject, [Credits Required by District], [Credits Required by State] as 'Credits Required by State Law', [District Requirements Meet or Exceed Law], [% of Districts Where Credit Requirements Exceed State Law] from v_Grad_Reqs_jdjtest where (Fullkey = '02326903XXXX' or Fullkey = 'XXXXXXXXXXXX') and year = '2003' and SubjectID >= 1 and SubjectID <= 7 and v_Grad_Reqs_jdjtest.year <= '2003' ORDER BY DISTSTATE, SubjectID; 

