#include <random>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <globjects/VertexAttributeBinding.h>

#include "Exhaust.h"


Exhaust::Exhaust (void) {
  // Shaders.
  shader_v_src = globjects::Shader::sourceFromFile("misc/exhaust.v.glsl");
  shader_v_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_v_src.get());
  shader_v = globjects::Shader::create(
    gl::GL_VERTEX_SHADER, shader_v_preprocessed.get());

  shader_f_src = globjects::Shader::sourceFromFile("misc/exhaust.f.glsl");
  shader_f_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_f_src.get());
  shader_f = globjects::Shader::create(
    gl::GL_FRAGMENT_SHADER, shader_f_preprocessed.get());

  program = globjects::Program::create();
  program->attach(shader_v.get(), shader_f.get());

  i_attr_coord3d = program->getAttributeLocation("coord3d");
  i_uniform_m = program->getUniformLocation("m");
  i_uniform_v = program->getUniformLocation("v");
  i_uniform_p = program->getUniformLocation("p");
  i_uniform_time = program->getUniformLocation("time");
  i_uniform_tex = program->getUniformLocation("texture");

  program->setUniform(i_uniform_tex, 0);

  // Vertices.
  std::vector<glm::vec3> vertices;

  std::random_device rd;
  std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
  std::mt19937 generator(seed);

  std::uniform_real_distribution<> r(0.5, 2.0);
  std::uniform_real_distribution<> r2(-4.0, 4.0);

  for (int i = 0; i < N_PARTICLE; ++i) {
    glm::vec3 pos = glm::vec3(r(generator), r2(generator), r(generator));

    vertices.push_back(pos);
    vertices.push_back(pos);
    vertices.push_back(pos);
    vertices.push_back(pos);
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

  // Texture.
  {
    auto res_texture = IMG_Load("misc/smoke.png");

    if (!res_texture) {
      throw std::runtime_error("Unable to load misc/smoke.png");
    }

    texture = globjects::Texture::create(gl::GL_TEXTURE_2D);
    texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);

    texture->image2D(
      0,
      gl::GL_RGBA,
      glm::ivec2(res_texture->w, res_texture->h),
      0,
      gl::GL_RGBA,
      gl::GL_UNSIGNED_BYTE,
      res_texture->pixels);

    SDL_FreeSurface(res_texture);
  }
}

void Exhaust::draw (glm::mat4 _v, glm::mat4 _p) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
  model = glm::translate(model, glm::vec3(5.5, 0.0, 0.0));

  glm::mat4 mvp = _p * _v * model;

  gl::glActiveTexture(gl::GL_TEXTURE0);
  texture->bind();

  program->use();
  program->setUniform(i_uniform_m, model);
  program->setUniform(i_uniform_v, _v);
  program->setUniform(i_uniform_p, _p);
  program->setUniform(i_uniform_time, SDL_GetTicks());
  vao->drawArrays(gl::GL_QUADS, 0, draw_len);
  program->release();

  texture->unbind();
}
