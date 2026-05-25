@echo off
setlocal

set "projRootDir=%~dp0"
set "projRootDir=%projRootDir:~0,-1%"

set "buildDir=%projRootDir%\build"
set "exePath=%buildDir%\Debug\glRendering.exe"

REM Create build dir only once
if not exist "%buildDir%" (
    mkdir "%buildDir%"
    cd /d "%buildDir%"
    cmake ..
) else (
    cd /d "%buildDir%"
)

echo ==========================
echo Building (incremental)...
echo ==========================

cmake --build . --config Debug

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo ==========================
echo Running...
echo ==========================

"%exePath%"

endlocal