@echo off
setlocal

REM Get project root directory (same as dirname "$0")
set "projRootDir=%~dp0"
set "projRootDir=%projRootDir:~0,-1%"

REM Create / clean build directory (like mkdir || rm -rf build/*)
if exist "%projRootDir%\build" (
    rmdir /s /q "%projRootDir%\build"
)

mkdir "%projRootDir%\build"
cd /d "%projRootDir%\build"

REM ls equivalent
dir

REM Configure project
cmake -DCMAKE_POLICY_VERSION_MINIMUM="3.5" ..

if errorlevel 1 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build project (like make)
cmake --build .

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

REM Run executable (like ./glRendering)
"%projRootDir%\build\Debug\glRendering.exe"

echo Done.
pause

endlocal