@REM
@cls
@echo off

echo ---------------------------------------------------------------------------
echo ----                    Deleted Previous Executable                     ---
del ..\bin\*exe
del ..\build\*.obj
del ..\build\*.pdb
del ..\build\*.ilk
echo ---------------------------------------------------------------------------

echo.
echo ---------------------------------------------------------------------------
echo ----                    Compiling External Files                        ---
cl /c /MDd /nologo /Zi /GR- /EHs ..\deps\ImGui\src\*.cpp -I ..\deps\ImGui\include -I ..\deps\SFML\include
cl /c /MDd /nologo /Zi /GR- /EHs ..\deps\TFD\tinyfiledialogs.c -I ..\deps\TFD
echo ---------------------------------------------------------------------------
echo.
echo ---------------------------------------------------------------------------
echo ----                       Compiling Project                           ----
cl /c /MDd /nologo /Zi /GR- /EHs ..\src\*.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\TFD -I ..\deps\ImGui\include -I ..\deps\SQL

echo ---------------------------------------------------------------------------
echo.
echo ---------------------------------------------------------------------------
echo ----                             LINKING                                ---
echo --------------------------------------------------------------------------- 
cl /MDd /nologo /Zi /GR- /EHs /Fe..\bin\output.exe .\*.obj ..\deps\SFML\lib\*.lib ..\deps\SQL\sqlite3.lib comdlg32.lib ole32.lib opengl32.lib user32.lib gdi32.lib shell32.lib Ws2_32.lib winmm.lib
echo.

echo ---------------------------------------------------------------------------
echo ----                             MOVING                                ---- 
echo ---------------------------------------------------------------------------
echo.
move *.obj .\build
move *.ilk .\build
move .\bin\*.ilk .\build
echo. 
echo ---------------------------------------------------------------------------
echo ----                            FINALIZED                              ----
echo ---------------------------------------------------------------------------
echo.  


