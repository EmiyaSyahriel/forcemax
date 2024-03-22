cmake_minimum_required(VERSION 3.8)

project(forcemax)
add_executable(forcemax src/forcemax.c res/forcemax.rc)
target_link_libraries(forcemax PRIVATE user32)

if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND NOT (CMAKE_BUILD_TYPE MATCHES "Deb"))
	target_compile_options(forcemax PUBLIC -Os -s)

	# Maximum level of binary stripping 
	add_custom_command(TARGET forcemax POST_BUILD COMMAND ${CMAKE_STRIP} -s forcemax.exe)
endif()