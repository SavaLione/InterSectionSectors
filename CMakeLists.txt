cmake_minimum_required (VERSION 2.6)

################################
# Variables
################################
set(ISS_OPTIMIZED 1 CACHE BOOL "Optimized")
set(ISS_ORIGINAL 1 CACHE BOOL "Original")

set(ISS_OPTIMIZED_NAME InterSectionSectors_Optimized)
set(ISS_ORIGINAL_NAME InterSectionSectors_Original)

################################
# 
################################

if(ISS_OPTIMIZED)
	add_subdirectory(src/optimized)
endif()

if(ISS_ORIGINAL_NAME)
	add_subdirectory(src/original)
endif()