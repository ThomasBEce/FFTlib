include_directories(${CMAKE_SOURCE_DIR}/src)

set(SRC main.cpp)
add_executable(main ${SRC})
target_link_libraries(main FFTlib)
