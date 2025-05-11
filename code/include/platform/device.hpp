#pragma once
#include <SDL3/SDL_video.h>
#include <glm/glm.hpp>
namespace tale
{
enum class GRAPHICS_API
{
  OPENGL,
  VULKAN
};
class Device
{
 public:
  Device(GRAPHICS_API api);
  ~Device();
  void Render();

 private:
  friend class Engine;
  glm::uvec2 m_windowSize {};
  void InitImGUI();

  GRAPHICS_API m_graphicsApi {GRAPHICS_API::OPENGL};
  SDL_Window* m_window {nullptr};
  bool m_shouldClose {false};
  SDL_GLContext m_glContext;
};
} // namespace tale
