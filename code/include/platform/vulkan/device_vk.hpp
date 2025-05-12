#pragma once
#include "platform/device.hpp"

namespace tale
{
struct VulkanBackend : gfx::IGraphicsBackend
{
  void Init() override;
  void InitImGui() override;
  void Render() override;
  void PreRender() override;
};
} // namespace tale
