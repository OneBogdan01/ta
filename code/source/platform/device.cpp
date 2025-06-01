#include "platform/device.hpp"

#include "platform/opengl/device_gl.hpp"
#include "platform/vulkan/device_vk.hpp"

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>
#include "utility/console.hpp"

#include <imgui.h>

using namespace tale;

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
Device::Device(gfx::GRAPHICS_API api) : m_graphicsApi(api)
{
  // const char* appName {"Tiny Ape Light Engine"};
  SDL_InitFlags flags {SDL_INIT_VIDEO};
  SDL_SetAppMetadata("Tiny Ape Light Engine", "0", "tale");
  if (SDL_Init(flags) == false)
  {
    log::Error("SDL could not be initialized");
    return;
  }
  switch (api)
  {
    case gfx::GRAPHICS_API::OPENGL:
      m_graphicsBackend = std::make_unique<OpenGLBackend>();
      break;
    case gfx::GRAPHICS_API::VULKAN:
      m_graphicsBackend = std::make_unique<VulkanBackend>();

      break;
  }

  m_graphicsBackend->Init();
  InitImGui();
}
Device::~Device() {}
void Device::Render()
{
  m_graphicsBackend->Render();
}
