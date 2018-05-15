#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Program.h>
#include <globjects/VertexArray.h>
#include <globjects/Texture.h>


class Rain {
public:
  const int N_PARTICLE = 1000;

  Rain (void);

  void draw (glm::mat4 _vp);

private:
  std::unique_ptr<globjects::Program> program;
  std::unique_ptr<globjects::File> shader_v_src;
  std::unique_ptr<globjects::AbstractStringSource> shader_v_preprocessed;
  std::unique_ptr<globjects::Shader> shader_v;
  std::unique_ptr<globjects::File> shader_f_src;
  std::unique_ptr<globjects::AbstractStringSource> shader_f_preprocessed;
  std::unique_ptr<globjects::Shader> shader_f;

  gl::GLint i_attr_coord3d;
  gl::GLint i_uniform_mvp;
  gl::GLint i_uniform_time;

  std::unique_ptr<globjects::VertexArray> vao;
  std::unique_ptr<globjects::Buffer> b_vertices;

  size_t draw_len;
};
