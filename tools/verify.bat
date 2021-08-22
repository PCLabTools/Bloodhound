@echo off

set COM_PORT=3
set BOARD_TYPE=teensy:avr:teensy31
set COMPILER="C:\Program Files (x86)\Arduino\arduino.exe"

rem Get the MCU code project name
for %%a in ("%~dp0\..\.") do set "PROJECT_NAME=%%~nxa"

rem Get the MCU code source folder path
for /d %%k in (%0\..) do set SOURCE_FOLDER=%%~dpk

if not exist "%SOURCE_FOLDER%\build" mkdir "%SOURCE_FOLDER%\build"

echo Initiating Build for Verification for Project: %PROJECT_NAME%

%COMPILER% --verify --pref build.path=%SOURCE_FOLDER%\build --board %BOARD_TYPE% --port %COM_PORT% --verbose /%PROJECT_NAME%.ino

rem Documentation Arduino CLI: https://github.com/arduino/Arduino/blobl/master/build/shared/manpage.adoc 