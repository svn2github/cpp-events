cmake_minimum_required(VERSION 2.6)

message(STATUS " * SigSlot found - building SigSlotSpeedTest")

set(SOURCES_ROOT_DIR "${BASE_DIR}/tests/speed/SigSlotSpeedTest")

add_executable(SigSlotSpeedTest
	"${SOURCES_ROOT_DIR}/main.cpp"
	"${SOURCES_ROOT_DIR}/run_test_mtg.cpp"
	"${SOURCES_ROOT_DIR}/run_test_mtl.cpp"
	"${SOURCES_ROOT_DIR}/run_test_st.cpp"
)
