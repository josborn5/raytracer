REM https://raytracing.github.io/books/RayTracingInOneWeekend.html

REM VS 2015:
REM call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

REM VS 2017:
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64


SET CODE_DIR=code
SET OUTPUT_DIR=bin

IF NOT EXIST %OUTPUT_DIR% mkdir %OUTPUT_DIR%

pushd %OUTPUT_DIR%

del *.pdb > NUL 2> NUL

cl -nologo -Zi -FC /EHsc ..\%CODE_DIR%\console.cpp /link user32.lib gdi32.lib -incremental:no -opt:ref

cl -nologo -Zi -FC /EHsc ..\%CODE_DIR%\unit_tests.cpp /link user32.lib gdi32.lib -incremental:no -opt:ref

cl -nologo -Zi -FC /EHsc ..\%CODE_DIR%\window.cpp /link user32.lib Gdi32.lib winmm.lib ..\lib\gentle_giant.lib -incremental:no -opt:ref

popd