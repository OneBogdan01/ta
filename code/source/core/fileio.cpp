#include "core/fileio.hpp"
namespace tale::io
{
std::string GetPath(const char* path)
{
  return std::string(tale::io::AssetPath) + path;
}
}

