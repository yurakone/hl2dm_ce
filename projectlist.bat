@echo off
cd /d "%~dp0"

echo Checking available projects...
devtools\bin\vpc.exe /hl2mp /tf /define:SOURCESDK /projects

echo.
echo Checking available groups...
devtools\bin\vpc.exe /hl2mp /tf /define:SOURCESDK /groups

pause