-- =============================================
-- Create view basic template
-- =============================================
IF EXISTS (SELECT TABLE_NAME 
	   FROM   INFORMATION_SCHEMA.VIEWS 
	   WHERE  TABLE_NAME = N'v_Questions')
    DROP VIEW v_Questions
GO

CREATE VIEW v_Questions
AS 

SELECT q.ID, q.[Disabled], q.Question, q.Display, s.SectionName, s.SectionQuestion, c.CategoryName, [PrimarySort] = s.sort, [SecondarySort] = c.sort, [TertiarySort] = q.sort
FROM 	glsQuestions 	q
INNER JOIN
	glsCategories	c	on q.CategoryKey = c.ID
INNER JOIN
	glsSections 	s	on c.SectionKey = s.ID


GO

