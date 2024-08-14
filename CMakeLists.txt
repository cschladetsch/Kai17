cmake_minimum_required(VERSION 3.14)  # Increased for FetchContent

project(PITokeniser VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library
add_library(pi_tokeniser 
    pi-tokeniser.cpp
)

# Include directories
target_include_directories(pi_tokeniser PUBLIC 
    ${PROJECT_SOURCE_DIR}
)

# Enable warnings
if(MSVC)
    target_compile_options(pi_tokeniser PRIVATE /W4)
else()
    target_compile_options(pi_tokeniser PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(Catch2)

# Add test executable
add_executable(pi_tokeniser_tests tests/pi_tokeniser_tests.cpp)
target_link_libraries(pi_tokeniser_tests PRIVATE pi_tokeniser Catch2::Catch2WithMain)

# Enable testing
enable_testing()
add_test(NAME pi-tokeniser-tests COMMAND pi-tokeniser-tests)
project(PITokeniser VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library
add_library(pi-tokeniser 
    pi-tokeniser.cpp
)

# Enable warnings
if(MSVC)
    target_compile_options(pi-tokeniser PRIVATE /W4)
else()
    target_compile_options(pi-tokeniser PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add tests (optional)
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
