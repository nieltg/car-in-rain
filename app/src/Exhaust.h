#pragma once

#include <memory>

#include <glbinding/gl/gl.h>

#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>
#include <globjects/VertexArray.h>


class Exhaust {
public:
  const int N_PARTICLE = 10000;

  Exhaust (void);

  void draw (glm::mat4 _v, glm::mat4 _p);

private:
  std::unique_ptr<globjects::Program> program;
  std::unique_ptr<globjects::File> shader_v_src;
  std::unique_ptr<globjects::AbstractStringSource> shader_v_preprocessed;
  std::unique_ptr<globjects::Shader> shader_v;
  std::unique_ptr<globjects::File> shader_f_src;
  std::unique_ptr<globjects::AbstractStringSource> shader_f_preprocessed;
  std::unique_ptr<globjects::Shader> shader_f;

  std::unique_ptr<globjects::Texture> texture;

  gl::GLint i_attr_coord3d;
  gl::GLint i_uniform_mvp;
  gl::GLint i_uniform_time;
  gl::GLint i_uniform_tex;

  std::unique_ptr<globjects::VertexArray> vao;
  std::unique_ptr<globjects::Buffer> b_vertices;

  size_t draw_len;
};
