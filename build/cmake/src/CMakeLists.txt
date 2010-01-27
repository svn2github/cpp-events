cmake_minimum_required(VERSION 2.6)

if("${UNIX}")
	set(PLATFORM_DIR "POSIX")
	set(PLATFORM_LIBS "pthread")
elseif("${WIN32}")
	set(PLATFORM_DIR "WinApi")
	set(PLATFORM_LIBS "Kernel32.lib")
else()
	set(PLATFORM_DIR "")
	set(PLATFORM_LIBS "")
endif()

message(STATUS "UNIX=${UNIX}")
message(STATUS "WIN32=${WIN32}")
message(STATUS "PLATFORM_DIR=${PLATFORM_DIR}")
message(STATUS "PLATFORM_LIBS=${PLATFORM_LIBS}")

if("${PLATFORM_DIR}" STREQUAL "")
	set(PLATFORM_DIR_DEFINE "//#define PLATFORM_DIR ???")
else()
	set(PLATFORM_DIR_DEFINE "#define PLATFORM_DIR ${PLATFORM_DIR}")
endif()

message(STATUS "PLATFORM_DIR_DEFINE=${PLATFORM_DIR_DEFINE}")

set(SOURCES_ROOT_DIR "${BASE_DIR}/src")

configure_file("./Config.hpp.template" "${SOURCES_ROOT_DIR}/Cpp/Events/Config.hpp")

add_library(CppEvents
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionList.cpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Threading.cpp"
)

target_link_libraries(CppEvents "${PLATFORM_LIBS}")

find_program(MCS_EXECUTABLE "${BASE_DIR}/tools/mcs/bin/Release/mcs")

# for some unknown reason 'if(NOT "${MCS_EXECUTABLE}")' does not work
if("${MCS_EXECUTABLE}" STREQUAL "MCS_EXECUTABLE-NOTFOUND")
	find_program(MCS_EXECUTABLE "${BASE_DIR}/tools/mcs/bin/mcs")
endif()

if("${MCS_EXECUTABLE}" STREQUAL "MCS_EXECUTABLE-NOTFOUND")
	message(STATUS " * MCS not found - source generation is disabled")
	return()
endif()

message(STATUS " * MCS found - source generation is enabled")

set(MCS_FILES
	"${SOURCES_ROOT_DIR}/FastDelegate/FastDelegate.h"
	"${SOURCES_ROOT_DIR}/Cpp/Events/ArgList.hpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Connection.hpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionEx.hpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionScope.hpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Events.hpp"
)

foreach(f ${MCS_FILES})
	add_custom_command(
		OUTPUT "${f}"
		COMMAND "${MCS_EXECUTABLE}" -o "${f}" "${f}.mcs"
		DEPENDS "${f}.mcs"
	)
endforeach(f ${MCS_FILES})

add_custom_target(mcs_target DEPENDS ${MCS_FILES})

add_dependencies(CppEvents mcs_target)
