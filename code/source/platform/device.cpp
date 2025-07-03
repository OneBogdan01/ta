#include "platform/device.hpp"

#include "core/fileio.hpp"
#include "platform/opengl/device_gl.hpp"
#include "platform/vulkan/device_vk.hpp"

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>
#include "utility/console.hpp"

#include <imgui.h>

using namespace hm;

void Device::InitImGui()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch

  // Setup Platform/Renderer backends
  m_graphicsBackend->InitImGui();
}
Device::Device() : m_graphicsApi(io::LoadGraphicsAPIFromConfig())
{
  // const char* appName {"Tiny Ape Light Engine"};
  SDL_InitFlags flags {SDL_INIT_VIDEO};
  SDL_SetAppMetadata("Hammered Engine", "0", "HammE");
  if (SDL_Init(flags) == false)
  {
    log::Error("SDL could not be initialized");
    return;
  }

  m_graphicsBackend->Init();
  InitImGui();
}
Device::~Device() {}
void Device::Render()
{

}
void Device::ChangeGraphicsBackend()
{
  ImGui::Begin("Graphics Settings");

  static const char* apiOptions[] = {"OpenGL", "Vulkan"};
  static int selectedApiIndex =
      (m_graphicsApi == gfx::GRAPHICS_API::OPENGL) ? 0 : 1;

  if (ImGui::Combo("Graphics API", &selectedApiIndex, apiOptions,
                   IM_ARRAYSIZE(apiOptions)))
  {
    gfx::GRAPHICS_API chosen = (selectedApiIndex == 0)
                                   ? gfx::GRAPHICS_API::OPENGL
                                   : gfx::GRAPHICS_API::VULKAN;

    if (chosen != m_graphicsApi)
    {
      io::SaveGraphicsAPIToConfig(
          (chosen == gfx::GRAPHICS_API::OPENGL) ? "OPENGL" : "VULKAN");

      // gracefully shut down the engine
      io::RestartApplication();
    }
  }

  ImGui::End();
}
void Device::PreRender()
{
  m_graphicsBackend->PreRender();
  ChangeGraphicsBackend();
}
