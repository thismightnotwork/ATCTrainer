cmake_minimum_required(VERSION 3.16)
project(ATCTrainer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Add ECFMP SDK (Git submodule)
add_subdirectory(third_party/ecfmp/src)

# Plugin
add_library(ATCTrainerPlugin SHARED
    plugin/EuroScopePlugIn.h
    plugin/ATCTrainerPlugin.h
    plugin/ATCTrainerPlugin.cpp
)
target_include_directories(ATCTrainerPlugin PRIVATE third_party/ecfmp/include)
target_link_libraries(ATCTrainerPlugin ecfmp-sdk)

# Test Harness
add_executable(TestHarness test/TestHarness.cpp)
target_link_libraries(TestHarness ATCTrainerPlugin)

# Output structure
set_target_properties(ATCTrainerPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
set_target_properties(TestHarness PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
