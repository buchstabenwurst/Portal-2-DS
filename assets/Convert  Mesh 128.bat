for %%i in (%*) do python "C:\Users\Joshua\dev\ds\tools\obj2dl\obj2dl.py" --input %%i --output "C:\Users\Joshua\dev\ds\Portal-DS\data\%%~ni.bin" --texture "128" "128"
pause