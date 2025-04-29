cmake_minimum_required(VERSION 3.12.0)

# Use solution folders to organize projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Version information
set(TALE_VERSION_MAJOR 1)
set(TALE_VERSION_MINOR 0)
set(TALE_VERSION_PATCH 0)
set(TALE_VERSION_TWEAK 0)

set(TALE_VERSION
    ${TALE_VERSION_MAJOR}.${TALE_VERSION_MINOR}.${TALE_VERSION_PATCH}.${TALE_VERSION_TWEAK}
)

project( tiny_ape_light_engine VERSION ${TALE_VERSION} LANGUAGES CXX )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Output directory for static lib (.LIB)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for shared lib (.DLL)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for executables (.EXE)

add_subdirectory(engine)
add_subdirectory(external)

# Enable multithreaded builds
if( MSVC )
    add_compile_options(/MP)
endif()



