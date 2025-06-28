#include "platform/opengl/device_gl.hpp"

#include "core/fileio.hpp"
#include "platform/opengl/opengl.hpp"
#include "rendering/shader.hpp"

#include <SDL3/SDL_init.h>

#include <SDL3/SDL_video.h>

#include "utility/console.hpp"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

using namespace tale;

void OpenGLBackend::Init()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  Window =
      SDL_CreateWindow("Tale", 800, 600, SDL_INIT_VIDEO | SDL_WINDOW_OPENGL);
  if (Window == nullptr)
  {
    log::Error("SDL could not create window {}", SDL_GetError());
    return;
  }

  GlContext = SDL_GL_CreateContext(Window);
  if (GlContext == nullptr)
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
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                        GL_TRUE); // Enable all messages
  log::Info("OpenGL debug output enabled.");
#endif
}
OpenGLBackend::~OpenGLBackend()
{
  DestroyBackend();
}
void OpenGLBackend::DestroyBackend()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  SDL_GL_DestroyContext(GlContext);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}
void OpenGLBackend::SetViewportSize(const glm::uvec2& windowSize,
                                    const glm::ivec2& windowPosition)
{
  glViewport(windowPosition.x, windowPosition.y, windowSize.x, windowSize.y);
}
void OpenGLBackend::PreRender()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}
void OpenGLBackend::Render()
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
  static GLuint vao;
  if (once)
  {
    glGenVertexArrays(1, &vao);
  }
  glBindVertexArray(vao);

  // Draw 3 vertices to form your triangle
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Unbind VAO and program if needed
  glBindVertexArray(0);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(Window);
}
void OpenGLBackend::InitImGui()
{
  ImGui_ImplSDL3_InitForOpenGL(Window, GlContext);
  ImGui_ImplOpenGL3_Init();
}
