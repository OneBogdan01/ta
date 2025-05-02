add_library(tiny_ape_light_engine STATIC
    source/engine.cpp
    include/engine.hpp
)

target_include_directories(tiny_ape_light_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(tiny_ape_light_engine PUBLIC cxx_std_20)
