select 

--'cast(rtrim([' + syscolumns.name + ']) as nchar) as [' + syscolumns.name + '],'
'''"''' + ' + isnull(cast(' + rtrim(syscolumns.name) + ' as varchar),'''') + ' + '''",''' + ' + '

from sysobjects 
inner join syscolumns on sysobjects.id = syscolumns.id
where sysobjects.name like 'orders'
order by syscolumns.colid

