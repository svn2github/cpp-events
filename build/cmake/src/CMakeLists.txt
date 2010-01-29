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

if(NOT PLATFORM_DIR)
	set(PLATFORM_DIR_DEFINE "//#define PLATFORM_DIR ???")
else()
	set(PLATFORM_DIR_DEFINE "#define PLATFORM_DIR ${PLATFORM_DIR}")
endif()

set(SOURCES_ROOT_DIR "${BASE_DIR}/src")

configure_file("./Config.hpp.template" "${SOURCES_ROOT_DIR}/Cpp/Events/Config.hpp")

add_library(CppEvents
	"${SOURCES_ROOT_DIR}/Cpp/Events/ConnectionList.cpp"
	"${SOURCES_ROOT_DIR}/Cpp/Events/Threading.cpp"
)

target_link_libraries(CppEvents "${PLATFORM_LIBS}")

find_program(MCS_EXECUTABLE "${BASE_DIR}/tools/mcs/bin/Release/mcs")

# for some unknown reason 'if(NOT "${MCS_EXECUTABLE}")' does not work
if(NOT MCS_EXECUTABLE)
	find_program(MCS_EXECUTABLE "${BASE_DIR}/tools/mcs/bin/mcs")
endif()

if(NOT MCS_EXECUTABLE)
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
	"${SOURCES_ROOT_DIR}/Cpp/Events/Event.hpp"
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
