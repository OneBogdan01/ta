# Required system packages
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

# Header-only libraries
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
set_target_properties(glm PROPERTIES FOLDER "engine/external")

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
set_target_properties(stb_image PROPERTIES FOLDER "engine/external")

# SDL3
add_subdirectory(SDL)  
if (TARGET SDL3::SDL3)
    set(SDL3_TARGET SDL3::SDL3)
elseif (TARGET SDL3::SDL3-static)
    set(SDL3_TARGET SDL3::SDL3-static)
elseif (TARGET SDL3)
    set(SDL3_TARGET SDL3)
elseif (TARGET SDL3-static)
    set(SDL3_TARGET SDL3-static)
else()
    message(FATAL_ERROR "Could not find any SDL3 target.")
endif()



# fmt
add_subdirectory(fmt EXCLUDE_FROM_ALL)
target_link_libraries(tiny_ape_light_engine PRIVATE fmt::fmt)
set_target_properties(fmt PROPERTIES FOLDER "engine/external")

# glad
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set_target_properties(glad PROPERTIES FOLDER "engine/external")

# imgui
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
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL3::SDL3 OpenGL::GL)
set_target_properties(imgui PROPERTIES FOLDER "engine/external")
