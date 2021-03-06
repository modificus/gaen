:: Run this first on a clean system to prepare Gaen build.

@ECHO OFF
SETLOCAL

:: Change to root dir
CD /d %~dp0

:: Write root directory to main GAEN_ROOT env var
FOR /f "tokens=1" %%B in ('CHDIR') do set GAEN_ROOT=%%B

if "%1"=="" (
    SET PLAT=win64
)
if "%1"=="win64" (
    SET PLAT=win64
)
if "%1"=="win32" (
    SET PLAT=win32
)
if "%PLAT%"=="" (
    echo Invalid platform type "%1", must be win32 or win64
    exit /b 1
)

set BUILD_DIR=%GAEN_ROOT%\build\%PLAT%

if not exist "%BUILD_DIR%" (
   mkdir "%BUILD_DIR%"
)

cd %BUILD_DIR%

if "%PLAT%"=="win64" (
    cmake -G "Visual Studio 14 Win64" %GAEN_ROOT%
)
if "%PLAT%"=="win32" (
    cmake -G "Visual Studio 14" %GAEN_ROOT%
)


:: Build scripts for the first time to ensure codegen happens
:: before VS is loaded. Otherwise the first build in VS will
:: not compile the scripts (it will generate them though)
if not exist "%BUILD_DIR%\src\scripts\registration.cpp" (
  call "%VS140COMNTOOLS%\vsvars32.bat"
  if %errorlevel% neq 0 exit /b %errorlevel%
  msbuild "%BUILD_DIR%\src\scripts\scripts.vcxproj"
  if %errorlevel% neq 0 exit /b %errorlevel%
)
