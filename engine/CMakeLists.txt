add_library(tiny_ape_light_engine STATIC
    src/engine.cpp
    inc/engine.hpp
)

target_include_directories(tiny_ape_light_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
set_property(TARGET tiny_ape_light_engine PROPERTY CXX_STANDARD 20)
target_compile_features(tiny_ape_light_engine PUBLIC cxx_std_20)
