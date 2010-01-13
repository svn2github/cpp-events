cmake_minimum_required(VERSION 2.6)

set(BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

set(MCS_EXECUTABLE, "${BASE_DIR}/tools/mcs/bin/release/mcs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_DIR}/lib")
set(SOURCES_ROOT_DIR "${BASE_DIR}/src")

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

add_library(CppEvents1
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionList.cpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Threading.cpp"
)

add_dependencies(CppEvents1 mcs_target)
