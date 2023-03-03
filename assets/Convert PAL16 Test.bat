for %%i in (%*) do python "D:\dev\DS\Portal\assets\img2ds.py" --input %%i --palinput %%i --name %%~ni --output "D:\dev\DS\Portal\data" --format "PAL16"
pause