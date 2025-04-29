#include "engine.hpp"

#include <cassert>
#include <iostream>
tale::Engine tale::Engine::m_engineInstance;
void tale::WriteLine(const char *text) { std::cout << text << '\n'; }
tale::Engine::Engine() {
  assert(m_instantiated == false);
  m_instantiated = true;
}
tale::Engine &tale::Engine::Instance() { return m_engineInstance; }
void tale::Engine::Init() {
  WriteLine("Engine is initialized");

}
void tale::Engine::Run() {
  WriteLine("Engine is running");

}
void tale::Engine::Quit()
{
  WriteLine("Engine is closed");
}
