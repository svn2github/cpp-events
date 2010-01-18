cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_DIR}/bin/probes")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_DIR}/lib/probes")

set(SOURCES_ROOT_DIR "${BASE_DIR}/probes")

add_executable(CtorVtbl
	"${SOURCES_ROOT_DIR}/CtorVtbl/main.cpp"
)

add_executable(FunctionDeclarator
	"${SOURCES_ROOT_DIR}/FunctionDeclarator/main.cpp"
)

add_executable(PartialMemberTemplate
	"${SOURCES_ROOT_DIR}/PartialMemberTemplate/main.cpp"
)
