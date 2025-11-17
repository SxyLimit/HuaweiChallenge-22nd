@echo off
setlocal

:: 检查是否有参数传入
if "%~1"=="" (
	echo Please provide the suffix for the file.
	exit /b
)

:: 设置文件夹A的路径，可以根据需要修改
set "folderA=HuaweiChallenge\22"

:: 构造源文件路径
set "sourceFile=%folderA%\main_%1.cpp"

:: 检查源文件是否存在
if not exist "%sourceFile%" (
	echo Source file %sourceFile% does not exist.
	exit /b
)

:: 构造目标文件路径
set "targetFile=main.cpp"

:: 检查目标文件是否存在，如果不存在则提示
if not exist "%targetFile%" (
	echo Target file %targetFile% does not exist. Creating new file.
)

:: 覆盖目标文件
copy /Y "%sourceFile%" "%targetFile%">nul
if %errorlevel%==0 (
	echo File %sourceFile% has been copied to %targetFile%.
) else (
	echo Failed to copy file.
)

endlocal