#include "engine.hpp"

#include <SDL3/SDL_events.h>

#include <cassert>

#include "utility/console.hpp"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

using namespace tale;
using namespace tale::log;

Engine& Engine::Instance()
{
  static Engine engineInstance;
  return engineInstance;
}
void Engine::Init()
{
  // TODO get the graphics API from config file
  m_device = new Device(gfx::GRAPHICS_API::OPENGL);
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
    }

    m_device->Render();
  }
}
void Engine::Shutdown()
{
  delete m_device;
  Info("Engine is closed");
}
