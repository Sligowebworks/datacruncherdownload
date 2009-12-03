select 
'Query' = 
'"' + isnull(cast(OrderID as varchar),'') + '",' + 
'"' + isnull(cast(CustomerID as varchar),'') + '",' + 
'"' + isnull(cast(EmployeeID as varchar),'') + '",' + 
'"' + isnull(cast(OrderDate as varchar),'') + '",' + 
'"' + isnull(cast(RequiredDate as varchar),'') + '",' + 
'"' + isnull(cast(ShippedDate as varchar),'') + '",' + 
'"' + isnull(cast(ShipVia as varchar),'') + '",' + 
'"' + isnull(cast(Freight as varchar),'') + '",' + 
'"' + isnull(cast(ShipName as varchar),'') + '",' + 
'"' + isnull(cast(ShipAddress as varchar),'') + '",' + 
'"' + isnull(cast(ShipCity as varchar),'') + '",' + 
'"' + isnull(cast(ShipRegion as varchar),'') + '",' + 
'"' + isnull(cast(ShipPostalCode as varchar),'') + '",' + 
'"' + isnull(cast(ShipCountry as varchar),'') + '",' + char(13) + char(10) , 
'Filename' = 'testcsv.csv'
from orders

union

select 

--'cast(rtrim([' + syscolumns.name + ']) as nchar) as [' + syscolumns.name + '],'
'Query' = 
'"OrderID","CustomerID","EmployeeID","OrderDate","RequiredDate","ShippedDate","ShipVia","Freight","ShipName","ShipAddress","ShipCity","ShipRegion","ShipPostalCode","ShipCountry"',
'Filename' = 'testcsv.csv'

from sysobjects 
inner join syscolumns on sysobjects.id = syscolumns.id
where sysobjects.name like 'orders'


