# Create test executable with just the plugboard tests
add_executable(plugboard_test 
    plugboard_test.cpp
    ${CMAKE_SOURCE_DIR}/plugboard.cpp)

# Link with GoogleTest
target_link_libraries(plugboard_test PRIVATE gtest gtest_main)

# Include the parent directory so we can find the headers
target_include_directories(plugboard_test PRIVATE ${CMAKE_SOURCE_DIR})