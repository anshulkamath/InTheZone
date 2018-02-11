for /f "tokens=1-4 delims=/ " %%i in ("%date%") do (
     set dow=%%i
     set month=%%j
     set day=%%k
     set year=%%l
)
set datestr=%month%_%day%_%year%
cd C:\Users\Robot\Z Code\InTheZone
git add -A
git commit -m %datestr%
git push https://github.com/anshulkamath/InTheZone master


pause