@cd %1
@echo %1
@del /s *.o
@del /s *.tdt
@if exist bin     rd /s /q bin
@if exist %1_Data rd /s /q %1_Data 
@cd ..

