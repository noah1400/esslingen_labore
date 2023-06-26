-- ================================================
-- Template generated from Template Explorer using:
-- Create Trigger (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- See additional Create Trigger templates for more
-- examples of different Trigger statements.
--
-- This block of comments will not be included in
-- the definition of the function.
-- ================================================
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		noscit00
-- Create date: 25.06.2023
-- Description:	Update update_at
-- =============================================
CREATE TRIGGER dbo.noscit00_updatedAt
   ON dbo.noscit00_parts
   AFTER INSERT, UPDATE
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for trigger here
	UPDATE dbo.noscit00_parts
	SET updated_at = GETDATE()
	FROM dbo.noscit00_parts
	JOIN inserted ON dbo.noscit00_parts.id = inserted.id;

END
GO