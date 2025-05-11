# Automatically collect all .cpp files in source/
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

# Automatically collect all .hpp files in include/
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(tiny_ape_light_engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)
target_include_directories(tiny_ape_light_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include   
)
target_compile_features(tiny_ape_light_engine PUBLIC cxx_std_20)

# Proper folder layout in Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX "source" FILES ${ENGINE_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "include" FILES ${ENGINE_HEADERS})