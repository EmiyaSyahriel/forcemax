cmake_minimum_required(VERSION 3.8)

project(forcemax)
add_executable(forcemax src/forcemax.c res/forcemax.rc)
target_link_libraries(forcemax PRIVATE user32)