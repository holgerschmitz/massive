cmake_minimum_required(VERSION 3.10)

# set the project name
project(massive)

cmake_policy(SET CMP0076 NEW)

find_package(MPI REQUIRED)
find_package(HDF5 REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})
include_directories(SYSTEM ${HDF5_INCLUDE_DIRS})

# add the executable
add_executable(massive)

target_link_libraries(massive ${MPI_C_LIBRARIES})
target_link_libraries(massive ${HDF5_LIBRARIES})

message("MPI ${MPI_INCLUDE_PATH} | ${MPI_C_LIBRARIES}")
message("HDF5 ${HDF5_INCLUDE_DIRS} | ${HDF5_LIBRARIES}")

add_subdirectory(src)
