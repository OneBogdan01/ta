#pragma once
#include <cstdint>
#include <string>

#include "platform/opengl/opengl.hpp"
namespace tale
{

struct ShaderPaths
{
  std::string Vertex {};
  std::string Fragment {};

  std::string GetPath() const;
};
class Shader
{
 public:
  Shader(const ShaderPaths& shader);

  ~Shader();
  std::string LoadShader(const std::string& path);
  bool CompileShader(GLuint& shaderId, GLenum shaderType, const GLchar* source);
  bool LinkProgram();
  bool LoadSource(const ShaderPaths& sourcePath);
  bool Load();
  void Reload();
  void Activate() const;

 private:
  uint32_t m_programId {};
  std::string m_resourcePath {};
  ShaderPaths m_shaderPaths {};
};
} // namespace tale
