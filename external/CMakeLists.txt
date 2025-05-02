# Vulkan is a required dependency
find_package(Vulkan REQUIRED)
# OpenGL is a required dependency
find_package(OpenGL REQUIRED)
# GLM is a header-only library
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)

# stb_image is also header-only
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)

# SDL has its own CMakeLists.txt files
add_subdirectory(SDL)

# ImGui is a static library
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_vulkan.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_sdl3.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL3::SDL3 OpenGL::GL)
