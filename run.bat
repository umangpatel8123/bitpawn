@echo off
echo Building the project...
cmake -S . -B build
cmake --build build

echo.
echo Running the application...
build\bitpawn.exe

pause
