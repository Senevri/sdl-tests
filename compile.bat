REM I usually have posix tools in path.
:: set oldpath=%PATH%
:: set PATH=%PATH%;"c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"
for /f "delims=" %%a in ( 'dir ext\SDL* /b' ) do set sdl=%%a
for /f "delims=" %%a in ( 'cd' ) do set pwd=%%a
set outdir=bin
cl /EHsc /MD  ^
src\main.cpp /Fe%outdir%\test.exe ^
/I %pwd%\ext\%sdl%\include /link ^
/LIBPATH:%pwd%\ext\%sdl%\lib\x64 ^
shell32.lib SDL2.lib SDL2main.lib ^
/SUBSYSTEM:CONSOLE

::cp -n "%pwd%\ext\%sdl%\lib\x64\SDL2.dll" %outdir%\
echo n |copy /-y "%pwd%\ext\%sdl%\lib\x64\*.dll" %outdir%\


:: set PATH=%oldpath%