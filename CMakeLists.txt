cmake_minimum_required(VERSION 3.16)

add_definitions(-std=c++2a)
project(AbstractLinearAlgebra)


set(CMAKE_CXX_FLAGS "-O3 -g3")

set(SRC test.cpp)

add_executable(testLinearAlgebra ${SRC})
set_target_properties(testLinearAlgebra PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")


target_link_libraries(testLinearAlgebra PUBLIC -lm -ldl)

