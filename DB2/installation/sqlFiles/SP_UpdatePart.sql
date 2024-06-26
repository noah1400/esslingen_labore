USE [SWB_DB2_Projekt]
GO
/****** Object:  StoredProcedure [dbo].[noscit00_UpdatePart]    Script Date: 26.06.2023 18:26:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[noscit00_UpdatePart] 
    -- Add the parameters for the stored procedure here
    @Name varchar(50) = NULL, 
    @Description varchar(100) = NULL,
    @Category varchar(50),
    @Id bigint
AS
BEGIN
    -- SET NOCOUNT ON added to prevent extra result sets from
    -- interfering with SELECT statements.
    SET NOCOUNT ON;

    IF @Category <> ''
    BEGIN
        DECLARE @CategoryId bigint;

		SET @Category = REPLACE(RTRIM(LTRIM(@Name)), ' ', '_');

        -- Check if a category with the name @Category exists in dbo.noscit00_categories
        SELECT @CategoryId = id
        FROM dbo.noscit00_categories
        WHERE name = @Category;

        IF @CategoryId IS NULL
        BEGIN

            -- Create a new category entry in dbo.noscit00_categories
            INSERT INTO dbo.noscit00_categories (name, description)
            VALUES (@Category, '');

            SET @CategoryId = SCOPE_IDENTITY(); -- Retrieve the newly generated category id
        END

		SET @Name = REPLACE(RTRIM(LTRIM(@Name)), ' ', '_');

        -- Update the entry in dbo.noscit00_parts with @Id, setting name = @Name, description = @Description, and category_id = @CategoryId
        UPDATE dbo.noscit00_parts
        SET name = @Name, description = @Description, category_id = @CategoryId
        WHERE id = @Id;
    END
    ELSE
    BEGIN

		SET @Name = REPLACE(RTRIM(LTRIM(@Name)), ' ', '_');

        -- Update the entry in dbo.noscit00_parts with @Id, setting name = @Name and description = @Description, without changing the category
        UPDATE dbo.noscit00_parts
        SET name = @Name, description = @Description
        WHERE id = @Id;
    END

    -- Optionally, you can add a SELECT statement here to return the updated row or any other desired output.
    SELECT * FROM dbo.noscit00_parts WHERE id = @Id;
END
