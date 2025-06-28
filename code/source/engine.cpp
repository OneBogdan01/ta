#include "engine.hpp"

#include "core/fileio.hpp"

#include <SDL3/SDL_events.h>

#include <cassert>

#include "utility/console.hpp"

#include <fstream>
#include <thread>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_init.h>

using namespace tale;
using namespace tale::log;

Engine& Engine::Instance()
{
  static Engine engineInstance;
  return engineInstance;
}
void SaveGraphicsAPIToConfig(const std::string& api)
{
  const std::string configPath = io::GetPath("") + "config.ini";

  std::ofstream out(configPath);

  out << "graphics_api=" << api << "\n";
  out.close();

  log::Info("Saved graphics API to config: {}", api);
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
void Engine::Init()
{
  m_selectedApi = LoadGraphicsAPIFromConfig();
  m_device = new Device(m_selectedApi);
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

void Engine::Run()
{
  while (m_device->m_shouldClose == false)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL3_ProcessEvent(&event); // Forward your event to backend
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
      {
        m_device->m_shouldClose = true;
      }
      if (event.type == SDL_EVENT_WINDOW_MINIMIZED)
      {
        m_device->m_shouldRender = true;
      }
      if (event.type == SDL_EVENT_WINDOW_RESTORED)
      {
        m_device->m_shouldRender = false;
      }
    }
    // do not draw if we are minimized
    if (m_device->m_shouldRender)
    {
      // throttle the speed to avoid the endless spinning
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }
    m_device->PreRender();

    ImGui::Begin("Graphics Settings");

    static const char* apiOptions[] = {"OpenGL", "Vulkan"};
    static int selectedApiIndex =
        (m_selectedApi == gfx::GRAPHICS_API::OPENGL) ? 0 : 1;

    if (ImGui::Combo("Graphics API", &selectedApiIndex, apiOptions,
                     IM_ARRAYSIZE(apiOptions)))
    {
      gfx::GRAPHICS_API chosen = (selectedApiIndex == 0)
                                     ? gfx::GRAPHICS_API::OPENGL
                                     : gfx::GRAPHICS_API::VULKAN;

      if (chosen != m_selectedApi)
      {
        SaveGraphicsAPIToConfig(
            (chosen == gfx::GRAPHICS_API::OPENGL) ? "OPENGL" : "VULKAN");

        // gracefully shut down the engine
        RestartApplication();
      }
    }

    ImGui::End();
    m_device->Render();
  }
}
void Engine::Shutdown()
{
  delete m_device;
  Info("Engine is closed");
}
