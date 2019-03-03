cmake_minimum_required (VERSION 2.6)

################################
# Variables
################################
set(ISS_OPTIMIZED 1 CACHE BOOL "Optimized")
set(ISS_ORIGINAL 1 CACHE BOOL "Original")

set(ISS_OPTIMIZED_NAME InterSectionSectors_Optimized)
set(ISS_ORIGINAL_NAME InterSectionSectors_Original)

################################
# Build
################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -fopenmp")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -fopenmp"")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -fopenmp"")

################################
# 
################################

if(ISS_OPTIMIZED)
	add_subdirectory(src/optimized)
endif()

if(ISS_ORIGINAL_NAME)
	add_subdirectory(src/original)
endif()