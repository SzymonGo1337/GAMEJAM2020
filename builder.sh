#!/bin/bash
export LD_LIBRARY_PATH=../lib/linux/

APP_NAME=Game

function build () {
	BUILD_MODE="Debug"

	if [ "$1" == '-r' ] || [ "$1" == "--release" ]
	then
		BUILD_MODE="Release"
	fi

	mkdir -p build && cd $_
	cmake -DCMAKE_BUILD_TYPE="$BUILD_MODE" ..
	exitCode=$?
	if [ "$exitCode" == "0" ]
	then
		make -j$(nproc)
		exitCode=$?
	fi
	cd ..
	exit $exitCode
}

function run {
	cd bin/
	./"$APP_NAME"
}

function clean {
	cd build
	make clean
}

case "$1" in
	"build") build "$2" ;;
	"run") run ;;
	"br") build "$2" && run ;;
	"clean") clean ;;
	*) echo "Available params: build, run, br, clean"
esac
