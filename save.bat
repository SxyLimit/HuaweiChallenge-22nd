@echo off
setlocal enabledelayedexpansion

:: Define source file and target folder
set "sourceFile=main.cpp"
set "targetFolder=HuaweiChallenge\22"

:: Check if the target folder exists, create it if not
if not exist "%targetFolder%" (
	mkdir "%targetFolder%"
	echo Target folder "%targetFolder%" created.
)

:: Initialize counter
set "counter=0"

:: Check existing main_x.cpp files in the target folder to find the highest number
for %%f in ("%targetFolder%\main_*.cpp") do (
	set "filename=%%~nxf"
	for /f "tokens=2 delims=_" %%n in ("!filename!") do (
		set "num=%%n"
		set "num=!num:.cpp=!"
		if !num! gtr !counter! set "counter=!num!"
	)
)

:: Increment counter
set /a counter+=1

:: Copy file and rename
copy "%sourceFile%" "%targetFolder%\main_%counter%.cpp" >nul
echo File copied to "%targetFolder%\main_%counter%.cpp".

:: Use wmic to get standardized date and time
for /f "tokens=2 delims==" %%a in ('wmic os get localdatetime /value') do set "datetime=%%a"
set "year=!datetime:~0,4!"
set "month=!datetime:~4,2!"
set "day=!datetime:~6,2!"
set "hour=!datetime:~8,2!"
set "minute=!datetime:~10,2!"
set "second=!datetime:~12,2!"

:: Create comment content in English
set "comment=// Copied on: %year%/%month%/%day% %hour%:%minute%:%second%"

:: Add comment to the beginning of the file
(
	echo %comment%
	type "%targetFolder%\main_%counter%.cpp"
) > "%targetFolder%\main_%counter%_temp.cpp"

:: Check if an additional argument is provided
if not "%~1"=="" (
	set "extra_comment=// Extra comment: %~1"
	(
		echo %comment%
		echo !extra_comment!
		type "%targetFolder%\main_%counter%.cpp"
	) > "%targetFolder%\main_%counter%_temp.cpp"
)

:: Replace the original file with the new one
move /y "%targetFolder%\main_%counter%_temp.cpp" "%targetFolder%\main_%counter%.cpp" >nul
echo Comment added to the file.

endlocal