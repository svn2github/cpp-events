cmake_minimum_required(VERSION 2.6)

include(CheckIncludeFileCXX)

CHECK_INCLUDE_FILE_CXX("sigc++/sigc++.h" HAVE_LIBSIGCPP)

if("${HAVE_LIBSIGCPP}")
	find_library(HAVE_LIBSIGCPP sigc)
endif()

if(NOT "${HAVE_LIBSIGCPP}")
	message(STATUS " * LibSigC++ not found - skipping LibSigCppSpeedTest")
	return()
endif()

message(STATUS " * LibSigC++ found - building LibSigCppSpeedTest")

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/speed/LibSigCppSpeedTest")

add_executable(LibSigCppSpeedTest
	"${SOURCES_ROOT_DIR}/main.cpp"
)

target_link_libraries(LibSigCppSpeedTest optimized sigc-vc80-2_0 debug sigc-vc80-d-2_0)