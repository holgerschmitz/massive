cmake_minimum_required(VERSION 3.10)

# set the project name
project(massive)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
add_executable(massive1x1v
    src/massive.cpp
    src/species/species.cpp
    huerto/constants.cpp
)

add_executable(massive2x3v
    src/massive.cpp
    src/species/species.cpp
    huerto/constants.cpp
)

target_compile_definitions(massive1x1v PRIVATE MASSIVE_1X_1V MASSIVE_ONE_V HUERTO_ONE_DIM)
target_compile_definitions(massive2x3v PRIVATE MASSIVE_2X_3V MASSIVE_THREE_V HUERTO_TWO_DIM)

function(setoptions target)
    target_include_directories(${target} PUBLIC ${MPI_INCLUDE_PATH})
    target_include_directories(${target} PUBLIC ${HDF5_INCLUDE_DIRS})

    target_link_libraries(${target} ${MPI_C_LIBRARIES})
    target_link_libraries(${target} ${HDF5_LIBRARIES})
    target_link_libraries(${target} /usr/local/lib/libschnek.so)
endfunction()

setoptions(massive1x1v)
setoptions(massive2x3v)

message("MPI ${MPI_INCLUDE_PATH} | ${MPI_C_LIBRARIES}")
message("HDF5 ${HDF5_INCLUDE_DIRS} | ${HDF5_LIBRARIES}")
