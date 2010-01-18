cmake_minimum_required(VERSION 2.6)

set(MCS_EXECUTABLE, "${BASE_DIR}/tools/mcs/bin/release/mcs")

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

add_library(CppEvents
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionList.cpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Threading.cpp"
)

add_dependencies(CppEvents mcs_target)
