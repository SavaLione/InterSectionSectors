cmake_minimum_required (VERSION 2.6)

################################
# Variables
################################
set(ISS_OPTIMIZED 1 CACHE BOOL "Optimized")
set(ISS_ORIGINAL 1 CACHE BOOL "Original")
set(ISS_ORIGINAL_TIME_TEST 1 CACHE BOOL "Original with time test")
set(ISS_ORIGINAL_WITHOUT_OUT 1 CACHE BOOL "Original without out")

set(ISS_OPTIMIZED_NAME InterSectionSectors_Optimized)
set(ISS_ORIGINAL_NAME InterSectionSectors_Original)
set(ISS_ORIGINAL_TIME_TEST_NAME InterSectionSectors_Original_With_Time_Test)
set(ISS_ORIGINAL_WITHOUT_OUT_NAME InterSectionSectors_Original_Without_out)

################################
# Build
################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -msse2 -fopenmp")

################################
# 
################################

if(ISS_OPTIMIZED)
	add_subdirectory(src/optimized)
endif()

if(ISS_ORIGINAL_NAME)
	add_subdirectory(src/original)
endif()

if(ISS_ORIGINAL_TIME_TEST)
	add_subdirectory(src/originaltimetest)
endif()

if(ISS_ORIGINAL_WITHOUT_OUT)
	add_subdirectory(src/optimizedwithoutout)
endif()