cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/examples")

set(SOURCES_ROOT_DIR "${BASE_DIR}/examples")

add_executable(EventsDemo
	"${SOURCES_ROOT_DIR}/EventsDemo/main.cpp"
	"${SOURCES_ROOT_DIR}/EventsDemo/Client.cpp"
	"${SOURCES_ROOT_DIR}/EventsDemo/Server.cpp"
)

target_link_libraries(EventsDemo CppEvents)
