cmake_minimum_required(VERSION 2.6)

include(CheckIncludeFileCXX)

CHECK_INCLUDE_FILE_CXX("gtest/gtest.h" HAVE_GTEST)

if("${HAVE_GTEST}")
	find_library(HAVE_GTEST gtest)
endif()

if(NOT "${HAVE_GTEST}")
	message(STATUS " * Google C++ Testing Framework not found - skipping UnitTests")
	return()
endif()

message(STATUS " * Google C++ Testing Framework found - building UnitTests")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/tests/unit")

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/unit")

add_executable(UnitTests
	"${SOURCES_ROOT_DIR}/main.cpp"
#	"${SOURCES_ROOT_DIR}/Test_IsPolymorphic/Tests.cpp"
	"${SOURCES_ROOT_DIR}/Test_EqualMemberAddress/File1.cpp"
	"${SOURCES_ROOT_DIR}/Test_EqualMemberAddress/File2.cpp"
	"${SOURCES_ROOT_DIR}/Test_EqualMemberAddress/TestClass.cpp"
	"${SOURCES_ROOT_DIR}/Test_EqualMemberAddress/TheTest.cpp"
	"${SOURCES_ROOT_DIR}/Test_ConnectDisconnect/Tests.cpp"
)

target_link_libraries(UnitTests CppEvents optimized gtest debug gtestd)

add_custom_target(RunUnitTests ALL UnitTests DEPENDS UnitTests)
