cmake_minimum_required(VERSION 2.6)

project(probes)

set(PROBES_LIST
	"FunctionDeclarator"
	"IsPolymorphic"
	"PartialMemberTemplate"
	"VirtualMemFuncPtrTest"
	"VtblSwitching"
)

foreach(f ${PROBES_LIST})
	try_run(
		EXIT_CODE
		COMPILE_IS_OK
		"${CMAKE_CURRENT_BINARY_DIR}"
		"${CMAKE_CURRENT_SOURCE_DIR}/../../src/${f}.cpp"
		COMPILE_OUTPUT_VARIABLE COMPILE_RESULTS
		RUN_OUTPUT_VARIABLE RUN_RESULTS
	)
	
	if(NOT COMPILE_IS_OK)
		set(RESULT ${COMPILE_RESULTS})
		message(STATUS "${f} - COMPILATION ERROR")
	else()
		set(RESULT ${RUN_RESULTS})
		if(EXIT_CODE)
			message(STATUS "${f} - RUN-TIME ERROR: ${EXIT_CODE}")
		else()
			message(STATUS "${f} - SUCCESS")
		endif()
	endif()

	file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/../../results/${f}.txt" "${RESULT}")
endforeach()
