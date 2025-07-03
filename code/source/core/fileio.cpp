#include "core/fileio.hpp"

#include <fstream>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_filesystem.h>
namespace hm::io
{
std::string GetPath(const char* path)
{
  return std::string(AssetPath) + path;
}
void SaveGraphicsAPIToConfig(const std::string& api)
{
  const std::string configPath = io::GetPath("") + "config.ini";

  std::ofstream out(configPath);

  out << "graphics_api=" << api << "\n";
  out.close();

  log::Info("Saved graphics API to config: {}", api);
}
void RestartApplication()
{
  const char* base_path = SDL_GetBasePath();
  if (!base_path)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get base path");
    return;
  }

  // Set your executable name here manually:
#ifdef _WIN32
  const char* exe_name = "game.exe"; // Change this to your actual exe name
#elif defined(__APPLE__)
  const char* exe_name = "game"; // macOS executable name
#else
  const char* exe_name = "game"; // Linux executable name
#endif

  // Construct full path to executable
  std::string exe_path = std::string(base_path) + exe_name;

  char cmd[4096];

#ifdef _WIN32
  // On Windows, use start with delay (timeout) and quotes properly escaped
  snprintf(cmd, sizeof(cmd), "cmd /C \"timeout 1 && start \"\" \"%s\"\"",
           exe_path.c_str());
#elif defined(__APPLE__)
  // macOS uses open, with sleep delay
  snprintf(cmd, sizeof(cmd), "sleep 1 && open \"%s\"", exe_path.c_str());
#else
  // Linux/Unix with sleep and direct execution
  snprintf(cmd, sizeof(cmd), "sleep 1 && \"%s\" &", exe_path.c_str());
#endif

  SDL_Log("Restarting application with command: %s", cmd);

  system(cmd);

  SDL_Quit();
  exit(0);
}
gfx::GRAPHICS_API LoadGraphicsAPIFromConfig()
{
  const std::string configPath = io::GetPath("") + "config.ini";

  std::ifstream in(configPath);
  if (!in)
  {
    return gfx::GRAPHICS_API::OPENGL; // fallback
  }

  std::string line;
  gfx::GRAPHICS_API result = gfx::GRAPHICS_API::OPENGL; // default

  while (std::getline(in, line))
  {
    if (line.find("graphics_api=") == 0)
    {
      std::string value = line.substr(strlen("graphics_api="));
      if (value == "VULKAN")
        result = gfx::GRAPHICS_API::VULKAN;
      else
        result = gfx::GRAPHICS_API::OPENGL;
      break;
    }
  }

  in.close();

  return result;
}
} // namespace tale::io
