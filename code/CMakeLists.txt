# Collect all .cpp files in source/
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

# Filter out files in source/platform/
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*/platform/.*")

# Set filtered sources
set(ENGINE_SOURCES ${ALL_SOURCES})

# Collect all .hpp files in include/
file(GLOB_RECURSE ALL_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Filter out files in include/platform/
list(FILTER ALL_HEADERS EXCLUDE REGEX ".*/platform/.*")

# Set filtered headers
set(ENGINE_HEADERS ${ALL_HEADERS})

# Now add platform-specific source and headers based on backend choice

if(USE_OPENGL)
    file(GLOB_RECURSE OPENGL_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/source/platform/opengl/*.cpp
    )
    file(GLOB_RECURSE OPENGL_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/opengl/*.hpp
    )
    list(APPEND ENGINE_SOURCES ${OPENGL_SOURCES})
    list(APPEND ENGINE_HEADERS ${OPENGL_HEADERS})
endif()

if(USE_VULKAN)
    file(GLOB_RECURSE VULKAN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/source/platform/vulkan/*.cpp
    )
    file(GLOB_RECURSE VULKAN_HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform/vulkan/*.hpp
    )
    list(APPEND ENGINE_SOURCES ${VULKAN_SOURCES})
    list(APPEND ENGINE_HEADERS ${VULKAN_HEADERS})
endif()


add_library(hammered_engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)
target_include_directories(hammered_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include   
)
target_compile_features(hammered_engine PUBLIC cxx_std_20)

# Engine asset directory
set(ENGINE_ASSET_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../assets" PARENT_SCOPE)

# Graphics APIs
option(USE_OPENGL "Use OpenGL as the graphics API" ON)
option(USE_VULKAN "Use Vulkan as the graphics API" OFF)


if(USE_OPENGL)
    add_compile_definitions(GFX_USE_OPENGL)
endif()
if(USE_VULKAN)
    add_compile_definitions(GFX_USE_VULKAN)
endif()



# Proper folder layout in Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX "source" FILES ${ENGINE_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "include" FILES ${ENGINE_HEADERS})
