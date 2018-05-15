#include <vector>

#include <SDL2/SDL.h>

#include <glm/gtc/matrix_transform.hpp>

#include <glbinding/gl/gl.h>

#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Buffer.h>
#include <globjects/Shader.h>
#include <globjects/VertexAttributeBinding.h>

#include "Rain.h"


Rain::Rain (void) {
  // Shaders.
  shader_v_src = globjects::Shader::sourceFromFile("rain.v.glsl");
  shader_v_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_v_src.get());
  shader_v = globjects::Shader::create(
    gl::GL_VERTEX_SHADER, shader_v_preprocessed.get());

  shader_f_src = globjects::Shader::sourceFromFile("rain.f.glsl");
  shader_f_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_f_src.get());
  shader_f = globjects::Shader::create(
    gl::GL_FRAGMENT_SHADER, shader_f_preprocessed.get());

  program = globjects::Program::create();
  program->attach(shader_v.get(), shader_f.get());

  i_attr_coord3d = program->getAttributeLocation("coord3d");
  i_uniform_mvp = program->getUniformLocation("mvp");
  i_uniform_time = program->getUniformLocation("time");

  // Vertices.
  std::vector<glm::vec3> vertices;

  for (int i = 0; i < N_PARTICLE; ++i) {
    vertices.push_back(glm::vec3(0.1 * i, 0.1 * i, 0.1 * i));
  }

  vao = globjects::VertexArray::create();

  b_vertices = globjects::Buffer::create();
  b_vertices->setData(vertices, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = vao->binding(0);
    vao_bind->setAttribute(i_attr_coord3d);
    vao_bind->setBuffer(b_vertices.get(), 0, sizeof(glm::vec3));
    vao_bind->setFormat(vertices.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    vao->enable(0);
  }

  draw_len = vertices.size();
}

void Rain::draw (glm::mat4 _vp) {
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
  glm::mat4 mvp = _vp * model;

  program->use();
  program->setUniform(i_uniform_mvp, mvp);
  program->setUniform(i_uniform_time, SDL_GetTicks());
  vao->drawArrays(gl::GL_POINTS, 0, draw_len);
  program->release();
}
