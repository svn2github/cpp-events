cmake_minimum_required(VERSION 2.6)

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/speed/CppEventsSpeedTest")

add_executable(CppEventsSpeedTest
	"${SOURCES_ROOT_DIR}/main.cpp"
)

target_link_libraries(CppEventsSpeedTest CppEvents)
