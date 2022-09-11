::set sdl_lib_zip=https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-2.24.0-win32-x64.zip
set sdl_devel_vc=https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-devel-2.24.0-VC.zip
wget -nc %sdl_devel_vc%
::wget -nc %sdl_lib_zip%

::for /f "tokens=1" %%a in ( 'dir *win32* /b' ) do 7z x -olib %%a 
for /f "tokens=1" %%a in ( 'dir *devel* /b' ) do 7z x -oext %%a 