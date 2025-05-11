#include "engine.hpp"

#include <cassert>

#include "utility/console.hpp"

using namespace tale;
using namespace tale::log;

Engine& Engine::Instance()
{
  static Engine engineInstance;
  return engineInstance;
}
void Engine::Init()
{
  Info("Engine is initialized");
}
void Engine::Run()
{
  Info("Engine is running");
}
void Engine::Quit()
{
  Info("Engine is closed");
}
