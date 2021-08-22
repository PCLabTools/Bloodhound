@echo off

rem Get the MCU code source folder path
for /d %%k in (%0) do set SOURCE_FOLDER=%%~dpk

echo Starting serial port monitor...

start "Serial Monitor" /separate "%SOURCE_FOLDER%termite-3.4\bin\Termite.exe"