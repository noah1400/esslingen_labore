USE [SWB_DB2_Projekt]
GO
/****** Object:  StoredProcedure [dbo].[noscit00_addpart]    Script Date: 26.06.2023 18:24:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[noscit00_addpart] 
    -- Add the parameters for the stored procedure here
    @Name varchar(50),
    @Description varchar(100),
    @CategoryName varchar(50)
AS
BEGIN
    -- SET NOCOUNT ON added to prevent extra result sets from
    -- interfering with SELECT statements.
    SET NOCOUNT ON;

	-- Trim leading and trailing spaces from @Name parameter
	-- And replace spaces in between
    SET @Name = REPLACE(LTRIM(RTRIM(@Name)), ' ', '_');
	SET @CategoryName = REPLACE(LTRIM(RTRIM(@CategoryName)), ' ', '_');

    -- Step 1: Check if a part with the same name exists
    DECLARE @PartId bigint;
    SELECT @PartId = id
    FROM dbo.noscit00_parts
    WHERE name = @Name;

    IF @PartId IS NOT NULL
    BEGIN
        -- Step 1A: Insert a new entry into noscit00_partentries with the id of the existing part
        INSERT INTO dbo.noscit00_partentries (part_id)
        VALUES (@PartId);
    END
    ELSE
    BEGIN
        -- Step 2: Check if a category with the given name exists
        DECLARE @CategoryId bigint;

        SELECT @CategoryId = id
        FROM dbo.noscit00_categories
        WHERE name = @CategoryName;

        IF @CategoryId IS NULL
        BEGIN
            -- Step 2A: Create a new category with an empty description and store the new id
            INSERT INTO dbo.noscit00_categories (name, description)
            VALUES (@CategoryName, '');
            
            SET @CategoryId = SCOPE_IDENTITY(); -- Retrieve the last inserted category id
        END

        -- Step 3: Create a new entry in noscit00_parts with the given name, description, and category id
        INSERT INTO dbo.noscit00_parts (name, description, category_id, created_at, updated_at)
        VALUES (@Name, @Description, @CategoryId, GETDATE(), GETDATE());

        -- Step 4: Insert a new entry into noscit00_partentries with the id of the newly inserted part
        INSERT INTO dbo.noscit00_partentries (part_id)
        VALUES (SCOPE_IDENTITY());
    END
END
