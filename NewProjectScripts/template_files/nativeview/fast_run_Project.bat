@echo off
setlocal

set "projRoot=%~dp0"
set "projRoot=%projRoot:~0,-1%"
for %%I in ("%projRoot%") do set "projectName=%%~nI"
set "buildDir=%projRoot%\build"
if not exist "%buildDir%" (
  mkdir "%buildDir%"
  cmake -S "%projRoot%" -B "%buildDir%"
) else (
  cd /d "%buildDir%"
)

echo ==========================
echo Incremental build...
echo ==========================

cmake --build "%buildDir%" --config Debug
if errorlevel 1 exit /b 1

if exist "%buildDir%\Debug\%projectName%.exe" (
  "%buildDir%\Debug\%projectName%.exe"
) else if exist "%buildDir%\%projectName%.exe" (
  "%buildDir%\%projectName%.exe"
) else (
  echo Executable not found.
  exit /b 1
)

endlocal
