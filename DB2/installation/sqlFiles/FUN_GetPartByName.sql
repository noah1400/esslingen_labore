-- ================================================
-- Template generated from Template Explorer using:
-- Create Procedure (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- This block of comments will not be included in
-- the definition of the procedure.
-- ================================================
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		noscit00
-- Create date: 25.06.2023
-- Description:	Returns part by name
-- =============================================
CREATE FUNCTION [db_owner].[noscit00_GetPartByName] 
(	
	-- Add the parameters for the function here
	@Name varchar(50)
)
RETURNS TABLE 
AS
RETURN 
(
	-- Add the SELECT statement with parameter references here
	SELECT p.id, p.name, p.description, c.name AS category, COUNT(pe.id) AS amount, p.created_at, p.updated_at
	FROM [SWB_DB2_Projekt].[dbo].[noscit00_parts] p
	JOIN [SWB_DB2_Projekt].[dbo].[noscit00_categories] c ON p.category_id = c.id
	LEFT JOIN [SWB_DB2_Projekt].[dbo].[noscit00_partentries] pe ON p.id = pe.part_id
	WHERE p.name = @Name
	GROUP BY p.id, p.name, p.description, c.name, p.created_at, p.updated_at
)
GO
