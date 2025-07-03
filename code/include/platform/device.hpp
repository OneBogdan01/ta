#pragma once

#include <memory>
#include <glm/glm.hpp>
namespace hm
{

namespace gfx
{

enum class GRAPHICS_API
{
  OPENGL,
  VULKAN
};

} // namespace gfx

class Device
{
 public:
  Device();
  ~Device();
  void Render();
  void ChangeGraphicsBackend();
  void PreRender();
  void Initialize();
  void DestroyBackend();

  void SetViewportSize(const glm::uvec2& windowSize,
                       const glm::ivec2& windowPosition);

 private:
  friend class Engine;
  glm::uvec2 m_windowSize {};
  void InitImGui();

  bool m_shouldClose {false};
  bool m_shouldRender {false};

  gfx::GRAPHICS_API m_graphicsApi {gfx::GRAPHICS_API::OPENGL};
};
} // namespace hm
