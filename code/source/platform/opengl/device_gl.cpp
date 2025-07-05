#include "core/device.hpp"

#include "platform/opengl/device_gl.hpp"

#include "core/fileio.hpp"
#include "platform/opengl/opengl_gl.hpp"
#include "platform/opengl/shader_gl.hpp"

#include "utility/console.hpp"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>
#include <glm/gtc/type_ptr.hpp>
namespace hm::internal
{
SDL_GLContext glContext {nullptr};
SDL_Window* window {nullptr};
} // namespace hm::internal

using namespace hm;
using namespace hm::internal;

Device::~Device()
{
  DestroyBackend();
}

void Device::Initialize()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window = SDL_CreateWindow(WindowTitle, m_windowSize.x, m_windowSize.y,
                            SDL_INIT_VIDEO | SDL_WINDOW_OPENGL);
  if (window == nullptr)
  {
    log::Error("SDL could not create window {}", SDL_GetError());
    return;
  }

  glContext = SDL_GL_CreateContext(window);
  if (glContext == nullptr)
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

#ifdef DEBUG

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Optional: to ensure callback is
                                         // called immediately
  glDebugMessageCallback(MessageCallback, nullptr);
  // Enable everything except notifications
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

  log::Info("OpenGL debug output enabled.");

#endif
  InitImGui();
}

void Device::DestroyBackend()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
void Device::SetViewportSize(const glm::uvec2& windowSize,
                             const glm::ivec2& windowPosition)
{
  glViewport(windowPosition.x, windowPosition.y, windowSize.x, windowSize.y);
}
void Device::PreRender()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
  ChangeGraphicsBackend();
}
void Device::Render()
{
  ImGui::ShowDemoWindow(); // Show demo window! :)

  // now you can make GL calls.
  glClearColor(1, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  static Shader triangle({io::GetPath("shaders/colored_triangle.vert"),
                          io::GetPath("shaders/colored_triangle.frag")});
  triangle.Activate();

  static bool once {true};
  // Memory leak
  static GLuint vao {};
  static glm::mat4 camMatrix {glm::mat4(1.0f)};

  if (once)
  {
    camMatrix = glm::scale(camMatrix, {1.0f, -1.f, 1.0f});

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // upload matrix
    once = false;
  }
  static GLint loc = glGetUniformLocation(triangle.m_programId, "uViewProj");

  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(camMatrix));

  // Draw 3 vertices to form your triangle
  glDrawArrays(GL_TRIANGLES, 0, 3);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(window);
}

void Device::InitPlatformImGui()
{
  ImGui_ImplSDL3_InitForOpenGL(window, glContext);
  ImGui_ImplOpenGL3_Init();
}

SDL_GLContextState* device::GetGlContext()
{
  return glContext;
}

SDL_Window* device::GetWindow()
{
  return window;
}
