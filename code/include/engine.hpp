#pragma once
#include "platform/device.hpp"
namespace tale
{

class Engine
{
 public:
  static Engine& Instance();
  /// <summary>
  /// Initializes core modules
  /// </summary>
  void Init();
  /// <summary>
  /// Starts the update loop
  /// </summary>
  void Run();
  /// <summary>
  /// Cleans up resources and close window
  /// </summary>
  void Shutdown();

  Device& GetDevice() const { return *m_device; }

 private:
  Device* m_device {nullptr};
  gfx::GRAPHICS_API m_selectedApi {};
};
} // namespace tale
