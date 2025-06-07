cmake_minimum_required(VERSION 3.10)
project(Scheduling)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "source/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(Scheduling ${SOURCE_FILES})

target_include_directories(Scheduling PRIVATE external/json/include)
target_include_directories(Scheduling PRIVATE include)
