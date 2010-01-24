cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/tests/speed")

add_subdirectory(BoostSignalsSpeedTest)
add_subdirectory(CppEventsSpeedTest)
add_subdirectory(DotNetSpeedTest)
add_subdirectory(LibSigCppSpeedTest)
add_subdirectory(QtSpeedTest)
add_subdirectory(SigSlotSpeedTest)
 