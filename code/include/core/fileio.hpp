#pragma once
#include <filesystem>
namespace tale
{
namespace io
{

std::string GetPath(const char* path);

constexpr std::string_view AssetPath {"assets/"};
} // namespace io
} // namespace tale
