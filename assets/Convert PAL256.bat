for %%i in (%*) do python "D:\devkitPro\nitro-engine\tools\img2ds\img2ds.py" --input %%i --name %%~ni --output "D:\dev\DS\Portal\data" --format "PAL256"
pause