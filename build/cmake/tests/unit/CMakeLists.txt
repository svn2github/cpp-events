cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/tests")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_DIR}/lib/tests")

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/unit")

add_executable(UnitTests
	"${SOURCES_ROOT_DIR}/main.cpp"
)
