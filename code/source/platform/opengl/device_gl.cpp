

#include <glad/glad.h>

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>

#include "platform/device.hpp"
#include "utility/console.hpp"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>
using namespace tale;

void Device::InitImGUI()
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
  ImGui_ImplSDL3_InitForOpenGL(m_window, m_glContext);
  ImGui_ImplOpenGL3_Init();
}
Device::Device(GRAPHICS_API api) : m_graphicsApi(api)
{
  // TODO call platform dependent code for now it is opengl
  auto appName {"Tiny Ape Light Engine"};
  SDL_InitFlags flags {SDL_INIT_VIDEO};
  SDL_SetAppMetadata("Tiny Ape Light Engine", "0", "tale");
  if (SDL_Init(flags) == false)
  {
    log::Error("SDL could not be initialized");
    return;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  m_window =
      SDL_CreateWindow(appName, 800, 600, SDL_INIT_VIDEO | SDL_WINDOW_OPENGL);
  if (m_window == nullptr)
  {
    log::Error("SDL could not create window {}", SDL_GetError());
    return;
  }

  m_glContext = SDL_GL_CreateContext(m_window);
  if (m_glContext == nullptr)
  {
    log::Error("SDL could not create a OpenGL context {}", SDL_GetError());
    return;
  }
  if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) ==
      false)
  {
    log::Error("Failed to initialize GLAD");
    return;
  }
  log::Info("OpenGL Version: {}",
            reinterpret_cast<const char*>(glGetString(GL_VERSION)));

  InitImGUI();
}
Device::~Device()
{
  SDL_GL_DestroyContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
void Device::Render()
{
  // now you can make GL calls.
  glClearColor(1, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(m_window);
}
