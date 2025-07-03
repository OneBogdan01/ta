#pragma once
#include "platform/device.hpp"
#include "utility/console.hpp"

#include <filesystem>
#include <SDL3/SDL_init.h>
namespace hm
{
namespace io
{

std::string GetPath(const char* path);
void SaveGraphicsAPIToConfig(const std::string& api);
void RestartApplication();
gfx::GRAPHICS_API LoadGraphicsAPIFromConfig();

constexpr std::string_view AssetPath {"assets/"};
} // namespace io
} // namespace tale
