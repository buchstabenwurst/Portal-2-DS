for %%i in (%*) do python "C:\dev\ds\tools\img2ds\img2ds.py" --input %%i --name %%~ni --output "C:\dev\ds\Portal-DS\data" --format "PAL16"
pause