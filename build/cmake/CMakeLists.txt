cmake_minimum_required(VERSION 2.6)

project(CppEvents)

set(BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_DIR}/lib")

include_directories("${BASE_DIR}/src")
link_directories("${BASE_DIR}/lib")
 
add_subdirectory(src)
add_subdirectory(tests)
