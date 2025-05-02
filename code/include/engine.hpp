#pragma once
namespace tale {

  class Engine{
  public:
    Engine();
    static Engine &Instance();
    void Init();
    void Run();
    void Quit();
  private:
    static Engine m_engineInstance;
    inline static  bool m_instantiated{false};
  };
  void WriteLine(const char* text);
}