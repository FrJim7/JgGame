@REM
@cls
@echo off

echo ---------------------------------------------------------------------------
echo ----                    Deleted Previous Executable                    ----
del ..\bin\*.exe
del .\*.o
echo ---------------------------------------------------------------------------
echo.
echo ---------------------------------------------------------------------------
echo ----                    Compiling External Files                       ----
clang++ -c -g ..\deps\ImGui\src\*.cpp -I ..\deps\ImGui\include -I ..\deps\SFML\include
@REM This file uses unsafe options as strcpy, strcat, etc. Clang give you a warning for each one, so I decided to block them.
clang -c -Wno-everything -g ..\deps\TFD\tinyfiledialogs.c -I ..\deps\TFD
echo ---------------------------------------------------------------------------
echo.
echo ---------------------------------------------------------------------------
echo ----                       Compiling Project                           ----
clang++ -c -g ..\src\*.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\TFD -I ..\deps\ImGui\include -I ..\deps\SQL

echo ---------------------------------------------------------------------------
echo.
echo ---------------------------------------------------------------------------
echo ----                             LINKING                               ----
echo --------------------------------------------------------------------------- 
clang++ -std=c++11 -g -o ..\bin\output.exe .\*.o ..\deps\SFML\lib\*.lib ..\deps\SQL\sqlite3.lib -lcomdlg32 -lole32 -lopengl32 -luser32 -lgdi32 -lshell32 -lWs2_32 -lwinmm
echo.

echo ---------------------------------------------------------------------------
echo ----                             MOVING                                ---- 
echo ---------------------------------------------------------------------------
echo.
echo. 
echo ---------------------------------------------------------------------------
echo ----                            FINALIZED                              ----
echo ---------------------------------------------------------------------------
echo. 