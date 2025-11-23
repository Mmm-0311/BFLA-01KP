@echo off
REM BFLA-01KP Compilation Script for Windows
REM Compiles the BFLA_01KP.cpp source code

echo Compiling BFLA_01KP...

REM Compile with optimization
g++ -O2 -o BFLA_01KP.exe ..\src\BFLA_01KP.cpp -lm

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo Compilation successful! Executable: BFLA_01KP.exe
    echo Run with: BFLA_01KP.exe
) else (
    echo Compilation failed!
    exit /b 1
)

