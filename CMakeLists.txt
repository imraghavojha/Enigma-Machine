cmake_minimum_required(VERSION 3.14)
project(EnigmaMachine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build your main executable
add_executable(enigma 
    main.cpp 
    rotor.cpp 
    plugboard.cpp 
    enigma_machine.cpp
    enigma_display.cpp)

# Enable testing
enable_testing()

# Add GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test subdirectory
add_subdirectory(tests)