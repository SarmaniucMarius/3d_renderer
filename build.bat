@echo off

rem todo: remove -wd2401
set compiler_flags=-nologo -Zi -GR- -Od -Oi -WX -W4 -FC -wd4201 -wd4100 -wd4189
set linker_flags=SDL2.lib SDL2main.lib

pushd ..\build

cl %compiler_flags% ..\code\main.cpp %linker_flags%

popd