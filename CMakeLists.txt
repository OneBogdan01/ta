cmake_minimum_required(VERSION 3.16)

# Set project version
project(tiny_ape_light_engine VERSION 1.0.0 LANGUAGES CXX)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for engine and external dependencies
add_subdirectory(code)
add_subdirectory(external)

# Enable multi-threaded compilation for MSVC
if(MSVC)
    add_compile_options(/MP)
endif()
