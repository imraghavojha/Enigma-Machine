# Create a library with your source code
add_library(enigma_lib STATIC
    ${CMAKE_SOURCE_DIR}/rotor.cpp
    ${CMAKE_SOURCE_DIR}/plugboard.cpp
    ${CMAKE_SOURCE_DIR}/enigma_machine.cpp)

# Set include directories for the library
target_include_directories(enigma_lib PUBLIC ${CMAKE_SOURCE_DIR})

# Create test executable for all tests
add_executable(all_tests
    plugboard_test.cpp
    rotor_test.cpp
    enigma_machine_test.cpp)

# Link against your code and GoogleTest
target_link_libraries(all_tests PRIVATE enigma_lib gtest gtest_main)

# You can also create individual test executables if you prefer
add_executable(plugboard_test plugboard_test.cpp)
target_link_libraries(plugboard_test PRIVATE enigma_lib gtest gtest_main)

add_executable(rotor_test rotor_test.cpp)
target_link_libraries(rotor_test PRIVATE enigma_lib gtest gtest_main)

add_executable(enigma_machine_test enigma_machine_test.cpp)
target_link_libraries(enigma_machine_test PRIVATE enigma_lib gtest gtest_main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(all_tests)
gtest_discover_tests(plugboard_test)
gtest_discover_tests(rotor_test)
gtest_discover_tests(enigma_machine_test)