@echo off
setlocal

set "projRoot=%~dp0"
set "projRoot=%projRoot:~0,-1%"
for %%I in ("%projRoot%") do set "projectName=%%~nI"
set "buildDir=%projRoot%\build"
if exist "%buildDir%" (
  rmdir /s /q "%buildDir%"
)
mkdir "%buildDir%"

cmake -S "%projRoot%" -B "%buildDir%" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
if errorlevel 1 exit /b 1

cmake --build "%buildDir%" --config Release
if errorlevel 1 exit /b 1

if exist "%buildDir%\Release\%projectName%.exe" (
  "%buildDir%\Release\%projectName%.exe"
) else if exist "%buildDir%\%projectName%.exe" (
  "%buildDir%\%projectName%.exe"
) else (
  echo Executable not found.
  exit /b 1
)

endlocal
