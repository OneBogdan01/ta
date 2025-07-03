cmake_minimum_required(VERSION 3.16)

# Set project version
project(hammered_engine VERSION 1.0.0 LANGUAGES CXX)


# Add subdirectories for engine and external dependencies
add_subdirectory(code)
add_subdirectory(external)
set_target_properties(hammered_engine PROPERTIES FOLDER "engine")
# Access to the includes of the libraries
target_link_libraries(hammered_engine
    PUBLIC
        vma
        vkbootstrap
        fmt::fmt
        glm
        stb_image
        glad
        imgui
)

# Enable multi-threaded compilation for MSVC
if(MSVC)
    add_compile_options(/MP)
endif()
