
file(GLOB TEST_SOURCE_FILES "source/*.cpp")

add_executable(Test ${TEST_SOURCE_FILES} ${SOURCE_FILES})

target_include_directories(Test PRIVATE ../include ../external/json/include)

target_link_libraries(Test PRIVATE gtest gtest_main)


