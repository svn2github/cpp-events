cmake_minimum_required(VERSION 2.6)

include(CheckIncludeFileCXX)

CHECK_INCLUDE_FILE_CXX("boost/signals.hpp" HAVE_BOOST_SIGNALS)

if("${HAVE_BOOST_SIGNALS}")
	CHECK_INCLUDE_FILE_CXX("boost/bind.hpp" HAVE_BOOST_SIGNALS)
endif()

if(NOT "${HAVE_BOOST_SIGNALS}")
	message(STATUS " * Boost.Signals not found - skipping BoostSignalsSpeedTest")
	return()
endif()

message(STATUS " * Boost.Signals found - building BoostSignalsSpeedTest")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/tests/speed")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_DIR}/lib/tests/speed")

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/speed/BoostSignalsSpeedTest")

add_executable(BoostSignalsSpeedTest
	"${SOURCES_ROOT_DIR}/main.cpp"
)
