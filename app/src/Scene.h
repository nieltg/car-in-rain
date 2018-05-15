#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/gl/gl.h>
#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Program.h>
#include <globjects/VertexArray.h>
#include <globjects/Texture.h>
#include <globjects/VertexAttributeBinding.h>
#include <globjects/Buffer.h>
#include <globjects/Shader.h>


class Scene {
public:
  int width = 0;
  int height = 0;

  Scene (void);

  void resize (int _w, int _h);
  void draw (void);

private:
  std::unique_ptr<globjects::Program> g_program;
  std::unique_ptr<globjects::File> g_vertexShaderSource;
  std::unique_ptr<globjects::AbstractStringSource> g_vertexShaderTemplate;
  std::unique_ptr<globjects::Shader> g_vertexShader;
  std::unique_ptr<globjects::File> g_fragmentShaderSource;
  std::unique_ptr<globjects::AbstractStringSource> g_fragmentShaderTemplate;
  std::unique_ptr<globjects::Shader> g_fragmentShader;

  std::unique_ptr<globjects::VertexArray> m_vao;
  std::unique_ptr<globjects::Buffer> m_vertices;
  std::unique_ptr<globjects::Buffer> m_texcoord;
  std::unique_ptr<globjects::Buffer> m_indices;

  std::unique_ptr<globjects::Texture> m_texture;

  gl::GLint attr_coord3d;
  gl::GLint attr_texcoord;
  gl::GLint uniform_mvp;
  gl::GLint uniform_tex;

  size_t indices_len;
};
