#pragma once
#include "platform/device.hpp"

#include <SDL3/SDL_video.h>
namespace tale
{
struct OpenGLBackend : gfx::IGraphicsBackend
{
  ~OpenGLBackend() override;
  void DestroyBackend();
  void SetViewportSize(const glm::uvec2& windowSize,
                       const glm::ivec2& windowPosition);
  void PreRender() override;

  void Render() override;

  void Init() override;
  void InitImGui() override;

  SDL_GLContext GlContext {nullptr};
  SDL_Window* Window {nullptr};

}; // namespace gl
} // namespace tale
