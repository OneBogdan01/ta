#include "platform/opengl/shader_gl.hpp"

#include "utility/console.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <SDL3/SDL_assert.h>
std::string hm::ShaderPaths::GetPath() const
{
  return Vertex + " " + Fragment;
}
hm::Shader::Shader(const ShaderPaths& shader) : m_shaderPaths(shader)
{
  Reload();
  m_resourcePath = m_shaderPaths.GetPath();
}
hm::Shader::~Shader()
{
  glDeleteProgram(m_programId);
}

std::string hm::Shader::LoadShader(const std::string& path)
{
  std::ifstream shaderFile {path};

  return {std::istreambuf_iterator(shaderFile),
          std::istreambuf_iterator<char>()};
}

bool hm::Shader::CompileShader(GLuint& shaderId, GLenum shaderType,
                               const GLchar* source)
{
  if (source == nullptr)
  {
    log::Error("Empty shader");
    return false;
  }
  shaderId = glCreateShader(shaderType);

  glShaderSource(shaderId, 1, &source, nullptr);

  glCompileShader(shaderId);
  GLint compiled {};
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE)
  {
#ifdef DEBUG

    GLint logLength {};
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    auto* log = new GLchar[logLength + 1];
    glGetShaderInfoLog(shaderId, logLength, &logLength, log);
    log::Error("Shader compilation failed: {}", log);
    delete[] log;

#endif
    glDeleteShader(shaderId);
    return false;
  }
  return true;
}
bool hm::Shader::LinkProgram()
{
  glLinkProgram(m_programId);
  GLint linked;
  glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
  if (linked == GL_FALSE)
  {
#ifdef DEBUG
    GLsizei len;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &len);

    GLchar* log = new GLchar[len + 1];
    glGetProgramInfoLog(m_programId, len, &len, log);
    log::Error("Shader linking failed: {}", log);
    delete[] log;
#endif

    return false;
  }

  return true;
}

void DeleteShader(GLuint& id)
{
  if (id)
  {
    glDeleteShader(id);
    id = 0;
  }
}
bool hm::Shader::LoadSource(const ShaderPaths& sourcePath)
{
  // compile shaders
  GLuint vertexId {};
  if (m_shaderPaths.Vertex.empty() == false)
  {
    const auto success {
        CompileShader(vertexId, GL_VERTEX_SHADER, sourcePath.Vertex.c_str())};

    if (success == false)
    {
      log::Error("Failed to compile vertex shader {}",
                 m_shaderPaths.Vertex.c_str());
      return false;
    }
  }
  GLuint fragmentId {};
  if (m_shaderPaths.Fragment.empty() == false)
  {
    const auto success {CompileShader(fragmentId, GL_FRAGMENT_SHADER,
                                      sourcePath.Fragment.c_str())};

    if (success == false)
    {
      log::Error("Failed to compile fragment shader {}",
                 m_shaderPaths.Fragment.c_str());
      return false;
    }
  }
  // attach shaders
  m_programId = glCreateProgram();

  if (vertexId)
  {
    glAttachShader(m_programId, vertexId);
  }
  if (fragmentId)
  {
    glAttachShader(m_programId, fragmentId);
  }

  // link shaders
  if (LinkProgram() == false)
  {
    DeleteShader(vertexId);
    DeleteShader(fragmentId);
    log::Error("Shader Linking failed");
    return false;
  }
  DeleteShader(vertexId);
  DeleteShader(fragmentId);
  return true;
}
bool hm::Shader::Load()
{
  static ShaderPaths sourcePaths;
  if (m_shaderPaths.Vertex.empty() == false)
  {
    sourcePaths.Vertex = LoadShader(m_shaderPaths.Vertex);
  }
  if (m_shaderPaths.Fragment.empty() == false)
  {
    sourcePaths.Fragment = LoadShader(m_shaderPaths.Fragment);
  }

  return LoadSource(sourcePaths);
}
void hm::Shader::Reload()
{
  if (m_programId > 0)
  {
    glDeleteProgram(m_programId);
    m_programId = 0;
  }

  bool success = Load();

  if (!success)
  {
    SDL_assert(success);
  }

  if (!success)
  {
    log::Error("Unable to load shader {}", m_resourcePath);
  }
}
void hm::Shader::Activate() const
{
  glUseProgram(m_programId);
}
