cmake_minimum_required(VERSION 3.1)

project(Game)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Debug build compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17 -no-pie -g -Wall -Ddebug")
# Release build compiler flags
set(RELEASE_BUILD_FLAGS "-std=c++17 -s -O3 -no-pie -Wall")

# For release build...
if(${CMAKE_BUILD_TYPE} MATCHES Release)
	if(WIN32)
		string(APPEND RELEASE_BUILD_FLAGS " -mwindows")
	endif()

	set(CMAKE_CXX_FLAGS ${RELEASE_BUILD_FLAGS})
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

file(GLOB_RECURSE SRC src/*)

add_executable(
	Game
	${SRC}
)
	
include_directories(include)

IF(WIN32)
	link_directories(lib/win)
	set(GL_DEP "opengl32")
ELSE()
	link_directories(lib/linux)
	set(GL_DEP "GL")
ENDIF()
	
set_target_properties(Game PROPERTIES OUTPUT_NAME "Game")
target_link_libraries(
	Game
	sfml-system
	sfml-graphics
	sfml-window
	sfml-audio
	${GL_DEP}
)
