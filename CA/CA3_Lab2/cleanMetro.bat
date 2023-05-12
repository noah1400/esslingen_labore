@for /d %%f in (*) do @call deleteData.bat %%f 
@del /s /q *.bak


