cmake_minimum_required(VERSION 2.6)

find_package(Qt4 QUIET COMPONENTS QtCore)

if(NOT "${Qt4_FOUND}")
	message(STATUS " * Qt4 not found - skipping QtSpeedTest")
	return()
endif()

message(STATUS " * Qt4 found - building QtSpeedTest")

include(${QT_USE_FILE})

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/speed/QtSpeedTest")

QT4_WRAP_CPP(QtSpeedTest_MOC_SRCS "${SOURCES_ROOT_DIR}/Objects.hpp")

add_executable(QtSpeedTest
	"${SOURCES_ROOT_DIR}/main.cpp"
	"${QtSpeedTest_MOC_SRCS}"
)

target_link_libraries(QtSpeedTest ${QT_LIBRARIES})
