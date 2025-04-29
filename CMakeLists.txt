cmake_minimum_required (VERSION 3.8)

project ("tiny_ape_light")


find_package(Vulkan REQUIRED)

add_subdirectory(external)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory(src)


