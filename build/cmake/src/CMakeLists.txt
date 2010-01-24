cmake_minimum_required(VERSION 2.6)

set(SOURCES_ROOT_DIR "${BASE_DIR}/src")

add_library(CppEvents
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionList.cpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Threading.cpp"
)

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
