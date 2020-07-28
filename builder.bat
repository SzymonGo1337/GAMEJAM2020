@echo off

set PATH=%PATH%;../lib_win/
set APP_NAME=Game.exe
set BUILD_MODE=Debug

if "%2"=="-r" (
	set BUILD_MODE=Release
)

if "%1"=="build" ( call:build )
if "%1"=="run" ( call:run )
if "%1"=="br" ( 
	call:build
	call:run
)
if "%1"=="clean" ( call:clean )

exit /B

:build
	mkdir build
	cd build
	
	cmake -DCMAKE_BUILD_TYPE=%BUILD_MODE% .. -G "MinGW Makefiles"
	make -j4
	
	cd ..
goto:eof

:run
	cd bin
	%APP_NAME%
	cd ..
goto:eof

:clean
	cd build
	make clean
	cd ..
goto:eof
