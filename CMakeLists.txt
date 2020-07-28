cmake_minimum_required(VERSION 3.1)

project(Game)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

SET(CMAKE_CXX_FLAGS "-std=c++17 -no-pie -g -Wall -Ddebug")

IF(${CMAKE_BUILD_TYPE} MATCHES Release)
	SET(CMAKE_CXX_FLAGS "-std=c++17 -s -O3 -no-pie -Wall")	
ENDIF()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

file(GLOB_RECURSE SRC src/*)

add_executable(
	Game
	${SRC}
)
	
include_directories(include)

IF(WIN32)
	link_directories(lib/win)
ELSE()
	link_directories(lib/linux)
ENDIF()
	
set_target_properties(Game PROPERTIES OUTPUT_NAME "Game")
target_link_libraries(
	Game
	sfml-system
	sfml-graphics
	sfml-window
	sfml-audio
)
