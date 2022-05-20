cmake_minimum_required(VERSION 3.10)

# set the project name
project(massive)

cmake_policy(SET CMP0076 NEW)

find_package(MPI REQUIRED)
find_package(HDF5 REQUIRED)
find_package(Boost REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# add the executable
add_executable(massive)

target_include_directories(massive PUBLIC ${MPI_INCLUDE_PATH})
target_include_directories(massive PUBLIC ${HDF5_INCLUDE_DIRS})

target_link_libraries(massive ${MPI_C_LIBRARIES})
target_link_libraries(massive ${HDF5_LIBRARIES})

message("MPI ${MPI_INCLUDE_PATH} | ${MPI_C_LIBRARIES}")
message("HDF5 ${HDF5_INCLUDE_DIRS} | ${HDF5_LIBRARIES}")

add_subdirectory(src)
