#pragma once
namespace tale
{

class Engine
{
 public:
  static Engine &Instance();
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
  void Quit();

 private:
};
} // namespace tale
