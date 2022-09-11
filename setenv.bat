
pushd "C:\Program Files (x86)\Microsoft Visual Studio" 
::\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
for /f "delims=" %%a in ( 'dir /s vcvars64.bat /b' ) do call "%%a"
popd