cmake_minimum_required(VERSION 3.16)

# Set project version
project(Hammered Engine VERSION 1.0.0 LANGUAGES CXX)


# Add subdirectories for engine and external dependencies
add_subdirectory(code)
add_subdirectory(external)
set_target_properties(tiny_ape_light_engine PROPERTIES FOLDER "engine")
# Access to the includes of the libraries
target_link_libraries(tiny_ape_light_engine
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
