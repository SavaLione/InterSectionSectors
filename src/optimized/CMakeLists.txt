project(${ISS_OPTIMIZED_NAME})

set(ISS_OPTIMIZED_HEADERS
	rand_sse.h
	ReadFile.h
	Sector.h)

set(ISS_OPTIMIZED_SOURCES
	InterSectionSectors.cpp
	rand_sse.cpp
	ReadFile.cpp
	Sector.cpp)

add_executable(${ISS_OPTIMIZED_NAME} ${ISS_OPTIMIZED_HEADERS} ${ISS_OPTIMIZED_SOURCES})