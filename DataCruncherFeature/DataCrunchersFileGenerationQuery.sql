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
'Filename' = 'testcsvs.csv'
from orders
