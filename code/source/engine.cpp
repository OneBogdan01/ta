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
  // get the graphics API from config file
  m_device = new Device(GRAPHICS_API::OPENGL);
  Info("Engine is initialized");
}
void Engine::Run()
{
  while (m_device->m_shouldClose == false)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL3_ProcessEvent(&event); // Forward your event to backend
      if (event.type == SDL_EVENT_QUIT)
      {
        m_device->m_shouldClose = true;
      }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)


    m_device->Render();
  }
}
void Engine::Quit()
{
  delete m_device;
  Info("Engine is closed");
}
