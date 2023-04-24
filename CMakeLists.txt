cmake_minimum_required(VERSION 3.16)

add_definitions(-std=c++2a)
project(AbstractLinearAlgebra)

set(MKLROOT ls /opt/intel/oneapi/mkl/latest/)
find_package(MKL CONFIG REQUIRED)
find_package(OpenMP)

set(CMAKE_C_COMPILER /opt/intel/oneapi/compiler/latest/linux/bin/icx)
set(CMAKE_CXX_COMPILER /opt/intel/oneapi/compiler/latest/linux/bin/icpx)



set(CMAKE_CXX_FLAGS "-O3 -g3")
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/example/test.cpp)
include_directories(include/)
include_directories(src/)
include_directories(lib/)
add_executable(testLinearAlgebra ${SRC})
set_target_properties(testLinearAlgebra PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/example/bin")
target_link_directories(testLinearAlgebra PUBLIC "${MKLROOT}/lib/intel64")
target_include_directories(testLinearAlgebra PUBLIC "-DMKL_ILP64 -m64 ${MKLROOT}/include/")

target_link_libraries(testLinearAlgebra PUBLIC OpenMP::OpenMP_CXX 
											-lmkl_intel_ilp64 -lmkl_gnu_thread -lmkl_core 
										    -lgomp -lpthread -lm -ldl
											)