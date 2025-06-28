#pragma once

#include <memory>
#include <glm/glm.hpp>
namespace tale
{

namespace gfx
{

enum class GRAPHICS_API
{
  OPENGL,
  VULKAN
};
struct IGraphicsBackend
{
  virtual ~IGraphicsBackend() = default;
  virtual void Init() = 0;
  virtual void InitImGui() = 0;
  virtual void Render() = 0;
  virtual void PreRender() = 0;
};
} // namespace gfx

class Device
{
 public:
  Device(gfx::GRAPHICS_API api);
  ~Device();
  void Render();
  void PreRender();

 private:
  friend class Engine;
  glm::uvec2 m_windowSize {};
  void InitImGui();

  gfx::GRAPHICS_API m_graphicsApi {gfx::GRAPHICS_API::OPENGL};

  std::unique_ptr<gfx::IGraphicsBackend> m_graphicsBackend {nullptr};
  bool m_shouldClose {false};
  bool m_shouldRender {false};
};
} // namespace tale
