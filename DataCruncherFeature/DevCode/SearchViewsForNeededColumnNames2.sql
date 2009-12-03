-- looks for and returns column names we need for page download feature

select 
* --control.name, test.name 
from 

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Template_Keys'
and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
'schooltype', 'charter', 'agencykey')
) control


full outer join

(SELECT col.Name
FROM sysobjects ob INNER Join syscolumns col  on ob.id = col.id
WHERE ob.type = 'V' AND ob.uid = 1 
AND ob.Name = 'v_Retention'
and col.Name in ('CESA', 'District Number', 'School Number', 'District Name', 'School Name', 'YearFormatted', 'StudentGroupLabel', 'SexLabel', 'RaceLabel', 'enrollment',
'schooltype', 'charter', 'agencykey')
) test


on 
control.[YearFormatted] = test.[YearFormatted] and 
control.[agencykey]  = test.[agencykey] and
control.[CESA] = test.[CESA] and 
control.[schooltype] = test.[schooltype] and 
control.[District Number] = test.[District Number] and 
control.[School Number] = test.[School Number] and 
control.[charter] = test.[charter] and 
control.[District Name] = test.[District Name] and 
control.[School Name] = test.[School Name] and 
control.[RaceLabel] = test.[RaceLabel] and 
control.[SexLabel] = test.[SexLabel] and 
control.[StudentGroupLabel] = test.[StudentGroupLabel]
