for %%i in (%*) do python "C:\dev\ds\tools\obj2dl\obj2dl.py" --input %%i --output "C:\dev\ds\Portal-DS\data\%%~ni.bin" --texture "128" "128"
pause